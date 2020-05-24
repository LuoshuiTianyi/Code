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
int val[Max_n], g[Max_s], f[11][Max_s];

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
    all[++cnt] = l[i] = read() - 1, all[++cnt] = r[i] = read();
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
  for (int i = 1; i <= cnt; i++) {
    val[i] = (LL)(ksm(10, all[i] - all[i - 1]) + mod - 1) * ksm(9) % mod;
    if (!all[i]) val[i] = 1;
    cout << val[i] << endl;
  }
  for (int i = 0; i <= cnt; i++)
    if (find(i) == i) id[i] = ++ct;
  for (int s = 0; s < (1 << ct); s++) {
    g[s] = 1;
    for (int i = 1; i <= cnt; i++)
      if ((s >> (id[find(i)] - 1) & 1) && (s >> (id[find(i - 1)] - 1) & 1)) 
        g[s] = (LL)g[s] * (val[i] + 1) % mod * ksm(val[i]) % mod;
  }
}
}  // namespace Init

namespace Solve {
void Mod(int &x) { x = x >= mod ? x - mod : x; }
void main() {
  f[0][0] = 1;
  for (int i = 1; i < 10; i++) {
    for (int s = 0; s < (1 << ct); s++) {
      if (!f[i - 1][s]) continue;
      int C = ((1 << ct) - 1) ^ s;
      for (int t = C;; t = (t - 1) & C) {
        Mod(f[i][s | t] += (LL)f[i - 1][s] * g[t] % mod);
        if (!t) break;
      }
    }
  }
  int ans = f[9][(1 << ct) - 1];
  for (int i = 1; i <= cnt; i++) ans = (LL)ans * val[i] % mod;
  ans = (LL)ans * ksm(10, n - all[cnt]) % mod;
  cout << ans << endl;
}
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
