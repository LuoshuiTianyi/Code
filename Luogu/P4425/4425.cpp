#include <cstdio>
#include <iostream>
#define ls (o << 1)
#define rs ((o << 1) + 1)
#define mid ((l + r) >> 1)
using namespace std;
int n, m, p, a[100001];
int L, R, x, y, ans, maxx[400001], adv[400001];
int query(int o, int l, int r) {
  if (l == r)
    return maxx[o] > x ? x + l : 1e9;
  return maxx[rs] > x ? min(adv[o], query(rs, mid + 1, r)) : query(ls, l, mid);
}
void pushup(int o, int l, int r) {
  maxx[o] = max(maxx[ls], maxx[rs]);
  x = maxx[rs], adv[o] = query(ls, l, mid);
}
void add(int o, int l, int r) {
  if (l == r) {
    maxx[o] = a[l] - l;
    return;
  }
  if (mid >= L)
    add(ls, l, mid);
  if (mid < R)
    add(rs, mid + 1, r);
  pushup(o, l, r);
}
int main() {
  freopen("4425.in", "r", stdin);
  freopen("4425.out", "w", stdout);
  cin >> n >> m >> p;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    L = i, R = i;
    add(1, 1, n);
  }
  x = maxx[1] - n;
  ans = query(1, 1, n) + n;
  printf("%d\n", ans);
  while (m--) {
    scanf("%d%d", &y, &x);
    y ^= (ans * p), x ^= (ans * p);
    a[y] = x, L = y, R = y;
    add(1, 1, n);
    x = maxx[1] - n;
    printf("%d\n", ans = query(1, 1, n) + n);
  }
}
