#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n, K, sum, L, R, now, a[40001], c[40001], f[40001][11];
void add(int k, int x) {
  for (int i = k; i <= n; i += i & -i)
    c[i] += x;
}
int query(int x) {
  int ans = 0;
  for (int i = x; i > 0; i -= i & -i)
    ans += c[i];
  return ans;
}
void Move(int l, int r) {
  while (L < l)
    sum -= query(a[L] - 1), add(a[L++], -1);
  while (L > l)
    sum += query(a[L - 1] - 1), add(a[--L], 1);
  while (R < r)
    sum += R - L + 1 - query(a[R + 1]), add(a[++R], 1);
  while (R > r)
    sum -= R - L + 1 - query(a[R]), add(a[R--], -1);
}
void solve(int l, int r, int L, int R) {
  if (l > r)
    return;
  int mid = (l + r) >> 1, p = L;
  for (int i = L; i <= min(mid - 1, R); i++) {
    Move(i + 1, mid);
    int Sum = f[i][now - 1] + sum;
    if (Sum < f[mid][now])
      f[mid][now] = Sum, p = i;
  }
  cout << l << " " << r << " " << L << " " << R << " " << f[mid][now] << " "
       << p << endl;
  solve(l, mid - 1, L, p);
  solve(mid + 1, r, p, R);
}
int main() {
  freopen("5152.in", "r", stdin);
  freopen("5152.out", "w", stdout);
  cin >> n >> K;
  L = 1;
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  memset(f, 10, sizeof(f));
  for (int i = 1; i <= n; i++)
    Move(1, i), f[i][1] = sum;
  for (now = 2; now <= K; now++)
    solve(1, n, 1, n);
  cout << f[n][K];
}
