#include <cstdio>
#include <iostream>
using namespace std;
struct node {
  int type, l, r, x, d, tmp;
} q[50001], q1[50001], q2[50001];
int n, m, cntq;
long long c[2][50001], Ans[50001], tmp[50001];
void add(int k, long long x, int p) {
  for (int i = k; i <= n; i += i & -i)
    c[p][i] += x;
}
void Add(int k, long long x) { add(k, x, 0), add(k, 1ll * x * k, 1); }
long long query(int k, int p) {
  long long ans = 0;
  for (int i = k; i > 0; i -= i & -i)
    ans += c[p][i];
  return ans;
}
long long Query(int k) { return 1ll * (k + 1) * query(k, 0) - query(k, 1); }
void Solve(int L, int R, int l, int r) {
  if (L > R)
    return;
  if (l == r) {
    for (int i = L; i <= R; i++)
      if (q[i].type == 2)
        Ans[q[i].d] = l;
    return;
  }
  int mid = (l + r) >> 1;
  for (int i = L; i <= R; i++) {
    if (q[i].type == 1 && q[i].x >= mid)
      Add(q[i].l, 1ll), Add(q[i].r + 1, -1ll);
    if (q[i].type == 2)
      tmp[i] = Query(q[i].r) - Query(q[i].l - 1);
  }
  int len1 = 0, len2 = 0;
  for (int i = L; i <= R; i++) {
    if (q[i].type == 1)
      if (q[i].x >= mid) {
        Add(q[i].l, -1ll), Add(q[i].r + 1, 1ll);
        q2[++len2] = q[i];
      } else
        q1[++len1] = q[i];
    else if (q[i].tmp + tmp[i] >= q[i].x)
      q2[++len2] = q[i];
    else
      q[i].tmp += tmp[i], q1[++len1] = q[i];
  }
  for (int i = 1; i <= len1; i++)
    q[L + i - 1] = q1[i];
  for (int i = 1; i <= len2; i++)
    q[L + len1 + i - 1] = q2[i];
  Solve(L, L + len1 - 1, l, mid);
  Solve(L + len1, R, mid + 1, r);
}
int main() {
  freopen("3332.in", "r", stdin);
  freopen("3332.out", "w", stdout);
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d%d%d", &q[i].type, &q[i].l, &q[i].r, &q[i].x);
    if (q[i].type == 2)
      q[i].d = ++cntq;
  }
  Solve(1, m, 0, 6e4);
  for (int i = 1; i <= cntq; i++)
    printf("%lld\n", Ans[i] - 1);
}
