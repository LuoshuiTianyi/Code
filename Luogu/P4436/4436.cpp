#include <cstdio>
#include <iostream>
using namespace std;
#define ls (o << 1)
#define rs ((o << 1) + 1)
#define mid ((l + r) >> 1)
int n, m, Q, key[1000001], ll[1000001], rr[1000001], l[1000001], r[1000001];
int now, top, stack[1000001];
int L, R, X, ans, maxx[4000001];
void build(int o, int l, int r) {
  if (l == r) {
    maxx[o] = key[l];
    return;
  }
  build(ls, l, mid), build(rs, mid + 1, r);
  maxx[o] = max(maxx[ls], maxx[rs]);
}
void query(int o, int l, int r) {
  if (ans)
    return;
  if (l == r) {
    ans = l;
    return;
  }
  if (mid < R && maxx[rs] > X)
    query(rs, mid + 1, r);
  if (mid >= L && maxx[ls] > X)
    query(ls, l, mid);
}
bool pd(int x) {
  L = ll[x], R = l[x] - 1, X = r[x], ans = 0;
  query(1, 1, n);
  l[x] = !ans ? ll[x] : ans + 1;
  return key[r[x]] >= l[x] && key[r[x]] <= r[x];
}
int main() {
  freopen("4436.in", "r", stdin);
  freopen("4436.out", "w", stdout);
  cin >> n >> m >> Q;
  int x, t, now, tp;
  for (int i = 1; i <= m; i++)
    scanf("%d", &x), scanf("%d", &key[x]);
  now = 1, tp = 1;
  for (int i = 1; i <= n; i++) {
    if (key[i - 1]) {
      now = i;
      if (key[i - 1] < i)
        tp = i;
    }
    ll[i] = tp, l[i] = now;
  }
  now = n, tp = n;
  for (int i = n; i >= 1; i--) {
    if (key[i]) {
      now = i;
      if (key[i] > i)
        tp = i;
    }
    rr[i] = tp, r[i] = now;
  }
  build(1, 1, n);
  stack[++top] = n;
  for (int i = n; i >= 1; i--) {
    stack[++top] = r[i];
    while (pd(i))
      r[i] = stack[--top];
  }
  while (Q--) {
    scanf("%d%d", &x, &t);
    printf(t >= l[x] && t <= r[x] ? "YES\n" : "NO\n");
  }
}
