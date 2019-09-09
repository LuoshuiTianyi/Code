#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n, m, head, tail, a[3001], que[3001];
long long q[3001], f[3001], g[3001];
void solve(int l, int r, int L, int R) {
  if (l > r)
    return;
  int p = L, mid = (l + r) >> 1;
  f[mid] = 1e18;
  for (int i = L; i <= min(mid - 1, R); i++) {
    long long x = g[i] + (q[mid] - q[i]) * (q[mid] - q[i]);
    if (x < f[mid])
      f[mid] = x, p = i;
  }
  solve(l, mid - 1, L, p);
  solve(mid + 1, r, p, R);
}
int main() {
  freopen("4072.in", "r", stdin);
  freopen("4072.out", "w", stdout);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    q[i] = q[i - 1] + a[i], g[i] = q[i] * q[i];
  }
  for (int j = 2; j <= m; j++) {
    solve(1, n, 1, n);
    for (int i = 1; i <= n; i++)
      g[i] = f[i];
  }
  cout << 1ll * f[n] * m - q[n] * q[n];
}
