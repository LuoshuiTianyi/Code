#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<int, ll> pii;
#define x first
#define y second
#define pb push_back
const int MAXN = 200005;

int n, m, cnt;
pii a[MAXN];
bool avis[MAXN];
struct Range {
  int l, r, type;
  ll val;
  Range() {}
  Range(int l, int r, int type, ll val) : l(l), r(r), type(type), val(val) {}
} b[MAXN];

int f[2][MAXN], wh[2][MAXN], res[MAXN];
vector<int> str[2][MAXN];
bool check(ll s, int l, int r) {
  if (s <= 0) return !s && r - l + 1 >= 0;
  ll L = 1, R = r - l + 1, mid, ans = 0;
  while (L <= R) {
    mid = (L + R) >> 1;
    if ((l + l + mid - 1) * mid <= s * 2)
      ans = mid, L = mid + 1;
    else
      R = mid - 1;
  }
  return s * 2 <= (r + r - ans + 1) * ans;
}
void modify(ll s, int l, int r, vector<int> &tar, int start) {
  ll L = 1, R = r - l + 1, mid, ans = 0;
  while (L <= R) {
    mid = (L + R) >> 1;
    if ((l + l + mid - 1) * mid <= s * 2)
      ans = mid, L = mid + 1;
    else
      R = mid - 1;
  }
  for (int i = l; i <= r; i++)
    if (ans && (i + i + ans - 2) * (ans - 1) <= (s - i) * 2 &&
        (s - i) * 2 <= (r + r - ans + 2) * (ans - 1)) {
      --ans, s -= i;
      tar.pb(1);
    } else
      tar.pb(0);
}
void update(int i, int ti, int ti_1, int pos, ll d) {
  if (pos <= f[ti][i]) return;
  str[ti][i].clear();
  f[ti][i] = pos;
  wh[ti][i] = ti_1;
  str[ti][i].pb(1);
  for (int j = f[ti][i] + 1; j <= b[i].r; j++) str[ti][i].pb(0);
  modify(d - f[ti][i], b[i].r + 1, f[ti_1][i - 1] - 1, str[ti][i], f[ti][i]);
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("E.in", "r", stdin);
  freopen("E.ans", "w", stdout);
#endif
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    ll y;
    scanf("%lld", &y);
    if (!y) continue;
    a[++m] = make_pair(n - i + 1, y);
    avis[n - i + 1] = 1;
  }
  if (!m) {
    for (int i = 1; i <= n; i++) putchar('0');
    return 0;
  }
  sort(a + 1, a + m + 1);
  b[cnt = 1] = Range(a[m].x, a[m].x, 2, a[m].y);
  for (int i = m - 1; i; i--) {
    if (a[i].y == a[i + 1].y)
      b[cnt].l = a[i].x, b[cnt].type = 0;
    else if (a[i].y == a[i + 1].y - 1)
      b[cnt].l = a[i].x, b[cnt].type = 1, b[cnt].val--;
    else
      b[++cnt] = Range(a[i].x, a[i].x, 2, a[i].y);
  }
  b[cnt + 1] = Range(-1, -1, 0, 0);
  bool error = 0;
  f[0][0] = -1;
  f[1][0] = n + 1;
  for (int i = 1; i <= cnt; i++) {
    f[0][i] = f[1][i] = -1;
    for (int t = 0; t <= 1; t++)
      if (f[t][i - 1] > b[i].r) {
        if (b[i].type == 0 || b[i].type == 2) {
          ll d = (b[i].val - 1) - (b[i - 1].val - 1 + t);
          int pos = -1;
          for (int j = min(b[i].l - 1ll, d); j > b[i + 1].r; --j)
            if (check(d - j, b[i].r + 1, f[t][i - 1] - 1)) {
              pos = j;
              break;
            }
          update(i, 0, t, pos, d);
        }
        if (b[i].type == 1 || b[i].type == 2) {
          ll d = b[i].val - (b[i - 1].val - 1 + t);
          if (check(d - b[i].l, b[i].r + 1, f[t][i - 1] - 1))
            update(i, 1, t, b[i].l, d);
        }
      }
    if (f[0][i] < 0 && f[1][i] < 0 && i == cnt && !b[i].type) error = 1;
  }
  if (error) {
    for (int t = 0; t <= 1; t++)
      if (f[t][cnt - 1] > b[cnt].r) {
        ll d = (b[cnt].val - 1) - (b[cnt - 1].val - 1 + t);
        int pos = -1;
        for (int j = min((ll)b[cnt].r, d); j >= b[cnt].l; --j) {
          if (avis[j]) continue;
          if (check(d - j, b[cnt].r + 1, f[t][cnt - 1] - 1)) {
            pos = j;
            break;
          }
        }
        update(cnt, 0, t, pos, d);
      }
  }
  int cur = (f[1][cnt] > 0);
  for (int i = 1; i < f[cur][cnt]; i++) res[i] = 0;
  for (int i = cnt; i > 0; i--) {
    for (int j = 0; j < (int)str[cur][i].size(); j++)
      res[j + f[cur][i]] = str[cur][i][j];
    cur = wh[cur][i];
  }
  for (int i = n; i > 0; i--) putchar(res[i] + '0');
  return 0;
}
