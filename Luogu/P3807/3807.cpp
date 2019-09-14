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
int Lucas(int n, int m) {
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("3807.in", "r", stdin);
  freopen("3807.out", "w", stdout);
#endif
  T = read();
  while (T--) {
    n = read(), m = read(), mod = read();
    cout << Lucas(n + m, n) << endl;
  }
}
