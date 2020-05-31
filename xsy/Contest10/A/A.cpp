#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
#define LL long long
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

const int Max_n = 2e6 + 5;
int n, K;
int top, stk[Max_n], m[Max_n];
LL f[Max_n], g[Max_n];
vector<LL> a[Max_n];
bool vis[Max_n];

namespace Input {
void main() { 
  fread(read_str, 1, 1 << 25, stdin); 
  n = read(), K = read();
  for (int i = 1; i <= n; i++) {
    a[i].resize(1 + (m[i] = read()), 0);
    for (int j = 0; j <= m[i]; j++) a[i][j + !j] += read();
    m[i] = min(m[i], K);
    for (int j = 2; j <= m[i]; j++) a[i][j] += a[i][j - 1];
  }
}
}  // namespace Input

namespace Init {
bool cmp(vector<LL> a, vector<LL> b) { return a.size() < b.size(); }
int t;
pair<LL, int> s[Max_n];
void main() {
  sort(a + 1, a + n + 1, cmp);
  for (int i = 1, p = 1; i <= K; i++) {
    while (p <= n && m[p] < i) p++;
    if (p > n) break;
    t = 0;
    for (int j = p; j <= n; j++) s[++t] = make_pair(a[j][i], j);
    nth_element(s + 1, s + tot, s + t + 1);
    for (int i = 1; i <= tot; i++)
      if (!vis[i]) 
  }
}
}  // namespace Init

namespace Solve {
void main() {}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("A.in", "r", stdin);
  freopen("A.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
