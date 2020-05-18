#include <cstdio>
#include <iostream>
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

const int Max_n = 2e6 + 5, mod = 1e9 + 7;
int n, m, L, ans, Ans;
int id[Max_n];
int f[Max_n], g[Max_n];
int w[Max_n], v[Max_n];
struct graph {
  int hd[Max_n];
  int cntr, nx[Max_n << 1], to[Max_n << 1];
  void addr(int u, int v) {
    cntr++;
    nx[cntr] = hd[u], to[cntr] = v;
    hd[u] = cntr;
  }
} Gr;

namespace Input {
void main() {
  n = read(), m = read(), L = read(), f[0] = g[L + 1] = 1;
  for (int i = 2; i <= n; i++) Gr.addr(read(), i);
  for (int i = 1; i <= n; i++) w[i] = read();
}
}  // namespace Input

void Mod(int &x) { x = x >= mod ? x - mod : x; }
void F(int x, int t) {
  Mod(f[x] += t * f[x - 1] + (t == -1 ? mod : 0));
}

namespace Init {
void build(int x) {
  if (w[x] == L) Mod(ans += f[L - 1]);
  F(w[x], 1);
  go(Gr, x, i, v) build(v);
  F(w[x], -1);
}
void main() {
  build(1);
}
}  // namespace Init

namespace Solve {
void DP(int x) {
  int t = v[id[x]], t1 = g[w[x] + 1], t2 = g[t + 1];
  F(t, 1);
  //go(Gr, x, i, v) DP(v);
  cout << x << " " << w[x] << " " << ans << endl;
  Mod(t1 = g[w[x] + 1] - t1 + mod), Mod(t2 = g[t + 1] - t2 + mod);
  Mod(ans += mod - (LL)t1 * f[w[x] - 1] % mod);
  Mod(ans += (LL)t2 * f[t - 1] % mod);
  Mod(g[w[x]] += t1), F(w[x] = t, -1);
  Mod(Ans += (LL)id[x] * ans % mod);
}
void main() {
  for (int s = 1; s <= m; s += n) {
    for (int i = 1; i <= n; i++) id[i] = s + i - 1;
    for (int i = 1; i <= L; i++) f[i] = g[i] = 0;
    DP(1);
  }
  cout << Ans << endl;
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
