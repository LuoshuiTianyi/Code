#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define go(x, i, v) for (int i = hd[x], v = to[i]; i; v = to[i = nx[i]])
#define inline __inline__ __attribute__((always_inline))
inline LL read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 505;
int n, m;
int cntr, hd[Max_n], nx[Max_n * Max_n << 1], to[Max_n * Max_n << 1];
int u[Max_n * Max_n], v[Max_n * Max_n];
double Ans, in[Max_n], f[Max_n][Max_n], num[Max_n * Max_n], ans[Max_n];
inline void addr(int u, int v) {
  cntr++;
  nx[cntr] = hd[u], to[cntr] = v;
  hd[u] = cntr;
}
inline void Elimi() {
  for (int i = 1, mp = 1; i < n; mp = ++i) {
    for (int j = i + 1; j < n; j++)
      if (abs(f[j][i]) > abs(f[mp][i])) mp = j;
    for (int j = i; j <= n; j++) swap(f[i][j], f[mp][j]);
    for (int j = 1; j < n; j++)
      if (i != j) {
        double x = f[j][i] / f[i][i];
        for (int k = i; k <= n; k++) f[j][k] -= f[i][k] * x;
      }
  }
  for (int i = 1; i < n; i++) ans[i] = (f[i][n] / f[i][i]) / in[i];
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("3232.in", "r", stdin);
  freopen("3232.out", "w", stdout);
#endif
  n = read(), m = read();
  for (int i = 1; i <= m; i++) {
    in[u[i] = read()]++, in[v[i] = read()]++;
    addr(u[i], v[i]), addr(v[i], u[i]);
  }
  for (int i = 1; i < n; i++) {
    f[i][i] = 1;
    go(i, j, v) if (v != n) f[i][v] = -1.0 / in[v];
  }
  f[1][n] = 1;
  Elimi();
  for (int i = 1; i <= m; i++) num[i] = ans[u[i]] + ans[v[i]];
  sort(num + 1, num + m + 1);
  for (int i = 1; i <= m; i++)
    Ans += (double)num[i] * (m - i + 1);
  printf("%.3lf", Ans);
}
