#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
#define LL long long
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])
#define inline __inline__ __attribute__((always_inline))
inline LL read() {
  LL x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-') w = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}

const int Max_n = 1e6 + 5, mod = 998244353;
int n, L, K, ans;
vector<int> f[Max_n], g[Max_n];
struct graph {
  int hd[Max_n];
  int cntr, nx[Max_n << 1], to[Max_n << 1];
  void addr(int u, int v) {
    cntr++;
    nx[cntr] = hd[u], to[cntr] = v;
    hd[u] = cntr;
  }
} G;

void Mod(int &x) { x = x >= mod ? x - mod : x; }
int ksm(int a, int b = mod - 2) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % mod)
    if (b & 1) res = 1ll * res * a % mod;
  return res;
}

namespace Input {
void main() {
  n = read(), L = read(), K = read();
  for (int i = 1; i < n; i++) {
    int u = read(), v = read();
    G.addr(u, v), G.addr(v, u);
  }
}
}  // namespace Input

namespace Init {
void main() {}
}  // namespace Init

namespace Solve {
void DP1(int x, int fa) {
  go(G, x, i, v) if (v != fa) {
    DP1(v, x);
    for (int i = 1; i <= L; i++)
      f[x][i] = 1ll * f[x][i] * (f[v][i - 1] + 1) % mod;
  }
}
void DP2(int x, int fa) {
  if (x != 1) {
    for (int i = 1; i <= L; i++) {
      g[x][i] = g[fa][i - 1];
      if (i > 1)
        g[x][i] =
            1ll * g[x][i] * f[fa][i - 1] % mod * ksm(f[x][i - 2] + 1) % mod;
      Mod(++g[x][i]);
    }
    Mod(ans -= ksm(1ll * f[x][L - 1] * (g[x][L] + mod - 1) % mod, K) - mod);
    // cout << x << " " << g[x][L] << endl;
  }
  Mod(ans += ksm(1ll * f[x][L] * g[x][L] % mod, K));
  go(G, x, i, v) if (v != fa) DP2(v, x);
}
void main() {
  for (int i = 1; i <= n; i++) f[i].resize(L + 1, 1), g[i].resize(L + 1, 1);
  DP1(1, 0), DP2(1, 0);
  // for (int i = 1; i <= n; i++) {
  //  for (int j = 0; j <= L; j++)
  //    cout << g[i][j] << " ";
  //  cout << endl;
  //}
  cout << ans << endl;
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("5291.in", "r", stdin);
  freopen("5291.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
