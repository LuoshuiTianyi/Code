#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
int n, size, Q, a[100001];
int minn[100001][18], pos[100001][18], Log[100001];
int top, ll[100001], rr[100001], stack[100001];
int L, R;
long long ans, Ans[100001], fr[100001], fl[100001];
struct node {
  int l, r, d;
} k[100001];
bool cmp(node a, node b) {
  return (a.l / size) == (b.l / size) ? a.r < b.r : (a.l / size) < (b.l / size);
}
int find(int l, int r) {
  if (l > r)
    return 0;
  if (l == r)
    return pos[l][0];
  int x = Log[r - l], p;
  return minn[l][x] > minn[r - (1 << x) + 1][x] ? pos[r - (1 << x) + 1][x]
                                                : pos[l][x];
}
void init() {
  cin >> n >> Q;
  size = sqrt(n);
  int now = 2;
  for (int i = 2; i <= (int)1e5; i++) {
    Log[i] = Log[i - 1];
    if (i == now)
      Log[i]++, now <<= 1;
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    minn[i][0] = a[i], pos[i][0] = i;
  }
  for (int i = 1; i <= Q; i++)
    scanf("%d%d", &k[i].l, &k[i].r), k[i].d = i;
  sort(k + 1, k + Q + 1, cmp);
  for (int j = 1; j <= 17; j++)
    for (int i = 1; i <= n - (1 << j) + 1; i++) {
      pos[i][j] = pos[i][j - 1],
      minn[i][j] = min(minn[i][j - 1], minn[i + (1 << (j - 1))][j - 1]);
      if (minn[i][j] != minn[i][j - 1])
        pos[i][j] = pos[i + (1 << (j - 1))][j - 1];
    }
  stack[top = 0] = 0;
  for (int i = 1; i <= n; i++) {
    while (top && a[stack[top]] >= a[i])
      top--;
    ll[i] = stack[top], stack[++top] = i;
  }
  for (int i = 1; i <= n; i++)
    fl[i] = fl[ll[i]] + 1ll * (i - ll[i]) * a[i];
  stack[top = 0] = n + 1;
  for (int i = n; i >= 1; i--) {
    while (top && a[stack[top]] >= a[i])
      top--;
    rr[i] = stack[top], stack[++top] = i;
  }
  for (int i = n; i >= 1; i--)
    fr[i] = fr[rr[i]] + 1ll * (rr[i] - i) * a[i];
}
long long workr(int x) {
  int p = find(L, x);
  return 1ll * a[p] * (p - L + 1) + fl[x] - fl[p];
}
long long workl(int x) {
  int p = find(x, R);
  return 1ll * a[p] * (R - p + 1) + fr[x] - fr[p];
}
void solve() {
  L = k[1].l, R = k[1].l - 1;
  for (int i = 1; i <= Q; i++) {
    while (R < k[i].r)
      ans += workr(++R);
    while (L > k[i].l)
      ans += workl(--L);
    while (R > k[i].r)
      ans -= workr(R--);
    while (L < k[i].l)
      ans -= workl(L++);
    Ans[k[i].d] = ans;
  }
}
int main() {
  freopen("3246.in", "r", stdin);
  freopen("3246.out", "w", stdout);
  init();
  solve();
  for (int i = 1; i <= Q; i++)
    printf("%lld\n", Ans[i]);
}
