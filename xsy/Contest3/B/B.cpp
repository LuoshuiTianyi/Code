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
int f[64][2][3];
LL m, N, a[Max_n], b[Max_n];
bool res[3];
bool check(LL x, LL y) {
  bool ans = 0;
  for (int i = 1; i <= n; i++) {
    LL M = b[i] - y, N = x - a[i];
    if (M < N || M < 0 || M < 0) continue;
    ans ^= ((N & M) == N);
  }
  return ans;
}
bool DP(int len, bool lim, int res) {
  if (!len) return res == Res;
  int &dp = f[len][lim][res];
  if (dp != -1) return dp;
  dp = 0;
  for (int i = 0; i <= (m & (1ll << len - 1)); i++) {
    if (lim && i > (N & (1ll << len - 1))) continue;
    dp ^= DP(len - 1, lim && (i == (N & (1ll << len - 1))), (res << 1 | i) % 3);
  }
  return dp;
}
void work(LL L, LL R, LL a, LL b) {
  m = b;
  cout << m << endl;
  for (Res = 0; Res < 3; Res++) {
    N = R - a, memset(f, -1, sizeof(f));
    res[Res] ^= DP(63, 1, 0);
    cout << N << " " << Res << " " << res[Res] << endl;
    if (L > a) {
      N = L - a - 1, memset(f, -1, sizeof(f));
      res[Res] ^= DP(63, 1, 0);
      cout << N << " " << Res << " " << res[Res] << endl;
    }
  }
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
#endif
  n = read();
  for (int i = 1; i <= n; i++) a[i] = read(), b[i] = read();
  res[0] = res[1] = res[2] = 0;
  work(0, 0, -2, 2);
  cout << res[0] << " " << res[1] << " " << res[2];
  //for (int i = 1; i <= n; i++) {
  //  work(0, 0, a[i], b[i]);
  //  for (int j = 0; j < 3; j++) cout << res[j] << " ";
  //  cout << endl;
  //}
  //LL l = -inf, r = inf, ans;
  //while (l != r) {
  //  LL mid = l + r >> 1;
  //  res[0] = res[1] = res[2] = 0;
  //  for (int i = 1; i <= n; i++) work(l, mid, a[i], b[i]);
  //  if (res[1] || res[2] || res[0])
  //    r = mid;
  //  else
  //    l = mid + 1;
  //}
  //LL L = l, R = l;
  //for (int k = 63; ~k; k--)
  //  if (check(L - (1ll << k), -lim)) L -= (1ll << k);
  //for (int k = 63; ~k; k--)
  //  if (check(R + (1ll << k), -lim)) R += (1ll << k);
  //cout << L << " " << -lim + R - L;
}
