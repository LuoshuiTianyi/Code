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
const int Max_n = 1e4 + 5;
const LL Inf = 1e17;
int n;
LL a[Max_n], b[Max_n];
bool check(LL x, LL y) {
  bool ans = 0;
  for (int i = 1; i <= n; i++) {
    LL m = b[i] - y, n = x - a[i];
    if (m < n || m < 0) continue;
    ans ^= ((n & m) == n);
  }
  return ans;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
#endif
  n = read();
  for (int i = 1; i <= n; i++) a[i] = read(), b[i] = read();
  cout << check(-1, 0);
}
