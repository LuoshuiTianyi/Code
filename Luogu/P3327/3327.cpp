#include <cstdio>
#include <iostream>
using namespace std;
int T, n, m;
int cntp, pri[50001];
long long ans, mu[50001], f[50001];
bool vis[50001];
void init() {
  mu[1] = 1;
  for (int i = 2; i <= 50000; i++) {
    if (!vis[i])
      pri[++cntp] = i, mu[i] = -1;
    for (int j = 1; j <= cntp && pri[j] * i <= 50000; j++) {
      vis[pri[j] * i] = true;
      if (!(i % pri[j]))
        break;
      mu[pri[j] * i] = -mu[i];
    }
  }
  for (int i = 1; i <= 50000; i++)
    mu[i] += mu[i - 1];
  for (int i = 1; i <= 50000; i++)
    for (int l = 1, r; l <= i; l = r + 1) {
      r = i / (i / l);
      f[i] += 1ll * (r - l + 1) * (i / l);
    }
}
int main() {
  freopen("3327.in", "r", stdin);
  freopen("3327.out", "w", stdout);
  cin >> T;
  init();
  while (T--) {
    scanf("%d%d", &n, &m);
    if (n > m)
      swap(n, m);
    ans = 0;
    for (int l = 1, r; l <= n; l = r + 1) {
      r = min(n / (n / l), m / (m / l));
      ans += 1ll * (mu[r] - mu[l - 1]) * f[n / l] * f[m / l];
    }
    printf("%lld\n", ans);
  }
}
