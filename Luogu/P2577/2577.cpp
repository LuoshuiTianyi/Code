#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
struct node {
  int a, b;
} k[201];
int n, f[201][40001], q[201], ans = 2e9;
bool cmp(node a, node b) { return a.b > b.b; }
int main() {
  freopen("2577.in", "r", stdin);
  freopen("2577.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++)
    cin >> k[i].a >> k[i].b;
  sort(k + 1, k + n + 1, cmp);
  for (int i = 1; i <= n; i++)
    q[i] = q[i - 1] + k[i].a;
  for (int i = 0; i <= 200; i++)
    for (int j = 0; j <= 40000; j++)
      f[i][j] = 2e9;
  f[0][0] = 0;
  for (int i = 1; i <= n; i++)
    for (int j = 0; j <= q[i]; j++) {
      if (j >= k[i].a)
        f[i][j] = min(f[i][j], max(f[i - 1][j - k[i].a], j + k[i].b));
      f[i][j] = min(f[i][j], max(f[i - 1][j], q[i] - j + k[i].b));
    }
  for (int i = 0; i <= q[n]; i++)
    ans = min(ans, f[n][i]);
  cout << ans;
}
