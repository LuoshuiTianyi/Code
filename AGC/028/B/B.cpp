#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
long long read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 1e5 + 5, mod = 1e9 + 7;
int n, ans;
int a[Max_n], inv[Max_n];
void Mod(int &x) { x %= mod; }
int main() {
#ifndef ONLINE_JUDGE
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
#endif
  n = read();
  for (int i = 1; i <= n; i++) a[i] = read();
  inv[1] = 1;
  for (int i = 2; i <= n; i++)
    inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
  for (int i = 2; i <= n; i++) Mod(inv[i] += inv[i - 1]);
  for (int i = 1; i <= n; i++)
    Mod(ans += 1ll * a[i] * (inv[i] + inv[n - i + 1] - 1) % mod);
  for (int i = 2; i <= n; i++) ans = 1ll * ans * i % mod;
  cout << ans;
}
