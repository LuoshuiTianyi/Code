#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
int n, m, now[50001], a[50001], size, L, R;
long long ans, answer[50001], total[50001];
struct Que {
  int l, r, d, q;
} k[50001];
bool cmp(Que a, Que b) { return a.q == b.q ? a.r < b.r : a.q < b.q; }
void Add(int x) {
  ans += 2 * now[a[x]];
  now[a[x]]++;
}
void Del(int x) {
  now[a[x]]--;
  ans -= 2 * now[a[x]];
}
long long gcd(long long a, long long b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}
int main() {
  freopen("1494.in", "r", stdin);
  freopen("1494.out", "w", stdout);
  cin >> n >> m;
  size = sqrt(n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  L = k[1].l, R = k[1].l - 1;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &k[i].l, &k[i].r);
    total[i] = 1ll * (k[i].r - k[i].l) * (k[i].r - k[i].l + 1);
    k[i].q = k[i].l / size;
    k[i].d = i;
  }
  sort(k + 1, k + m + 1, cmp);
  for (int i = 1; i <= m; i++) {
    while (L > k[i].l)
      Add(--L);
    while (L < k[i].l)
      Del(L++);
    while (R > k[i].r)
      Del(R--);
    while (R < k[i].r)
      Add(++R);
    answer[k[i].d] = ans;
  }
  for (int i = 1; i <= m; i++) {
    if (!answer[i])
      cout << "0/1\n";
    else {
      long long g = gcd(answer[i], total[i]);
      printf("%lld/%lld\n", answer[i] / g, total[i] / g);
    }
  }
}
