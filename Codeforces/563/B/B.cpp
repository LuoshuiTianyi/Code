#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
int n, m, a[100001], r[100002], d[100001], c[100001], kind, sum, num[100001],
    pos, key[100001];
long long ans, rest;
inline void write(long long x) {
  if (x < 0)
    putchar('-'), x = -x;
  if (x > 9)
    write(x / 10);
  putchar(x % 10 + '0');
}
bool cmp(int a, int b) { return c[a] < c[b]; }
int main() {
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    num[i] = i;
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), r[i] = a[i], rest += a[i];
  for (int i = 1; i <= n; i++)
    scanf("%d", &c[i]), d[i] = i;
  sort(num + 1, num + n + 1, cmp);
  pos = 1;
  for (int i = 1; i <= m; i++) {
    ans = 0;
    bool flag = false;
    scanf("%d%d", &kind, &sum);
    if (rest < sum)
      flag = true;
    if (r[kind] >= sum)
      r[kind] -= sum, ans = 1ll * sum * c[kind], rest -= sum;
    else {
      ans = 1ll * r[kind] * c[kind];
      sum -= r[kind];
      rest -= r[kind];
      r[kind] = 0;
      while (r[num[pos]] < sum && pos <= n) {
        ans += 1ll * r[num[pos]] * c[num[pos]];
        sum -= r[num[pos]];
        rest -= r[num[pos]];
        r[num[pos]] = 0;
        pos++;
      }
      if (pos <= n) {
        r[num[pos]] -= sum;
        rest -= sum;
        ans += 1ll * sum * c[num[pos]];
      }
    }
    if (flag)
      ans = 0;
    write(ans);
    printf("\n");
  }
}
