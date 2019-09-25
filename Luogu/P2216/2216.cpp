#include <cstdio>
#include <iostream>
using namespace std;
int n, m, x, a[1001][1001], maxx[1001][1001][11], minn[1001][1001][11], top,
    ans = 2e9;
int main() {
  freopen("2216.in", "r", stdin);
  freopen("2216.out", "w", stdout);
  cin >> n >> m >> x;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      scanf("%d", &a[i][j]);
      minn[i][j][0] = maxx[i][j][0] = a[i][j];
    }
  for (int k = 1; k <= 10; k++)
    for (int i = 1; i + (1 << (k - 1)) <= n; i++)
      for (int j = 1; j + (1 << (k - 1)) <= m; j++) {
        maxx[i][j][k] =
            max(maxx[i][j][k - 1],
                max(maxx[i + (1 << (k - 1))][j][k - 1],
                    max(maxx[i][j + (1 << (k - 1))][k - 1],
                        maxx[i + (1 << (k - 1))][j + (1 << (k - 1))][k - 1])));
        minn[i][j][k] =
            min(minn[i][j][k - 1],
                min(minn[i + (1 << (k - 1))][j][k - 1],
                    min(minn[i][j + (1 << (k - 1))][k - 1],
                        minn[i + (1 << (k - 1))][j + (1 << (k - 1))][k - 1])));
      }
  while ((1 << (top + 1)) < x)
    top++;
  for (int i = 1; i <= n - x + 1; i++)
    for (int j = 1; j <= m - x + 1; j++) {
      ans = min(
          ans,
          max(maxx[i][j][top],
              max(maxx[i + x - (1 << top)][j][top],
                  max(maxx[i][j + x - (1 << top)][top],
                      maxx[i + x - (1 << top)][j + x - (1 << top)][top]))) -
              min(minn[i][j][top],
                  min(minn[i + x - (1 << top)][j][top],
                      min(minn[i][j + x - (1 << top)][top],
                          minn[i + x - (1 << top)][j + x - (1 << top)][top]))));
    }
  cout << ans;
}
