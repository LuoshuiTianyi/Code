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
#define mid ((l + r) >> 1)
long long read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-') w = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 2e5 + 5;
int n, m;
int num[Max_n], a[Max_n], key[Max_n];
int L, R, x, ans, cnts, rt[Max_n], sum[Max_n * 20], ls[Max_n * 20],
    rs[Max_n * 20];
bool cmp(int x, int y) { return a[x] < a[y]; }
void build(int o, int l, int r) {
  int now = ++cnts;
  if (l == r) {
    sum[now] = sum[o] + 1;
    return;
  }
  if (key[x] <= mid)
    build(ls[o], l, mid);
  else
    build(rs[o], mid + 1, r);
  ls[now] = key[x] <= mid ? now + 1 : ls[o];
  rs[now] = key[x] <= mid ? rs[o] : now + 1;
  sum[now] = sum[ls[now]] + sum[rs[now]];
}
void query(int p1, int p2, int l, int r) {
  if (l == r) {
    ans = a[num[l]];
    return;
  }
  if (sum[ls[p2]] - sum[ls[p1]] >= x) {
    query(ls[p1], ls[p2], l, mid);
  } else {
    x -= sum[ls[p2]] - sum[ls[p1]];
    query(rs[p1], rs[p2], mid + 1, r);
  }
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("3834.in", "r", stdin);
  freopen("3834.out", "w", stdout);
#endif
  n = read(), m = read();
  for (int i = 1; i <= n; i++) a[i] = read(), num[i] = i;
  sort(num + 1, num + n + 1, cmp);
  for (int i = 1; i <= n; i++) key[num[i]] = i;
  for (int i = 1; i <= n; i++) x = i, rt[i] = cnts + 1, build(rt[i - 1], 1, n);
  while (m--) {
    L = read(), R = read(), x = read();
    query(rt[L - 1], rt[R], 1, n);
    printf("%d\n", ans);
  }
}
