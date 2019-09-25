#include <cstdio>
#include <iostream>
using namespace std;
int n, m, mod = 1e9 + 7;
long long ksm(long long a, int n) {
  long long base = 1;
  while (n) {
    if (n % 2)
      base = base * a % mod;
    a = a * a % mod;
    n >>= 1;
  }
  return base;
}
int main() {
  cin >> n >> m;
  if (n > m)
    swap(n, m);
  if (n == 1)
    cout << ksm(2, m);
  if (n == 2)
    cout << 4ll * ksm(3, m - 1) % mod;
  if (n == 3)
    cout << 112ll * ksm(3, m - 3) % mod;
  if (n == 4)
    if (m == 4)
      cout << "912";
    else
      cout << 2688ll * ksm(3, m - 5) % mod;
  if (n == 5)
    if (m == 5)
      cout << "7136";
    else
      cout << 21321ll * ksm(3, m - 6) % mod;
  if (n == 6)
    if (m == 6)
      cout << "56768";
    else
      cout << 170112ll * ksm(3, m - 7) % mod;
  if (n == 7)
    if (m == 7)
      cout << "453504";
    else
      cout << 1360128ll * ksm(3, m - 8) % mod;
  if (n == 8)
    if (m == 8)
      cout << "3626752";
    else
      cout << 10879488ll * ksm(3, m - 9) % mod;
}
