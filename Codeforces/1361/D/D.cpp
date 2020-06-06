#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
#define LL long long
#define LD long double
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
int n, K, cnt;
vector<LD> d[Max_n];
LD sqr(LD x) { return x * x; }
struct dots {
  LD x, y, dis;
  LD operator*(const dots &b) const {
    return x * b.y - y * b.x;
  }
} k[Max_n];

namespace Input {
void main() { 
  fread(read_str, 1, 1 << 25, stdin); 
  n = read(), K = read();
  for (int i = 1; i <= n; i++) {
    LD x = read(), y = read();
    k[i].x = x, k[i].y = y, k[i].dis = sqrt(sqr(x) + sqr(y));
  }
}
}  // namespace Input

namespace Init {
bool cmp(dots a, dots b) {
  return a * b < 0;
}
void main() {
  sort(k + 1, k + n + 1, cmp);
  for (int i = 1; i <= n; i++) {
    if (k[i].x == 0 && k[i].y == 0) continue;
    if (k[i] * k[i - 1] != 0) cnt++;
    d[cnt].push_back(k[i].dis);
  }
  for (int i = 1; i <= cnt; i++) sort(d[i].begin(), d[i].end());
}
}  // namespace Init

namespace Solve {
void main() {
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
