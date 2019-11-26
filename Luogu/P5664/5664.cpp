#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])
LL read() {
  LL x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-') w = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = (x << 1) + (x << 3) + ch - '0';
    ch = getchar();
  }
  return x * w;
}

const int Max_n = 2005, mod = 998244353;
int n, m, ans;
int a[200][Max_n], tot[200];

namespace Input {
void main() {
  n = read(), m = read();
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) (tot[i] += (a[i][j] = read())) %= mod;
}
}  // namespace Input

namespace Init {
void main() {
  ans = 1;
  for (int i = 1; i <= n; i++) ans = 1ll * ans * (tot[i] + 1) % mod;
  ans = (ans - 1 + mod) % mod;
}
}  // namespace Init

namespace Solve {
int f[400], g[400];
void main() {
  for (int x = 1; x <= m; x++) {
    for (int i = 0; i <= 2 * n + 1; i++) f[i] = 0;
    f[n] = 1;
    for (int i = 1; i <= n; i++) {
      for (int j = 0; j <= 2 * n + 1; j++) g[j] = 0;
      for (int j = 1; j <= 2 * n + 1; j++)
        g[j - 1] = 1ll * f[j] * (tot[i] - a[i][x] + mod) % mod;
      for (int j = 0; j < 2 * n + 1; j++)
        (g[j + 1] += 1ll * f[j] * a[i][x] % mod) %= mod;
      for (int j = 0; j <= 2 * n + 1; j++) (f[j] += g[j]) %= mod;
      cout << f[n] << " ";
    }
    cout << endl;
    for (int i = n; i <= 2 * n + 1; i++) ans = (ans - g[i] + mod) % mod;
  }
  cout << ans;
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("5664.in", "r", stdin);
  freopen("5664.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
  return 0;
}
