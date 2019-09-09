#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n, Q, a[100001], cnt, key[100001], book[2][100001], size, t[100001], now, C;
int L, R, lnow;
long long ans, Ans[100001], maxx, nowmax;
void Max(long long &a, long long b) {
  if (b > a)
    a = b;
}
struct Que {
  int l, r, q, d;
} k[100001];
struct number {
  int num, d;
} num[100001];
bool cmp(number a, number b) { return a.num < b.num; }
bool cmp2(Que a, Que b) { return a.q != b.q ? a.q < b.q : a.r < b.r; }
long long Pow(int l, int r) {
  long long maxx = 0;
  int book[100001] = {0};
  for (int i = l; i <= r; i++)
    Max(maxx, 1ll * (++book[a[i]]) * key[a[i]]);
  return maxx;
}
void And(int x) {
  if (t[a[x]] != now) {
    t[a[x]] = now;
    book[1][a[x]] = book[0][a[x]];
  }
}
void Add(int x) {
  And(x);
  Max(nowmax, 1ll * (++book[1][a[x]]) * key[a[x]]);
}
void add(int x) { Max(maxx, 1ll * (++book[0][a[x]]) * key[a[x]]); }
int main() {
  freopen("4241.in", "r", stdin);
  freopen("4241.out", "w", stdout);
  cin >> n >> Q;
  size = sqrt(n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &num[i].num);
    num[i].d = i;
  }
  sort(num + 1, num + n + 1, cmp);
  for (int i = 1; i <= n; i++) {
    if (num[i].num != num[i - 1].num)
      key[++cnt] = num[i].num;
    a[num[i].d] = cnt;
  }
  for (int i = 1; i <= Q; i++) {
    scanf("%d%d", &k[i].l, &k[i].r);
    k[i].d = i, k[i].q = k[i].l / size;
    if (k[i].r - k[i].l <= size) {
      Ans[i] = Pow(k[i].l, k[i].r);
      k[i].q = 1e9;
      C++;
    }
  }
  sort(k + 1, k + Q + 1, cmp2);
  k[0].q = -1;
  for (int i = 1; i <= Q - C; i++) {
    now++;
    if (k[i].q != k[i - 1].q) {
      lnow = (k[i].q + 1) * size, nowmax = maxx = 0,
      R = (k[i].q + 1) * size - 1;
      memset(book, 0, sizeof(book));
    }
    L = lnow;
    while (R < k[i].r)
      add(++R);
    nowmax = maxx;
    while (L > k[i].l)
      Add(--L);
    Ans[k[i].d] = nowmax;
  }
  for (int i = 1; i <= Q; i++)
    printf("%lld\n", Ans[i]);
}
