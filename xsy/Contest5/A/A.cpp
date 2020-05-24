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

const int Max_n = 100, Max_s = 1 << 15 | 1, mod = 1e9 + 7;
int n, m;
int l[Max_n], r[Max_n], l2[Max_n], r2[Max_n];
int cnt, ct, all[Max_n], fa[Max_n], id[Max_n];
int val[Max_n], g[Max_s], f[10][Max_s];
vector Con[Max_n];

int ksm(int a, int b = mod - 2) {
  int res = 1;
  for (; b; b >>= 1, a = (LL)a * a % mod)
    if (b & 1) res = (LL)res * a % mod;
  return res;
}

namespace Input {
void main() { 
  fread(read_str, 1, 1 << 25, stdin); 
  n = read(), m = read();
  for (int i = 1; i <= m; i++)
    all[++cnt] = l[i] = read(), all[++cnt] = r[i] = read();
}
}  // namespace Input

namespace Init {
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
void main() {
  sort(all + 1, all + cnt + 1);
  cnt = unique(all + 1, all + cnt + 1) - all - 1;
  for (int i = 1; i <= cnt; i++) fa[i] = i;
  for (int i = 1; i <= m; i++) {
    l2[i] = lower_bound(all + 1, all + cnt + 1, l[i]) - all;
    r2[i] = lower_bound(all + 1, all + cnt + 1, r[i]) - all;
    fa[find(r2[i])] = find(l2[i]);
  }
  for (int i = 1; i <= cnt; i++) ksm(10, all[i] - all[i - 1]);
  for (int i = 1; i <= cnt; i++) {
    if (find(i) == i) id[i] = ++ct;
    Con[id[find(i)]].push_back(i);
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
