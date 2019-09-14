#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define go(x, i, v) for (int i = hd[x], v = to[i]; i; v = to[i = nx[i]])
#define inline __inline__ __attribute__((always_inline))
inline LL read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 2e5 + 5;
int T;
int n, m, mod;
int fac[Max_n], ifac[Max_n];
int ksm(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % mod)
    if (b & 1) res = 1ll * res * a % mod;
  return res;
}
void Init() {
  fac[0] = 1;
  for (int i = 1; i <= n + m; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
  ifac[n + m] = ksm(fac[n + m], mod - 2);
  for (int i = n + m - 1; ~i; i--) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod;
}
int C(int n, int m) {
  return n < m ? 0 : 1ll * fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
int Lucas(int n, int m) {
  if (!m) return 1;
  return 1ll * C(n % mod, m % mod) * Lucas(n / mod, m / mod) % mod;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("3807.in", "r", stdin);
  freopen("3807.out", "w", stdout);
#endif
  T = read();
  while (T--) {
    n = read(), m = read(), mod = read();
    Init();
    cout << Lucas(n + m, n) << endl;
  }
}
