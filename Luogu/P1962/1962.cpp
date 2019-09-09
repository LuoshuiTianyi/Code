#include <cstdio>
#include <iostream>
using namespace std;
long long n, mod = 1e9 + 7, jz[3][3], ans[3], now[3][3], now2[3];
void Mod(long long &x) { x %= mod; }
long long ksm(long long x) {
  do {
    if (x % 2 == 1) {
      for (int i = 1; i <= 2; i++)
        for (int j = 1; j <= 2; j++)
          Mod(now2[i] += jz[i][j] * ans[j]);
      for (int i = 1; i <= 2; i++)
        ans[i] = now2[i], now2[i] = 0;
    }
    for (int i = 1; i <= 2; i++)
      for (int j = 1; j <= 2; j++)
        for (int k = 1; k <= 2; k++)
          Mod(now[i][j] += jz[i][k] * jz[k][j] % mod);
    for (int i = 1; i <= 2; i++)
      for (int j = 1; j <= 2; j++)
        jz[i][j] = now[i][j], now[i][j] = 0;
    x >>= 1;
  } while (x > 0);
  return ans[1];
}
int main() {
  freopen("1962.in", "r", stdin);
  freopen("1962.out", "w", stdout);
  cin >> n;
  ans[1] = 1, ans[2] = 1, jz[1][1] = 1, jz[2][1] = 1, jz[1][2] = 1;
  cout << ksm(n - 2);
}
