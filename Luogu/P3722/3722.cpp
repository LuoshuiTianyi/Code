#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
#define ls (o << 1)
#define rs ((o << 1) + 1)
#define mid ((l + r) >> 1)
int n, m, p1, p2, a[200001], ql[200001], qr[200001];
int top, L, R, x, stack[200001], rr[200001], ll[200001];
long long ans, sum[800005], adv[800005], sum1[200001], sum2[200001];
vector<int> Mount[5][200005];
void pushdown(int o, int l, int r) {
  adv[ls] += adv[o], adv[rs] += adv[o];
  sum[ls] += 1ll * (mid - l + 1) * adv[o];
  sum[rs] += 1ll * (r - mid) * adv[o];
  adv[o] = 0;
}
void add(int o, int l, int r) {
  if (L > R)
    return;
  if (l >= L && r <= R) {
    sum[o] += 1ll * (r - l + 1) * x, adv[o] += x;
    return;
  }
  pushdown(o, l, r);
  if (mid >= L)
    add(ls, l, mid);
  if (mid < R)
    add(rs, mid + 1, r);
  sum[o] = sum[ls] + sum[rs];
}
void query(int o, int l, int r) {
  if (l >= L && r <= R) {
    ans += sum[o];
    return;
  }
  pushdown(o, l, r);
  if (mid >= L)
    query(ls, l, mid);
  if (mid < R)
    query(rs, mid + 1, r);
  sum[o] = sum[ls] + sum[rs];
}
void Add(int l, int r, int w) {
  L = l, R = r, x = w;
  add(1, 0, n);
}
void Query(int l, int r) {
  L = l, R = r, ans = 0;
  query(1, 0, n);
}
int main() {
  freopen("3722.in", "r", stdin);
  freopen("3722.out", "w", stdout);
  cin >> n >> m >> p1 >> p2;
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  stack[top = 0] = 0;
  for (int i = 1; i <= n; i++) {
    while (top > 0 && a[stack[top]] < a[i])
      top--;
    ll[i] = stack[top], stack[++top] = i;
  }
  stack[top = 0] = n + 1;
  for (int i = n; i >= 1; i--) {
    while (top > 0 && a[stack[top]] < a[i])
      top--;
    rr[i] = stack[top], stack[++top] = i;
  }
  for (int i = 1; i <= n; i++) {
    Mount[1][rr[i]].push_back(i);
    Mount[2][ll[i]].push_back(i);
  }
  int l, r;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &ql[i], &qr[i]);
    sum2[i] += 1ll * (qr[i] - ql[i]) * p1;
    Mount[3][ql[i] - 1].push_back(i);
    Mount[4][qr[i]].push_back(i);
  }
  for (int i = 1; i <= n; i++) {
    for (int j = 0, limit = Mount[1][i].size(); j < limit; j++) {
      int to = Mount[1][i][j];
      Add(ll[to], ll[to], p1);
      Add(ll[to] + 1, to - 1, p2);
    }
    for (int j = 0, limit = Mount[2][i].size(); j < limit; j++) {
      int to = Mount[2][i][j];
      Add(to + 1, rr[to] - 1, p2);
    }
    for (int j = 0, limit = Mount[3][i].size(); j < limit; j++) {
      int to = Mount[3][i][j];
      Query(ql[to], qr[to]);
      sum1[to] = ans;
    }
    for (int j = 0, limit = Mount[4][i].size(); j < limit; j++) {
      int to = Mount[4][i][j];
      Query(ql[to], qr[to]);
      sum2[to] += ans;
    }
  }
  for (int i = 1; i <= m; i++)
    printf("%lld\n", sum2[i] - sum1[i]);
}
