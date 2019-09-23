#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>
using std::make_pair;
using std::max;
using std::min;
using std::pair;
using namespace std;
typedef long long ll;
const int N = 1e4 + 5;
int n;
ll x[N], y[N];
int res[3];
int dp[64][2][3];
inline void calc(ll c, ll x, ll y, ll r) {
  ll n = x - c;
  register int i, j, k;
  r -= y;
  if (r < 0) return res[0] = res[1] = res[2] = 0, void();
  memset(dp, 0, sizeof(dp));
  dp[63][1][0] = 1;
  for (i = 63; i > 0; i--)
    if (!(n >> (i - 1) & 1)) {
      for (j = 0; j < 3; j++) {
        if (dp[i][0][j]) dp[i - 1][0][(j * 2) % 3] ^= 1;
        if (dp[i][1][j]) {
          if (r >> (i - 1) & 1)
            dp[i - 1][0][(j * 2) % 3] ^= 1;
          else
            dp[i - 1][1][(j * 2) % 3] ^= 1;
        }
      }
    } else {
      for (j = 0; j < 3; j++) {
        if (dp[i][0][j]) {
          dp[i - 1][0][(j * 2) % 3] ^= 1;
          dp[i - 1][0][(j * 2 + 1) % 3] ^= 1;
        }
        if (dp[i][1][j]) {
          if (r >> (i - 1) & 1)
            dp[i - 1][0][(j * 2) % 3] ^= 1, dp[i - 1][1][(j * 2 + 1) % 3] ^= 1;
          else
            dp[i - 1][1][(j * 2) % 3] ^= 1;
        }
      }
    }
  y = (y % 3 + 3) % 3;
  res[y] = dp[0][0][0] ^ dp[0][1][0];
  res[(y + 1) % 3] = dp[0][0][1] ^ dp[0][1][1];
  res[(y + 2) % 3] = dp[0][0][2] ^ dp[0][1][2];
  return;
}
int lres[3], rres[3], mres[3];
inline ll epc(ll c) {
  int k;
  ll l = -1000000000000000000ll, r = 1000000000000000000ll, mid;
  register int i;
  rres[0] = rres[1] = rres[2] = 0;
  for (i = 1; i <= n; i++) {
    calc(c, x[i], y[i], r);
    rres[0] ^= res[0];
    rres[1] ^= res[1];
    rres[2] ^= res[2];
  }
  lres[0] = lres[1] = lres[2] = 0;
  for (i = 0; i < 3; i++)
    if (rres[i]) {
      k = i;
      break;
    }
  while (l < r) {
    mid = (l + r) >> 1;
    mres[0] = mres[1] = mres[2] = 0;
    for (i = 1; i <= n; i++) {
      calc(c, x[i], y[i], mid);
      mres[0] ^= res[0];
      mres[1] ^= res[1];
      mres[2] ^= res[2];
    }
    if (mres[k] ^ lres[k])
      r = mid, memcpy(rres, mres, sizeof(int) * 3);
    else
      l = mid + 1, memcpy(lres, mres, sizeof(int) * 3);
  }
  return l;
}
inline bool light(ll x, ll y) {
  int res = 0;
  ll xx, yy, n, m;
  register int i;
  for (i = 1; i <= ::n; i++) {
    xx = ::x[i];
    yy = ::y[i];
    n = xx - x;
    m = y - yy;
    if (m < 0 || m > n) continue;
    res ^= ((n | m) == n);
  }
  return res;
}
inline void solve(ll c, pair<ll, ll> &a) {
  ll k = epc(c), lk = k, rk = k;
  //  fprintf(stderr,"%lld\n",k);
  register ll i;
  for (i = 1ll << 62; i; i >>= 1)
    if (light(c, lk - i)) lk -= i;
  for (i = 1ll << 62; i; i >>= 1)
    if (light(c, rk + i)) rk += i;
  a.first = c + (rk - lk);
  //cout << rk << endl;
  a.second = lk;
  return;
}
signed main() {
  freopen("B.in", "r", stdin);
  freopen("B.ans", "w", stdout);
  pair<ll, ll> a;
  register int i;
  scanf("%d", &n);
  for (i = 1; i <= n; i++) scanf("%lld%lld", &x[i], &y[i]);
  solve(-100000000000000000, a);
  long long c = -100000000000000000;
  printf("%lld %lld", a.first, a.second);
  return 0;
}
