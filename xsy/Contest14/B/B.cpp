#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])

char s[1 << 25], *S = s;
#define getchar() (*S++)
template <typename tp>
inline void read(tp &dig) {
  char ch = getchar();
  int flag = 0;
  dig = 0;
  while (!isdigit(ch)) {
    if (ch == '-') flag = 1;
    ch = getchar();
  }
  while (isdigit(ch)) dig = dig * 10 + ch - '0', ch = getchar();
  if (flag) dig = -dig;
}

const int Max_n = 1e6 + 5, mod = 1e9 + 7;
int n, m, L, ans, Ans;
int fa[Max_n];
int f[Max_n], g[Max_n];
int f1[Max_n], f2[Max_n], g1[Max_n], g2[Max_n];
int cnt, stk[Max_n << 1];
bool vis[Max_n];
int w[Max_n], nx[Max_n], v[Max_n << 2];
struct graph {
  int hd[Max_n];
  int cntr, nx[Max_n], to[Max_n];
  void addr(int u, int v) {
    cntr++;
    nx[cntr] = hd[u], to[cntr] = v;
    hd[u] = cntr;
  }
} Gr;

namespace Input {
void main() {
  fread(s, 1, 1 << 25, stdin);
  read(n), read(m), read(L), f[0] = g[L + 1] = 1;
  for (int i = 2; i <= n; i++) read(fa[i]);
  for (int i = n; i >= 2; i--) Gr.addr(fa[i], i);
  for (int i = 1; i <= n; i++) read(w[i]);
  for (int i = 1; i <= m; i++) read(v[i]);
}
}  // namespace Input

void Mod(int &x) { x = x >= mod ? x - mod : x; }

namespace Init {
void build(int x) {
  stk[++cnt] = x;
  go(Gr, x, i, v) build(v);
  stk[++cnt] = x;
}
void main() { build(1); }
}  // namespace Init

namespace Solve {
void main() {
  for (int i = m + 1; i <= m + n; i++) v[i] = v[i - n];
  for (int s = 1; s <= m; s += n) {
    for (int i = 1; i <= n; i++) nx[i] = v[s + i - 1];
    for (int i = 1; i <= L; i++) f[i] = g[i] = 0;
    for (int i = 1; i <= cnt; i++) {
      int x = stk[i];
      if (!vis[x]) {
        g1[x] = g[w[x] + 1] - (w[x] == L), g2[x] = g[nx[x] + 1] - (nx[x] == L);
        f1[x] = f[w[x] - 1], f2[x] = f[nx[x] - 1],
        Mod(f[nx[x]] += f[nx[x] - 1]);
      } else {
        Mod(g1[x] = g[w[x] + 1] - g1[x] + mod),
            Mod(g2[x] = g[nx[x] + 1] - g2[x] + mod);
        Mod(g[w[x]] += g1[x]), Mod(f[w[x] = nx[x]] += mod - f[nx[x] - 1]);
      }
      vis[x] ^= 1;
    }
    ans = g[1];
    for (int i = 1; i <= n; i++) {
      Mod(ans += mod - (LL)f1[i] * g1[i] % mod);
      Mod(ans += (LL)f2[i] * g2[i] % mod);
      if (s + i - 1 <= m) Mod(Ans += (LL)ans * (s + i - 1) % mod);
    }
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
