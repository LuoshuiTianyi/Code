#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
int n, m, K, a[50001], size, L, R, now[50001];
long long ans, answer[50001];
struct Que {
  int l, r, d, q;
} k[50001];
bool cmp(Que a, Que b) { return a.q != b.q ? a.q < b.q : a.r < b.r; }
inline void Del(int x) { ans -= 2 * (--now[a[x]]) + 1; }
inline void Add(int x) { ans += 2 * (++now[a[x]]) - 1; }
int main() {
  freopen("2709.in", "r", stdin);
  freopen("2709.out", "w", stdout);
  cin >> n >> m >> K;
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  size = sqrt(n);
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &k[i].l, &k[i].r);
    k[i].q = k[i].l / size;
    k[i].d = i;
  }
  sort(k + 1, k + m + 1, cmp);
  L = k[1].l, R = k[1].l - 1;
  for (int i = 1; i <= m; i++) {
    while (L < k[i].l)
      Del(L++);
    while (L > k[i].l)
      Add(--L);
    while (R > k[i].r)
      Del(R--);
    while (R < k[i].r)
      Add(++R);
    answer[k[i].d] = ans;
  }
  for (int i = 1; i <= m; i++)
    printf("%lld\n", answer[i]);
}
