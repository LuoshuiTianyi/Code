#include <cstdio>
#include <iostream>
using namespace std;
const int mod = 1e9 + 7;
int n, m, K, ans = 1, f[5001], s[5001], c[5001], cnt[26], Ans[5001];
char opt;
void Mod(int &x) { x -= x >= mod ? mod : 0; }
int ksm(int a, int b) {
  int base = 1;
  while (b) {
    if (b & 1)
      base = 1ll * base * a % mod;
    a = 1ll * a * a % mod;
    b >>= 1;
  }
  return base;
}
int main() {
  freopen("A.in", "r", stdin);
  freopen("A.out", "w", stdout);
  cin >> n >> m >> K;
  f[0] = 1;
  for (int i = 1; i <= n; i++)
    scanf("%d%d", &s[i], &c[i]);
  for (int j = 1; j <= K; j++)
    for (int i = 1; i <= n; i++)
      if (s[i] <= j)
        Mod(f[j] += f[j - s[i]]);
  for (int i = 1; i <= n; i++)
    Mod(Ans[c[i]] += f[K - s[i]]);
  for (int i = 1; i <= m; i++) {
    scanf("%s", &opt);
    cnt[opt - 'A']++;
  }
  for (int i = 0; i < 26; i++)
    if (cnt[i]) {
      int tot = 0;
      for (int j = 1; j <= n; j++)
        if (Ans[j])
          Mod(tot += ksm(Ans[j], cnt[i]));
      ans = 1ll * ans * tot % mod;
    }
  cout << ans;
}
