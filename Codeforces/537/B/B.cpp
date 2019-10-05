#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
int n, K, m;
long long a[100001];
double ans;
int main() {
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
  cin >> n >> K >> m;
  for (int i = 1; i <= n; i++)
    scanf("%lld", &a[i]);
  sort(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++)
    a[i] += a[i - 1];
  for (int i = 0; i <= min(n, m); i++) {
    long long sum = a[n] - a[i] + min(1ll * (n - i) * K, 1ll * m - i);
    ans = max(ans, sum * 1.0 / (1ll * (n - i)));
  }
  printf("%.20f", ans);
}
