#include <cstdio>
#include <iostream>
using namespace std;
int T, n, m, cnt, pri[10000001], mu[10000001], sum[10000001];
bool vis[10000001];
void init() {
  mu[1] = 1;
  for (int i = 2; i <= 10000000; i++) {
    if (!vis[i])
      pri[++cnt] = i, mu[i] = -1;
    for (int j = 1; j <= cnt && pri[j] * i <= 10000000; j++) {
      vis[pri[j] * i] = true;
      if (!(i % pri[j]))
        break;
      mu[pri[j] * i] = -mu[i];
    }
  }
  for (int i = 1; i <= cnt; i++)
    for (int j = 1; j * pri[i] <= 10000000; j++)
      sum[j * pri[i]] += mu[j];
  for (int i = 1; i <= 10000000; i++)
    sum[i] += sum[i - 1];
}
int main() {
  freopen("2257.in", "r", stdin);
  freopen("2257.out", "w", stdout);
  init();
  cin >> T;
  while (T--) {
    long long ans = 0;
    scanf("%d%d", &n, &m);
    if (n > m)
      swap(n, m);
    for (int i = 1, r; i <= n; i = r + 1) {
      r = min(n / (n / i), m / (m / i));
      ans += 1ll * (sum[r] - sum[i - 1]) * (n / i) * (m / i);
    }
    printf("%lld\n", ans);
  }
}
