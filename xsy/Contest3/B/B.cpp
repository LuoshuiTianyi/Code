#include <cstdio>
#include <cstring>
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
int n, Res;
int f[65][2][3];
LL m, N, a[Max_n], b[Max_n];
bool res[3];
inline bool check(LL x, LL y) {
  bool ans = 0;
  for (int i = 1; i <= n; i++) {
    LL M = b[i] - y, N = x - a[i];
    if (M < 0 || M < 0) continue;
    ans ^= ((N & M) == N);
  }
  return ans;
}
void DP(int Res) {
  memset(f, 0, sizeof(f));
  f[63][1][Res] = 1;
  for (int i = 63; i > 0; i--)
    for (int j = 0; j < 3; j++)
      for (int l = 0; l < 2; l++)
        for (int k = 0; k <= (m >> (i - 1) & 1); k++) {
          if (l && k > (N >> (i - 1) & 1)) continue;
          f[i - 1][l && k][(j << 1 | k) % 3] ^= f[i][l][j];
        }
  //  if (!(m >> (i - 1) & 1)) {
  //    for (int j = 0; j < 3; j++) {
  //      if (f[i][0][j]) f[i - 1][0][(j << 1) % 3] ^= 1;
  //      if (f[i][1][j])
  //        if (N >> (i - 1) & 1)
  //          f[i - 1][0][(j << 1) % 3] ^= 1;
  //        else
  //          f[i - 1][1][(j << 1) % 3] ^= 1;
  //    }
  //  } else {
  //    for (int j = 0; j < 3; j++) {
  //      if (f[i][0][j])
  //        f[i - 1][0][(j << 1) % 3] ^= 1, f[i - 1][0][(j << 1 | 1) % 3] ^= 1;
  //      if (f[i][1][j])
  //        if (N >> (i - 1) & 1)
  //          f[i - 1][0][(j << 1) % 3] ^= 1, f[i - 1][1][(j << 1 | 1) % 3] ^= 1;
  //        else
  //          f[i - 1][1][(j << 1) % 3] ^= 1;
  //    }
  //  }
  for (int i = 0; i < 3; i++)
    res[i] ^= f[0][0][i] ^ f[0][1][i];
}
inline void work(LL L, LL R, LL a, LL b) {
  m = b + 4, N = R - a;
  if (N < 0) return;
  DP(((a % 3) + 3) % 3);
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
#endif
  n = read();
  for (int i = 1; i <= n; i++) a[i] = read(), b[i] = read();
  m = 3, N = 2, Res = 0;
  // cout << DP(2, 1, 0);
  // for (int i = 1; i <= n; i++) {
  // work(-3, -1, -3, -1);
  // cout << res[0] << " " << res[1] << " " << res[2] << endl;
  //}
  LL l = -inf, r = inf;
  while (l != r) {
    LL mid = (l + r) >> 1;
    res[0] = res[1] = res[2] = 0;
    for (int i = 1; i <= n; i++) work(l, mid, a[i], b[i]);
    if (res[0] || res[1] || res[2])
      r = mid;
    else
      l = mid + 1;
  }
  LL L = l, R = l;
  // cout << check(l, -lim) << endl;
  for (int k = 63; ~k; k--)
    if (check(L - (1ll << k), -lim)) L -= (1ll << k);
  for (int k = 63; ~k; k--)
    if (check(R + (1ll << k), -lim)) R += (1ll << k);
  cout << L << " " << -lim + R - L;
}
