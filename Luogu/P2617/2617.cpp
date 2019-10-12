#include <cstdio>
#include <iostream>
using namespace std;
int n, m, sum, cnt, a[200001], c[200001], tmp[400001], Ans[200001];
char opt;
struct node {
  int type, x, y, k, tmp, id;
} q[400001], q1[400001], q2[400001];
void add(int k, int x) {
  for (int i = k; i <= n; i += i & -i)
    c[i] += x;
}
int query(int k) {
  int ans = 0;
  for (int i = k; i > 0; i -= i & -i)
    ans += c[i];
  return ans;
}
void Solve(int L, int R, int l, int r) {
  if (L > R)
    return;
  if (l == r) {
    for (int i = L; i <= R; i++)
      if (q[i].type == 3)
        Ans[q[i].id] = l;
    return;
  }
  int mid = (l + r) >> 1;
  for (int i = L; i <= R; i++) {
    if (q[i].type == 1 && q[i].y <= mid)
      add(q[i].x, 1);
    if (q[i].type == 2 && q[i].y <= mid)
      add(q[i].x, -1);
    if (q[i].type == 3)
      tmp[i] = query(q[i].y) - query(q[i].x - 1);
  }
  int len1 = 0, len2 = 0;
  for (int i = L; i <= R; i++) {
    if (q[i].type == 1 && q[i].y <= mid)
      add(q[i].x, -1);
    if (q[i].type == 2 && q[i].y <= mid)
      add(q[i].x, 1);
    if (q[i].type == 3) {
      if (q[i].tmp + tmp[i] > q[i].k - 1)
        q1[++len1] = q[i];
      else {
        q[i].tmp += tmp[i];
        q2[++len2] = q[i];
      }
    } else if (q[i].y <= mid)
      q1[++len1] = q[i];
    else
      q2[++len2] = q[i];
  }
  for (int i = 1; i <= len1; i++)
    q[L + i - 1] = q1[i];
  for (int i = 1; i <= len2; i++)
    q[L + len1 + i - 1] = q2[i];
  Solve(L, L + len1 - 1, l, mid);
  Solve(L + len1, R, mid + 1, r);
}
int main() {
  freopen("2617.in", "r", stdin);
  freopen("2617.out", "w", stdout);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    sum++;
    q[sum].type = 1, q[sum].x = i, q[sum].y = a[i];
  }
  for (int i = 1; i <= m; i++) {
    scanf("%s", &opt);
    if (opt == 'Q') {
      q[++sum].id = ++cnt;
      scanf("%d%d%d", &q[sum].x, &q[sum].y, &q[sum].k);
      q[sum].type = 3;
    } else {
      int A, B;
      scanf("%d%d", &A, &B);
      sum++;
      q[sum].type = 2, q[sum].x = A, q[sum].y = a[A];
      sum++;
      q[sum].type = 1, q[sum].x = A, q[sum].y = B;
      a[A] = B;
    }
  }
  Solve(1, sum, 0, 2e9);
  for (int i = 1; i <= cnt; i++)
    printf("%d\n", Ans[i]);
}
