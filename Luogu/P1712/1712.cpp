#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
int n, m, cnt, maxx[4000001], adv[4000001], sum[4000001],
    head = 1, ans, x, L, R, bf, answer = 1e9, flag;
struct node {
  int l, r, len;
} k[500001];
struct cl {
  int num, d;
} s[1000001];
void read(int &x) {
  x = 0;
  char ch = getchar();
  while (!isdigit(ch))
    ch = getchar();
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
}
bool cmp(node a, node b) { return a.len < b.len; }
bool cmp2(cl a, cl b) { return a.num < b.num; }
void pushdown(int o, int l, int r) {
  if (adv[o] != 0) {
    int mid = (l + r) / 2;
    sum[o * 2] += adv[o] * (mid - l + 1);
    sum[o * 2 + 1] += adv[o] * (r - mid);
    adv[o * 2] += adv[o];
    adv[o * 2 + 1] += adv[o];
    maxx[o * 2] += adv[o];
    maxx[o * 2 + 1] += adv[o];
    adv[o] = 0;
  }
}
void pushup(int o) {
  sum[o] = sum[o * 2] + sum[o * 2 + 1];
  maxx[o] = max(maxx[o * 2], maxx[o * 2 + 1]);
}
void add(int o, int l, int r) {
  if (l >= L && r <= R) {
    adv[o] += x;
    sum[o] += (r - l + 1) * x;
    maxx[o] += x;
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
  if (l >= L && r <= R) {
    ans = max(ans, maxx[o]);
    return;
  }
  pushdown(o, l, r);
  int mid = (l + r) / 2;
  if (L <= mid)
    query(o * 2, l, mid);
  if (R > mid)
    query(o * 2 + 1, mid + 1, r);
}
int main() {
  freopen("1712.in", "r", stdin);
  freopen("1712.out", "w", stdout);
  read(n);
  read(m);
  for (int i = 1; i <= n; i++) {
    read(k[i].l);
    read(k[i].r);
    k[i].len = k[i].r - k[i].l + 1;
  }
  sort(k + 1, k + n + 1, cmp);
  for (int i = 1; i <= n; i++) {
    s[i].num = k[i].l;
    s[i].d = i;
    s[i + n].num = k[i].r;
    s[i + n].d = i + n;
  }
  sort(s + 1, s + n * 2 + 1, cmp2);
  s[0].num = -1;
  for (int i = 1; i <= n * 2; i++) {
    if (s[i].num != s[i - 1].num)
      cnt++;
    if (s[i].d <= n)
      k[s[i].d].l = cnt;
    else
      k[s[i].d - n].r = cnt;
  }
  for (int i = 1; i <= n; i++) {
    L = k[i].l;
    R = k[i].r;
    x = 1;
    add(1, 1, cnt);
    ans = 0;
    L = 1, R = cnt;
    query(1, 1, cnt);
    if (ans == m) {
      while (ans == m) {
        L = k[head].l;
        R = k[head].r;
        x = -1;
        add(1, 1, cnt);
        ans = 0;
        L = 1;
        R = cnt;
        query(1, 1, cnt);
        bf = head;
        head++;
      }
      answer = min(answer, k[i].len - k[bf].len);
      flag = 1;
    }
  }
  if (!flag)
    cout << "-1";
  else
    cout << answer;
}
