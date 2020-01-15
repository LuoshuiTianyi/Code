#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
typedef int LL;
const double eps = 1e-7;
const LL maxn = 70;
LL n;
double ans = 1.0;
double D[maxn][maxn], p[maxn][maxn];
inline double Solve() {
  double ret(1.0);
  LL N(n - 1), tr(0);
  for (LL i = 1; i <= N; ++i) {
    LL mx(i);
    for (LL j = i + 1; j <= N; ++j)
      if (D[mx][i] < D[j][i]) mx = j;
    if (mx != i) swap(D[mx], D[i]), tr ^= 1;
    if (D[i][i] > -eps && D[i][i] < eps) return 0.0;
    for (LL j = i + 1; j <= N; ++j) {
      double tmp = D[j][i] / D[i][i];
      for (LL k = i; k <= N; ++k) D[j][k] -= tmp * D[i][k];
    }
    ret = ret * D[i][i];
  }
  if (tr) ret = -ret;
  return ret;
}
int main() {
  freopen("3317.in", "r", stdin);
  freopen("3317.ans", "w", stdout);
  scanf("%d", &n);
  for (LL i = 1; i <= n; ++i) {
    for (LL j = 1; j <= n; ++j) {
      scanf("%lf", &D[i][j]);
    }
  }
  for (LL i = 1; i <= n; ++i) {
    for (LL j = 1; j <= n; ++j) {
      if (fabs(D[i][j]) < eps)
        D[i][j] = eps;
      else if (fabs(1.0 - D[i][j]) < eps)
        D[i][j] = 1.0 - eps;
      if (j > i) ans *= (1.0 - D[i][j]);
      D[i][j] = D[i][j] / (1 - D[i][j]);
    }
  }
  for (LL i = 1; i <= n; ++i) {
    D[i][i] = 0;
    for (LL j = 1; j <= n; ++j)
      if (i != j) D[i][i] += D[i][j], D[i][j] = -D[i][j];
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++)
      printf("%.2lf ", D[i][j]);
    cout << endl;
  }
  ans *= Solve();
  printf("%.10lf\n", ans);
  return 0;
}
