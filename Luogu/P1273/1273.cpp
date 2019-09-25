#include <cstdio>
#include <iostream>
using namespace std;
int n, m, size[3001], head[3001], nx[3001], to[3001], w[3001], cnt;
int f[3001][3001], money[3001];
void DP(int x) {
  if (x > n - m) {
    size[x] = 1;
    f[x][1] = money[x];
  }
  for (int i = head[x]; i; i = nx[i]) {
    DP(to[i]);
    size[x] += size[to[i]];
  }
  for (int i = head[x]; i; i = nx[i])
    for (int j = size[x]; j >= 1; j--)
      for (int k = 1; j - k >= 0; k++)
        f[x][j] = max(f[x][j], f[x][j - k] + f[to[i]][k] - w[i]);
}
int main() {
  freopen("1273.in", "r", stdin);
  freopen("1273.out", "w", stdout);
  cin >> n >> m;
  int sum;
  for (int i = 1; i <= n - m; i++) {
    cin >> sum;
    while (sum--) {
      cnt++;
      cin >> to[cnt] >> w[cnt];
      nx[cnt] = head[i];
      head[i] = cnt;
    }
  }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      f[i][j] = -1e9;
  for (int i = n - m + 1; i <= n; i++)
    cin >> money[i];
  DP(1);
  for (int i = m; i >= 0; i--)
    if (f[1][i] >= 0) {
      cout << i;
      return 0;
    }
}
