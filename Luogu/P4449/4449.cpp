#include <cstdio>
#include <iostream>
using namespace std;
const int mod = 1e9 + 7;
int T, K, n, m, ans;
int cntp, pri[5000001], mu[5000001], f[5000001];
bool vis[5000001];
int ksm(int a) {
  int base = 1, b = K;
  while (b) {
    if (b & 1)
      base = 1ll * base * a % mod;
    a = 1ll * a * a % mod;
    b >>= 1;
  }
  return base;
}
void init() {
  mu[1] = 1;
  for (int i = 2; i <= 5000000; i++) {
    if (!vis[i])
      pri[++cntp] = i, mu[i] = -1;
    for (int j = 1; j <= cntp && pri[j] * i <= 5000000; j++) {
      vis[pri[i] * j] = true;
      if (!i % pri[j])
        break;
      mu[pri[j] * i] = -mu[j];
    }
  }
}
int main() {
  freopen("4449.in", "r", stdin);
  freopen("4449.out", "w", stdout);
  cin >> T >> K;
  init();
  while (T--) {
    ans = 0;
    scanf("%d%d", &n, &m);
    if (m <= n)
      swap(n, m);
    for (int i = 1, r; i <= n; i = r + 1) {
      r = min((n / i), (m / i));
      ans = (ans + 1ll * (f[r] - f[i - 1]) * (n / i) * (m / i) % mod) % mod;
    }
    printf("%d\n", ans);
  }
}
