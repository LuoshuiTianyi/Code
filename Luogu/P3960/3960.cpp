#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
int n, m, Q, sum[2400001], x, adv[2400001], bj[2400001], L, R;
long long s[600001];
bool book[600001];
struct node {
  int x, y, d, next;
} k[300002];
bool cmp(node a, node b) {
  if (a.x == b.x)
    return a.d < b.d;
  return a.x < b.x;
}
void pushdown(int o, int l, int r) {
  if (adv[o] != -1) {
    int mid = (l + r) / 2;
    adv[o * 2] = adv[o * 2 + 1] = adv[o];
    sum[o * 2] = (mid - l + 1) * adv[o];
    sum[o * 2 + 1] = (r - mid) * adv[o];
    adv[o] = -1;
  }
}
void pushup(int o) { sum[o] = sum[o * 2] + sum[o * 2 + 1]; }
void add(int o, int l, int r) {
  if (l >= L && r <= R) {
    sum[o] = x * (r - l + 1);
    adv[o] = x;
    return;
  }
  pushdown(o, l, r);
  int mid = (l + r) / 2;
  if (mid >= L)
    add(o * 2, l, mid);
  if (mid < R)
    add(o * 2 + 1, mid + 1, r);
  pushup(o);
}
void query(int o, int l, int r) {
  int mid = (l + r) / 2;
  if (l == r) {
    x = r;
    return;
  }
  pushdown(o, l, r);
  if (sum[o * 2] < R) {
    R -= sum[o * 2];
    query(o * 2 + 1, mid + 1, r);
  } else
    query(o * 2, l, mid);
  pushup(o);
}
void work(int l, int r, int X) {
  sum[1] = 0;
  adv[1] = 0;
  L = 1, R = m;
  x = 1;
  add(1, 1, m + Q);
  int xl[300001];
  for (int i = l; i <= r; i++)
    xl[i - l] = k[i].next;
  for (int i = l; i <= r; i++) {
    R = k[i].y;
    query(1, 1, m + Q);
    if (x < m)
      s[k[i].d + n] = (long long)(X - 1) * m + x;
    else {
      book[k[i].d + n] = 1;
      s[k[i].d + n] = xl[x - m];
    }
    L = x, R = x;
    x = 0;
    add(1, 1, m + Q);
    L = m + i - l + 1, R = m + i - l + 1;
    x = 1;
    add(1, 1, m + Q);
  }
}
int main() {
  freopen("3960.in", "r", stdin);
  freopen("3960.out", "w", stdout);
  cin >> n >> m >> Q;
  for (int i = 1; i <= max(n, m) + Q; i++)
    adv[i] = -1;
  L = 1, R = n, x = 1;
  add(1, 1, n + Q);
  for (int i = 1; i <= n; i++)
    s[i] = (long long)i * (long long)m;
  for (int i = 1; i <= Q; i++) {
    scanf("%d%d", &k[i].x, &k[i].y);
    k[i].d = i;
    R = k[i].x;
    query(1, 1, n + Q);
    k[i].next = x;
    L = x, R = x;
    x = 0;
    add(1, 1, n + Q);
    L = n + i, R = n + i;
    x = 1;
    add(1, 1, n + Q);
  }
  sort(k + 1, k + Q + 1, cmp);
  int head = 1;
  for (int i = 2; i <= Q + 1; i++)
    if (k[i].x != k[i - 1].x) {
      work(head, i - 1, k[i - 1].x);
      head = i;
    }
  for (int i = n + 1; i <= n + Q; i++) {
    if (book[i])
      s[i] = s[s[i]];
    printf("%lld\n", s[i]);
  }
}
