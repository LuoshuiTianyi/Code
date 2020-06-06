#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define LL long long
#define LD double
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])

char read_str[1 << 25], *CH = read_str;
#define getchar() (*CH++)
LL read() {
  char ch = getchar();
  int fl = 0;
  LL x = 0;
  while (!isdigit(ch)) {
    if (ch == '-') fl = 1;
    ch = getchar();
  }
  while (isdigit(ch)) x = (x << 1) + (x << 3) + ch - '0', ch = getchar();
  return fl ? -x : x;
}
void rstr(char *s) {
  char *x = s;
  char ch = getchar();
  while (ch == ' ' || ch == '\n' || ch == '\r') ch = getchar();
  while (ch != ' ' && ch != '\n' && ch != '\r') {
    *x++ = ch;
    ch = getchar();
  }
}

const int Max_n = 5e5 + 5;
int n, K, divi, cnt;
LD ans, sec[Max_n];
vector<LD> d[Max_n];
struct dots {
  LD x, y, dis;
  LD operator*(const dots &b) const {
    return x * b.y - y * b.x;
  }
} k[Max_n];

namespace Input {
void main() { 
  fread(read_str, 1, 1 << 25, stdin); 
  n = read(), K = read(), divi = K / 2;
  for (int i = 1; i <= n; i++) {
    LD x = read(), y = read();
    k[i].x = x, k[i].y = y, k[i].dis = sqrt(x * x + y * y);
  }
}
}  // namespace Input

namespace Init {
bool cmp(dots a, dots b) {
  return a * b < 0;
}
void main() {
  sort(k + 1, k + n + 1, cmp);
  cnt = 1;
  for (int i = 2; i <= n; i++) {
    if (k[i] * k[i - 1] != 0) cnt++;
    d[cnt].push_back(k[i].dis);
  }
  for (int i = 1; i <= cnt; i++) sort(d[i].begin(), d[i].end());
}
}  // namespace Init

namespace Solve {
priority_queue<LD> q;
void main() {
  int c = 0, tp = K;
  for (int i = 1; i <= cnt; i++)
    for (int j = d[i].size() - 1; ~j; j--) {
      q.push(d[i][j] * (K - ((int)d[i].size() - 1 - j) * 2 - 1));
    }
  while (K && q.top() > 0) ans += q.top(), q.pop(), K--;
  if (K) {
    K--;
    for (int i = 1; i <= cnt; i++)
      if ((int)d[i].size() >= divi) {
        for (int j = K - 1; ~j; j--)
          ans += d[i][j] * (tp - (divi + K - 1 - j) * 2 - 1);
        break;
      }
  }
  printf("%.7lf", ans);
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("D.in", "r", stdin);
  freopen("D.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
