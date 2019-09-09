#include <cstdio>
#include <iostream>
using namespace std;
int n, m, a[100001];
int opt, l, r;
long long c[2][100001], x;
void add(int k, long long x, bool p) {
  for (int i = k; i <= n; i += i & -i)
    c[p][i] += x;
}
long long query(int k, bool p) {
  long long ans = 0;
  for (int i = k; i > 0; i -= i & -i)
    ans += c[p][i];
  return ans;
}
int main() {
  freopen("3372.in", "r", stdin);
  freopen("3372.out", "w", stdout);
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), a[i] += a[i - 1];
  while (m--) {
    scanf("%d%d%d", &opt, &l, &r);
    if (opt == 1) {
      scanf("%lld", &x);
      add(l, x, 0), add(l, 1ll * x * l, 1);
      add(r + 1, -x, 0), add(r + 1, -1ll * x * (r + 1), 1);
    } else
      printf("%lld\n", 0ll + a[r] - a[l - 1] + 1ll * (r + 1) * query(r, 0) -
                           query(r, 1) - 1ll * (l)*query(l - 1, 0) +
                           query(l - 1, 1));
  }
}
