#include <cstdio>
#include <iostream>
using namespace std;
int n, ls[20001], rs[20001];
long long f[42][42][42], tmp[42][42][42], a[20001], b[20001], c[20001];
void Save(int x, int A, int B) {
  for (int i = 0; i <= A + 1; i++)
    for (int j = 0; j <= B; j++)
      tmp[x][i][j] = f[x][i][j];
}
void DP(int x, int deep, int A, int B) {
  if (x < 0) {
    for (int i = 0; i <= A; i++)
      for (int j = 0; j <= B; j++)
        f[deep][i][j] = c[-x] * (a[-x] + i) * (b[-x] + j);
    return;
  }
  DP(ls[x], deep + 1, A + 1, B);
  Save(deep + 1, A + 1, B);
  DP(rs[x], deep + 1, A, B + 1);
  for (int i = 0; i <= A; i++)
    for (int j = 0; j <= B; j++)
      f[deep][i][j] = min(tmp[deep + 1][i + 1][j] + f[deep + 1][i][j],
                          f[deep + 1][i][j + 1] + tmp[deep + 1][i][j]);
}
int main() {
  freopen("4438.in", "r", stdin);
  freopen("4438.out", "w", stdout);
  cin >> n;
  for (int i = 1; i < n; i++)
    scanf("%d%d", &ls[i], &rs[i]);
  for (int i = 1; i <= n; i++)
    scanf("%lld%lld%lld", &a[i], &b[i], &c[i]);
  DP(1, 1, 0, 0);
  cout << f[1][0][0];
}
