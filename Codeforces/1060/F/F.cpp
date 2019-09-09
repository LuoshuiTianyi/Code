#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define LD long double
#define go(x, i, v) for (int i = hd[x], v = to[i]; i; v = to[i = nx[i]])
LL read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 55;
int n;
int cntr, hd[Max_n], nx[Max_n << 1], to[Max_n << 1];
int size[Max_n];
LD fac[Max_n];
LD f[Max_n][Max_n], g[Max_n], tp[Max_n];
void addr(int u, int v) {
  cntr++;
  nx[cntr] = hd[u], to[cntr] = v;
  hd[u] = cntr;
}
LD C(int n, int m) {
  if (m > n) return 0;
  return fac[n] / fac[m] / fac[n - m];
}
void DP(int x, int fa) {
  size[x] = f[x][0] = 1;
  //cout << x << " " << fa << endl;
  go(x, i, v) if (v != fa) {
    DP(v, x);
    for (int i = 0; i <= size[v]; i++) {
      g[i] = 0;
      for (int j = 0; j < i; j++) g[i] += f[v][j] / 2;
      g[i] += f[v][i] * (size[v] - i);
    }
    for (int i = 0; i <= size[x] + size[v]; i++) tp[i] = 0;
    for (int i = 0; i < size[x]; i++)
      for (int j = 0; j <= size[v]; j++)
        tp[i + j] += f[x][i] * g[j] * C(i + j, i) *
                     C(size[x] + size[v] - i - 1 - j, size[x] - i - 1);
    size[x] += size[v];
    for (int i = 0; i < size[x]; i++) f[x][i] = tp[i];
  }
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("F.in", "r", stdin);
  freopen("F.out", "w", stdout);
#endif
  n = read();
  int u, v;
  for (int i = 1; i < n; i++) {
    u = read(), v = read();
    addr(u, v), addr(v, u);
  }
  fac[0] = 1;
  for (int i = 1; i < Max_n; i++) fac[i] = fac[i - 1] * i;
  for (int i = 1; i <= n; i++) {
    memset(f, 0, sizeof(f));
    DP(i, 0);
    printf("%.6lf\n", (double)(f[i][n - 1] / fac[n - 1]));
  }
}
