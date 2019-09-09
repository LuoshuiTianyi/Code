#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
int n, m, a[50001], ans, answer[200001], now[1000001], L, R, size;
struct Que {
  int q, l, r, d;
} k[200001];
bool cmp(Que a, Que b) { return a.q == b.q ? a.r < b.r : a.q < b.q; }
void Add(int x) {
  if (!now[a[x]])
    ans++;
  now[a[x]]++;
}
void Del(int x) {
  now[a[x]]--;
  if (!now[a[x]])
    ans--;
}
int main() {
  freopen("1878.in", "r", stdin);
  freopen("1878.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  size = sqrt(n);
  cin >> m;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &k[i].l, &k[i].r);
    k[i].q = k[i].l / size;
    k[i].d = i;
  }
  sort(k + 1, k + m + 1, cmp);
  L = k[1].l, R = k[1].l - 1;
  for (int i = 1; i <= m; i++) {
    while (L > k[i].l)
      Add(--L);
    while (L < k[i].l)
      Del(L++);
    while (R < k[i].r)
      Add(++R);
    while (R > k[i].r)
      Del(R--);
    answer[k[i].d] = ans;
  }
  for (int i = 1; i <= m; i++)
    printf("%d\n", answer[i]);
}
