#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
int n, m, a[5001], q[5001], h[5002], f[5001][5001], pos[5002][5001], inf = 1e9;
int work(int l, int r) {
  int mid = (l + r) >> 1;
  return (2 * mid - l - r) * (q[mid] - q[mid - 1]) + q[l - 1] + q[r] - q[mid] -
         q[mid - 1];
}
int main() {
  freopen("4767.in", "r", stdin);
  freopen("4767.out", "w", stdout);
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  sort(a + 1, a + n + 1);
  for (int i = 2; i <= n; i++)
    q[i] = a[i] - a[i - 1];
  for (int l = 1; l <= 2; l++)
    for (int i = 2; i <= n; i++)
      q[i] += q[i - 1];
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
