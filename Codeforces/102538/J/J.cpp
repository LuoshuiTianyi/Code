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

const int Max_n = 2e5 + 5, mod = 998244353;
int T, n, m, ans;
int tot, cnt;
int deg[Max_n];
bool vis[Max_n];
struct graph {
  int cntr;
  int hd[Max_n], nx[Max_n * 3], to[Max_n * 3];
  void addr(int u, int v) {
    cntr++;
    nx[cntr] = hd[u], to[cntr] = v;
    hd[u] = cntr;
  }
} G;

namespace Input {
void main() { 
  n = read(), m = read(), G.cntr = 0;
  for (int i = 1; i <= n; i++) G.hd[i] = deg[i] = vis[i] = 0;
  for (int i = 1; i <= m; i++) {
    int u = read(), v = read();
    deg[u]++, deg[v]++;
    G.addr(u, v), G.addr(v, u);
  }
}
}  // namespace Input

namespace Solve {
void dfs(int x) {
  vis[x] = 1, tot++, cnt += deg[x];
  go(G, x, i, v) if (!vis[v]) dfs(v);
}
void main() {
  ans = 1;
  for (int i = 1; i <= n; i++)
    if (!vis[i]) {
      tot = cnt = 0, dfs(i);
      cnt >>= 1;
      for (int j = n; j <= cnt; j++) ans = 5ll * ans % mod;
    }
  printf("%d\n", ans);
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("J.in", "r", stdin);
  freopen("J.out", "w", stdout);
#endif
  fread(read_str, 1, 1 << 25, stdin); 
  T = read();
  while (T--) {
    Input::main();
    Solve::main();
  }
}
