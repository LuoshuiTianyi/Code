#include <algorithm>
#include <cstdio>
#include <iostream>
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

const int Max_n = 1e5 + 5;
int n, m;
int id[Max_n], deg[Max_n];
LL buk[Max_n], r3[Max_n], r4[Max_n], tp[Max_n];
LL d2[Max_n], d3[Max_n];
bool vis[Max_n];
struct graph {
  int hd[Max_n];
  int cntr, nx[Max_n << 1], to[Max_n << 1];
  void addr(int u, int v) {
    cntr++;
    nx[cntr] = hd[u], to[cntr] = v;
    hd[u] = cntr;
  }
} G;

namespace Input {
void main() { 
  fread(read_str, 1, 1 << 25, stdin); 
  n = read(), m = read();
  for (int i = 1; i <= m; i++) {
    int u = read(), v = read();
    G.addr(u, v), G.addr(v, u);
    deg[u]++, deg[v]++;
  }
}
}  // namespace Input

namespace Init {
bool cmp(int a, int b) { return deg[a] > deg[b]; }
void Push(int x) {
  r4[x] += tp[x] / 2, tp[x] = 0;
}
void main() {
  for (int i = 1; i <= n; i++) id[i] = i;
  sort(id + 1, id + n + 1, cmp);
  for (int i = 1; i <= n; i++) {
    int x = id[i];
    vis[x] = 1;
    LL tmp = 0;
    go(G, x, j, v) if (!vis[v])
      go(G, v, k, p) if (!vis[p]) buk[p]++;
    go(G, x, j, v) if (!vis[v])
      r3[v] += buk[v], tmp += buk[v];
    r3[x] += tmp / 2;
    go(G, x, j, v) if (!vis[v])
      go(G, v, k, p) if (!vis[p]) tp[x] += buk[p] - 1, tp[p] += buk[p] - 1, r4[v] += buk[p] - 1;
    Push(x);
    go(G, x, j, v) if (!vis[v])
      go(G, v, k, p) if (!vis[p]) Push(p), buk[p]--;
  }
}
}

namespace Solve {
void main() {
  for (int i = 1; i <= n; i++) go(G, i, j, v) d2[i] += deg[v] - 1;
  for (int i = 1; i <= n; i++) {
    go(G, i, j, v) d3[i] += d2[v] - (deg[i] - 1);
    d3[i] -= 2ll * r3[i];
  }
  for (int i = 1; i <= n; i++) {
    LL ans = 0;
    go(G, x, i, v) ans += d3[v];
    printf("%lld\n", ans);
  }
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
