#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void read(int &x) {
  x = 0;
  ll w = 1;
  char ch = 0;
  while (ch < '0' || ch > '9') {
    ch = getchar();
    if (ch == '-') w = -1;
  }
  while (ch <= '9' && ch >= '0') {
    x = (x << 1ll) + (x << 3ll) + ch - '0';
    ch = getchar();
  }
}
const int N = 1005;
int n, m;
ll ans;
char s[N];
int a[N][N], mn[N][N], mn2[N][N];
int l[N][N], r[N][N];
int main() {
  read(n), read(m);
  for (int i = 1; i <= n; ++i) {
    scanf("%s", s + 1);
    for (int j = 1; j <= m; ++j) a[i][j] = s[j] - 'a' + 1;
  }
  for (int i = 1; i <= n; ++i) {
    int col = 0, pos = 0;
    for (int j = m; j; --j) {
      if (a[i][j] != col) pos = j, col = a[i][j];
      r[i][j] = mn[i][j] = mn2[i][j] = pos;
    }
  }
  for (int j = 1; j <= m; ++j) {
    int col = 0, pos = 0;
    for (int i = 1; i <= n; ++i) {
      if (a[i][j] != col)
        pos = i, col = a[i][j];
      else
        mn[i][j] = min(mn[i][j], mn[i - 1][j]);
      l[i][j] = pos;
    }
  }
  for (int j = 1; j <= m; ++j) {
    int col = 0, pos = 0;
    for (int i = n; i; --i) {
      if (a[i][j] != col)
        pos = i, col = a[i][j];
      else
        mn2[i][j] = min(mn2[i][j], mn2[i + 1][j]);
    }
  }
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j) {
      int now = i, len = i - l[i][j] + 1, flag = 1, val = m;
      for (int t = 1; t <= 2; ++t) {
        if (now - l[now][j] + 1 != len || !now) {
          flag = 0;
          break;
        }
        val = min(val, mn[now][j]), now = l[now][j] - 1;
      }
      if (flag && now && now - l[now][j] + 1 >= len) {
        val = min(val, mn2[now - len + 1][j]);
      } else
        flag = 0;
      if (flag && val >= j) ans += val - j + 1;
    }
  printf("%lld\n", ans);
  return 0;
}
