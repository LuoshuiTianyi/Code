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
int n;
LL ans1, ans2;
int a[Max_n], sum[2];
int main() {
#ifndef ONLINE_JUDGE
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
#endif
  n = read();
  int now = 0;
  sum[0] = 1;
  for (int i = 1; i <= n; i++) {
    a[i] = read();
    if (a[i] < 0) now ^= 1;
    ans1 += sum[now ^ 1], ans2 += sum[now]++;
  }
  cout << ans1 << " " << ans2;
}
