#include <cstdio>
#include <iostream>
using namespace std;
int n, mod, f[2][4201], ans;
void Mod(int &x) { x %= mod; }
int main() {
  freopen("2467.in", "r", stdin);
  freopen("2467.out", "w", stdout);
  cin >> n >> mod;
  f[0][2] = 1;
  for (int i = 3; i <= n; i++)
    for (int j = 2; j <= i; j++)
      Mod(f[i % 2][j] = f[i % 2][j - 1] + f[(i - 1) % 2][i - j + 1]);
  for (int i = 2; i <= n; i++)
    Mod(ans += f[n % 2][i]);
  Mod(ans <<= 1);
  cout << ans;
}
