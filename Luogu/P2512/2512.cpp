#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
int n, a[1000001], c[1000001];
long long tot, ans, aver;
int main() {
  freopen("2512.in", "r", stdin);
  freopen("2512.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), tot += a[i];
  aver = 1ll * tot / n;
  for (int i = 1; i < n; i++)
    c[i] = c[i - 1] + a[i] - aver;
  sort(c, c + n);
  long long line = c[n / 2];
  for (int i = 0; i < n; i++)
    ans += abs(line - c[i]);
  cout << ans;
}
