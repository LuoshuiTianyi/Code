#include <cstdio>
#include <cstdlib>
#include <ctime>
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

const int Max_n = 3e5 + 5, mod = 998244353;
int n, m;
int cntd, dep[Max_n], dfn[Max_n], siz[Max_n];
int c[Max_n];
struct graph {
  int hd[Max_n];
  int cntr, nx[Max_n << 1], to[Max_n << 1];
  void addr(int u, int v) {
    cntr++;
    nx[cntr] = hd[u], to[cntr] = v;
    hd[u] = cntr;
  }
} G;
struct que {
  int u, v, x;
} k[Max_n];

namespace Input {
void main() {
  n = read(), m = read();
  int u, v;
  for (int i = 1; i < n; i++) {
    u = read(), v = read();
    G.addr(u, v), G.addr(v, u);
  }
}
}  // namespace Input

namespace Init {
void build(int x, int fa) {
  dep[x] = dep[fa] + 1, siz[x] = 1, dfn[x] = ++cntd;
  go(G, x, i, v) if (v != fa) build(v, x), siz[x] += siz[v];
}
void main() { build(1, 0); }
}  // namespace Init

namespace Solve {
void add(int k, int x) {
  for (int i = k; i <= n; i += i & -i) (c[i] += x) %= mod;
}
int query(int k) {
  int ans = 0;
  for (int i = k; i; i -= i & -i) (ans += c[i]) %= mod;
  return (ans + mod) % mod;
}
void main() {
  srand((unsigned)time(NULL));
  int cnt = 0, u, v;
  char op;
  for (int i = 1; i <= m; i++) {
    scanf(" %c", &op);
    u = read();
    if (op == 'U')
      add(dfn[k[u].v], -k[u].x), add(dfn[k[u].v] + siz[k[u].v], k[u].x);
    else {
      v = read();
      if (op == 'Q')
        printf("%s\n", query(dfn[u]) == query(dfn[v]) ? "Yes" : "No");
      else {
        k[++cnt].x = rand() % mod;
        if (dep[u] > dep[v]) swap(u, v);
        add(dfn[v], k[cnt].x), add(dfn[v] + siz[v], -k[cnt].x);
        k[cnt].u = u, k[cnt].v = v;
      }
    }
  }
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("3950.in", "r", stdin);
  freopen("3950.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
