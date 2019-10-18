#include <cstdio>
#include <iostream>
using namespace std;
int n, head, tail, tot, Ans = 2e9, w[20001], d[20002], q[20002], que[20001],
                        f[20001];
void solve(int l, int r, int L, int R) {
  if (l > r)
    return;
  int p = L, mid = (l + r) >> 1;
  f[mid] = 1e9;
  for (int i = L; i <= min(mid - 1, R); i++) {
    int x = tot - d[i] * q[i] - d[mid] * (q[mid] - q[i]);
    if (x < f[mid])
      f[mid] = x, p = i;
  }
  solve(l, mid - 1, L, p);
  solve(mid + 1, r, p, R);
  Ans = min(Ans, f[mid]);
}
int main() {
  freopen("4360.in", "r", stdin);
  freopen("4360.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++)
    scanf("%d%d", &w[i], &d[i]);
  for (int i = n; i >= 1; i--)
    d[i] += d[i + 1];
  for (int i = 1; i <= n; i++)
    q[i] = q[i - 1] + w[i], tot += w[i] * d[i];
  solve(1, n, 1, n);
  cout << Ans;
}
