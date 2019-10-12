#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
int n, m, A, B, a[100002];
int Sum(int l, int r) {
  int y = (upper_bound(a + 1, a + n + 1, r) - a - 1),
      x = (lower_bound(a + 1, a + n + 1, l) - a);
  if (a[x] > r || x > y || a[y] < l)
    return 0;
  return y - x + 1;
}
long long Work(int l, int r) { return 1ll * Sum(l, r) * B * (r - l + 1); }
long long solve(int l, int r) {
  int mid = (l + r) / 2;
  if (!Sum(l, r))
    return A;
  if (l == r)
    return 1ll * B * Sum(l, r);
  return min(Work(l, r), solve(l, mid) + solve(mid + 1, r));
}
int main() {
  freopen("C.in", "r", stdin);
  freopen("C.out", "w", stdout);
  cin >> m >> n >> A >> B;
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  sort(a + 1, a + n + 1);
  cout << solve(1, (1 << m));
}
