#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
long long read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 1e5 + 5;
int n, m, ans;
int tx, ty, sx, sy, a[Max_n], b[Max_n];
int r[Max_n], w[Max_n];
long long sum, n1, n2;
void Max(long long &a, long long b) { a = a > b ? a : b; }
void chkmax(int r, int w) {
  Max(n1, sum);
  Max(n2, sum - (r < sx && w < sy));
}
bool chk(int x) {
  if (tx + ty <= x) return 1;
  int pos = m;
  sum = n1 = n2 = 0;
  for (int i = 1; i <= m; i++) w[i] = n;
  for (int i = 1; i <= n; i++) {
    while (pos >= 1 && a[i] + b[pos] > x) sum += n - (w[pos--] = i - 1);
    r[i] = pos;
  }
  for (int rl = 0, wl = 0; rl <= n; rl++) {
    sum += min(r[rl], wl);
    sum -= min(m - r[rl], m - wl);
    chkmax(rl, wl);
    while (wl <= m && rl + w[wl + 1] >= n) sum += rl + w[++wl] - n;
    chkmax(rl, wl);
  }
  return n1 == n2;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
#endif
  n = read(), m = read();
  for (int i = 1; i <= n; i++) a[i] = read();
  for (int i = 1; i <= m; i++) b[i] = read();
  tx = a[1], ty = b[1];
  sort(a + 1, a + n + 1);
  sort(b + 1, b + m + 1);
  for (int i = 1; i <= n; i++)
    if (a[i] == tx) sx = i;
  for (int i = 1; i <= m; i++)
    if (b[i] == ty) sy = i;
  int l = 2, r = tx + ty;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (chk(mid)) {
      ans = mid;
      r = mid - 1;
    } else
      l = mid + 1;
  }
  cout << ans;
}
