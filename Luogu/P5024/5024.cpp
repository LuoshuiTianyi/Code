#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n, m, nx[200001], to[200001], head[100001], a, b, c, d, type;
int fa[200001], deep[200001], w[100001], jump[100001][18];
long long f[100001][2], g[100001][2], mm[100001], dp[100001][18][2][2],
    inf = 2e15;
void read(int &x) {
  x = 0;
  char ch = getchar();
  while (!isdigit(ch))
    ch = getchar();
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
}
void put(long long x) {
  if (x < 0) {
    putchar('-');
    x = -x;
  }
  if (x > 9)
    put(x / 10);
  putchar(x % 10 + '0');
}
long long min(long long a, long long b) { return a < b ? a : b; }
void Min(long long &a, long long b) { a = a < b ? a : b; }
void add(int u, int v, int d) {
  nx[d] = head[u];
  to[d] = v;
  head[u] = d;
}
void build() {
  int que[100001], hd = 0, tail = 0;
  que[++tail] = 1;
  do {
    int x = que[++hd];
    for (register int i = head[x]; i; i = nx[i])
      if (to[i] != fa[x]) {
        fa[to[i]] = x;
        deep[to[i]] = deep[x] + 1;
        que[++tail] = to[i];
      }
  } while (hd < tail);
}
void DP(int x) {
  f[x][1] = w[x];
  if (x == a)
    f[x][(c + 1) % 2] = inf;
  if (x == b)
    f[x][(d + 1) % 2] = inf;
  for (register int i = head[x]; i; i = nx[i])
    if (to[i] != fa[x]) {
      int p = to[i];
      DP(p);
      f[x][1] += mm[p];
      f[x][0] += f[p][1];
    }
  mm[x] = min(f[x][1], f[x][0]);
}
void D_P() {
  int que[100001], hd = 0, tail = 0;
  que[++tail] = 1;
  do {
    int x = que[++hd];
    for (register int i = head[x]; i; i = nx[i])
      if (to[i] != fa[x]) {
        int p = to[i];
        g[p][0] = g[x][1] + f[x][1] - mm[p];
        g[p][1] = min(g[x][0] + f[x][0] - f[p][1], g[p][0]);
        que[++tail] = p;
      }
  } while (hd < tail);
}
long long work() {
  if (deep[a] < deep[b]) {
    swap(a, b);
    swap(c, d);
  }
  long long tx[2] = {inf, inf}, ty[2] = {inf, inf}, nx[2], ny[2];
  tx[c] = f[a][c], ty[d] = f[b][d];
  for (register int i = 17; i >= 0; i--)
    if (deep[jump[a][i]] >= deep[b]) {
      nx[0] = nx[1] = inf;
      for (register int j = 0; j <= 1; j++)
        for (register int k = 0; k <= 1; k++)
          Min(nx[j], tx[k] + dp[a][i][k][j]);
      tx[0] = nx[0], tx[1] = nx[1];
      a = jump[a][i];
    }
  if (a == b)
    return tx[d] + g[b][d];
  for (register int i = 17; i >= 0; i--)
    if (jump[a][i] != jump[b][i]) {
      nx[0] = nx[1] = inf;
      ny[0] = ny[1] = inf;
      for (register int j = 0; j <= 1; j++)
        for (register int k = 0; k <= 1; k++) {
          Min(nx[j], tx[k] + dp[a][i][k][j]);
          Min(ny[j], ty[k] + dp[b][i][k][j]);
        }
      tx[0] = nx[0], tx[1] = nx[1];
      ty[0] = ny[0], ty[1] = ny[1];
      a = jump[a][i];
      b = jump[b][i];
    }
  int lca = fa[a];
  return min(f[lca][0] - f[a][1] - f[b][1] + tx[1] + ty[1] + g[lca][0],
             f[lca][1] - mm[a] - mm[b] + min(tx[0], tx[1]) + min(ty[0], ty[1]) +
                 g[lca][1]);
}
int main() {
  freopen("5024.in", "r", stdin);
  freopen("5024.out", "w", stdout);
  read(n), read(m), read(type);
  int u, v;
  for (register int i = 1; i <= n; i++)
    read(w[i]);
  for (register int i = 1; i < n; i++) {
    read(u), read(v);
    add(u, v, i);
    add(v, u, i + n);
  }
  deep[1] = 1;
  build();
  DP(1);
  D_P();
  for (register int i = 1; i <= n; i++) {
    jump[i][0] = fa[i];
    dp[i][0][0][0] = 2e15;
    dp[i][0][0][1] = f[fa[i]][1] - mm[i];
    dp[i][0][1][0] = f[fa[i]][0] - f[i][1];
    dp[i][0][1][1] = f[fa[i]][1] - mm[i];
  }
  for (register int j = 1; j <= 17; j++)
    for (register int i = 1; i <= n; i++) {
      jump[i][j] = jump[jump[i][j - 1]][j - 1];
      for (register int k = 0; k <= 1; k++)
        for (register int l = 0; l <= 1; l++) {
          dp[i][j][k][l] = 2e15;
          for (register int q = 0; q <= 1; q++)
            dp[i][j][k][l] =
                min(dp[i][j][k][l],
                    dp[i][j - 1][k][q] + dp[jump[i][j - 1]][j - 1][q][l]);
        }
    }
  for (register int i = 1; i <= m; i++) {
    read(a), read(c), read(b), read(d);
    if ((fa[a] == b && c == 0 && d == 0) || (fa[b] == a && c == 0 && d == 0)) {
      cout << "-1\n";
      continue;
    }
    put(work());
    putchar('\n');
  }
}
