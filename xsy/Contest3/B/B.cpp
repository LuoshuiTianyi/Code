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
const LL lim = 1e17, inf = 1e18;
int n;
LL m, f[64][2][3], a[Max_n], b[Max_n];
LL DP(int len, bool lim, int res) {
  if (!len) return 1;
  
}
void work(LL L, LL R, LL a, LL b) {
  m = b + lim;
  memset(f, -1, sizeof(f));
  DP(63, 1, 0);
}
bool check(LL x, LL y) {
  bool ans = 0;
  for (int i = 1; i <= n; i++) {
    LL M = b[i] - y, N = x - a[i];
    if (M < N || M < 0 || M < 0) continue;
    ans ^= ((N & M) == N);
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
  LL l = -inf, r = inf, ans;
}
