#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define LL long long
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define GO debug("GO\n")
inline int rint() {
  register int x = 0, f = 1;
  register char c;
  while (!isdigit(c = getchar()))
    if (c == '-') f = -1;
  while (x = (x << 1) + (x << 3) + (c ^ 48), isdigit(c = getchar()))
    ;
  return x * f;
}
const int N = 12, M = 55;
int n, m;
LL graph[N], cnt[1 << N], ecnt[1 << N], f[1 << N][M], g[1 << N][M];
LL C[M][M];
void init() {
  for (int i = 0; i <= m; ++i) {
    C[i][0] = 1;
    for (int j = 1; j <= i; ++j) C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
  }
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("xhc.in", "r", stdin);
  freopen("xhc.out", "w", stdout);
#endif
  n = rint(), m = rint();
  init();
  for (int i = 0; i < m; ++i) {
    int u = rint(), v = rint();
    u--, v--;
    graph[u] |= (1 << v);
    graph[v] |= (1 << u);
  }
  for (int i = 0; i < 1 << n; ++i) {
    for (int j = 0; j < n; ++j)
      if (i >> j & 1) ecnt[i] += __builtin_popcount(graph[j] & i);
    ecnt[i] >>= 1;  //每条边算了两遍
  }

  for (int S = 0; S < 1 << n; ++S) {
    if (__builtin_popcount(S) == 1) {
      g[S][0] = 1;
      continue;
    }
    for (int T = (S - 1) & S; T; T = (T - 1) & S)
      if (T & (S & -S)) {
        for (int i = 0; i <= ecnt[T] + ecnt[S ^ T]; ++i) {
          for (int j = 0; j <= min(ecnt[T], 1ll * i); ++j)
            f[S][i] += g[T][j] * C[ecnt[S ^ T]][i - j];
        }
        /*
        for (int k1 = 0; k1 <= ecnt[T]; ++ k1)
                for (int k2 = 0; k2 <= ecnt[S ^ T]; ++ k2)
                        f[S][k1 + k2] += g[T][k1] * C[ecnt[S ^ T]][k2];*/
      }
    for (int i = 0; i <= ecnt[S]; ++i) g[S][i] = C[ecnt[S]][i] - f[S][i];
  }
  double ans = 0;
  for (int i = 0; i < m; ++i) ans += 1.0 * f[(1 << n) - 1][i] / C[m][i];
  printf("%.6lf\n", ans / (m + 1));
}
