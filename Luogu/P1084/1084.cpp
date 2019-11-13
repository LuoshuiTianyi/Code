#include <algorithm>
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

const int Max_n = 5e4 + 5;
int n, m;
LL ans;
int t, f[Max_n], a[Max_n], s[Max_n];
LL dep[Max_n];

struct graph {
  int hd[Max_n];
  int cntr, nx[Max_n << 1], to[Max_n << 1], w[Max_n << 1];
  void addr(int u, int v, int W = 0) {
    cntr++;
    nx[cntr] = hd[u], to[cntr] = v, w[cntr] = W;
    hd[u] = cntr;
  }
} G;

namespace Input {
void main() {
  n = read();
  int u, v, w;
  for (int i = 1; i < n; i++) {
    u = read(), v = read(), w = read();
    G.addr(u, v, w), G.addr(v, u, w);
  }
  m = read();
  for (int i = 1; i <= m; i++) a[i] = read();
}
}  // namespace Input

namespace Init {
void build(int x, int fa) {
  go(G, x, i, v) if (v != fa) dep[v] = dep[x] + G.w[i], build(v, x);
}
bool cmp(int x, int y) { return dep[a[x]] < dep[a[y]]; }
bool cmp2(int x, int y) { return dep[x] > dep[y]; }
void main() {
  build(1, 0);
  sort(a + 1, a + m + 1, cmp), dep[0] = 1e18;
  go(G, 1, i, v) s[++t] = v;
  sort(s + 1, s + t + 1, cmp2);
}
}  // namespace Init

namespace Solve {
void DP(int x, int fa) {
  go(G, x, i, v) if (v != fa) {
    DP(v, fa);
    if (dep[f[v]] - dep[x] < dep[f[x]] - dep[x]) f[x] = f[v];
  }
}
bool check(LL lim) {
  
}
void main() {
  if (m < t) {
    puts("-1");
    return;
  }
  LL l = 0, r = 1e18;
  while (l <= r) {
    LL mid = l + r >> 1;
    if (check(mid)) ans = mid, r = mid - 1;
    else l = mid + 1;
  }
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("1084.in", "r", stdin);
  freopen("1084.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
