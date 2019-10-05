#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n, m, fmax[1001][1001][2], fmin[1001][1001][2];
char a[1001][1001];
int main() {
  freopen("5003.in", "r", stdin);
  freopen("5003.out", "w", stdout);
  cin >> n >> m;
  swap(n, m);
  memset(fmin, 0x7f, sizeof(fmin));
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  fmin[1][1][0] = fmin[1][1][1] = 0;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if (a[i][j - 1] != '#')
        for (int k = 0; k < 2; k++) {
          fmax[i][j][k] =
              max(fmax[i - 1][j][k],
                  max(fmax[i - 1][j][(k + 1) % 2] + 1,
                      max(fmax[i][j - 1][k] + 1, fmax[i][j - 1][(k + 1) % 2])));
          fmin[i][j][k] =
              min(fmin[i - 1][j][k],
                  min(fmin[i - 1][j][(k + 1) % 2] + 1,
                      min(fmin[i][j - 1][k] + 1, fmin[i][j - 1][(k + 1) % 2])));
        }
  // if(fmax[n][m][0]==0&&fmax[n][m][1]==0)
  // cout<<"-1";
  // else
  cout << max(fmax[n][m][0], fmax[n][m][1]) << " "
       << min(fmin[n][m][0], fmin[n][m][1]);
}
