#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n, m, d[501], q[501], h[502], f[501][501], pos[502][501], inf = 1e9;
int work(int l, int r) {
  int mid = (l + r) >> 1;
  return h[l] - h[mid] - (mid - l) * (h[mid] - h[mid + 1]) + q[r] - q[mid] -
         (r - mid) * (q[mid] - q[mid - 1]);
}
int main() {
  freopen("4677.in", "r", stdin);
  freopen("4677.out", "w", stdout);
  cin >> n >> m;
  for (int i = 2; i <= n; i++) {
    scanf("%d", &d[i]);
    q[i] = d[i], h[i - 1] = d[i];
  }
  for (int l = 1; l <= 2; l++)
    for (int i = 1; i <= n; i++)
      q[i] += q[i - 1];
  for (int l = 1; l <= 2; l++)
    for (int i = n; i >= 1; i--)
      h[i] += h[i + 1];
  for (int i = 1; i <= n; i++)
    f[i][1] = work(1, i), pos[i][1] = 0;
  for (int j = 2; j <= m; j++) {
    pos[n + 1][j] = n;
    for (int i = n; i > j; i--) {
      f[i][j] = inf;
      for (int k = pos[i][j - 1]; k <= pos[i + 1][j]; k++) {
        int tmp = f[k][j - 1] + work(k + 1, i);
        if (tmp < f[i][j])
          f[i][j] = tmp, pos[i][j] = k;
      }
    }
  }
  cout << f[n][m];
}
