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
int a1, a2, k1, k2, n;
int main() {
#ifndef ONLINE_JUDGE
  freopen("A.in", "r", stdin);
  freopen("A.out", "w", stdout);
#endif
  a1 = read(), a2 = read(), k1 = read(), k2 = read(), n = read();
  if (n <= a1 * (k1 - 1) + a2 * (k2 - 1))
    cout << "0 ";
  else
    cout << min(a1 + a2, n - a1 * (k1 - 1) - a2 * (k2 - 1)) << " ";
  if (k1 > k2) swap(k1, k2), swap(a1, a2);
  int tmp = n, ans = 0;
  ans += min(a1, n / k1);
  tmp -= ans * k1;
  ans += min(a2, tmp / k2);
  cout << ans;
}
