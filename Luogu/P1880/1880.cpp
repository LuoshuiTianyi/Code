#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n, a[101], fmax[201][101], posi[201][101], fmin[201][101], maxans, minans;
int main() {
  freopen("1880.in", "r", stdin);
  freopen("1880.out", "w", stdout);
  cin >> n;
  memset(fmin, 0x7f, sizeof(fmin));
  minans = 2e9;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    a[i + n] = a[i];
  }
  for (int i = 1; i <= 2 * n; i++)
    a[i] += a[i - 1], fmin[i][i] = 0, posi[i][i] = i;
  for (int i = 1; i < n; i++)
    for (int j = 1; j <= 2 * n - i; j++) {
      fmax[j][j + i] =
          max(fmax[j][j + i - 1], fmax[j + 1][j + i]) + a[j + i] - a[j - 1];
      for (int k = posi[j + 1][j + i]; k >= posi[j][j + i - 1]; k--)
        if (fmin[j][j + i] >
            0ll + fmin[j][k] + fmin[k + 1][j + i] + a[j + i] - a[j - 1])
          fmin[j][j + i] =
              fmin[j][k] + fmin[k + 1][j + i] + a[j + i] - a[j - 1],
                      posi[j][j + i] = k;
    }
  for (int i = 1; i <= n; i++) {
    minans = min(minans, fmin[i][i + n - 1]);
    maxans = max(maxans, fmax[i][i + n - 1]);
  }
  cout << minans << endl;
  cout << maxans;
}
