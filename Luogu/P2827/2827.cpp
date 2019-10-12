#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
int n, m, Q, T, cnt;
long long v, u, num[100001], ans[10000001];
queue<long long> q[4];
int pd() {
  int p = 0;
  long long maxx = -1e18;
  for (int i = 1; i <= 3; i++)
    if (!q[i].empty())
      if (q[i].front() > maxx) {
        maxx = q[i].front();
        p = i;
      }
  return p;
}
int main() {
  freopen("2827.in", "r", stdin);
  freopen("2827.out", "w", stdout);
  cin >> n >> m >> Q >> u >> v >> T;
  for (int i = 1; i <= n; i++)
    cin >> num[i];
  sort(num + 1, num + n + 1);
  for (int i = n; i >= 1; i--)
    q[1].push(num[i]);
  for (int t = 1; t <= m; t++) {
    int p = pd();
    long long x = q[p].front() + (long long)(t - 1) * Q;
    if (t % T == 0)
      printf("%lld ", x);
    long long a = x * u / v;
    long long b = x - a;
    a -= t * Q;
    b -= t * Q;
    q[2].push(a);
    q[3].push(b);
    q[p].pop();
  }
  cout << endl;
  for (int i = 1; i <= 3; i++)
    while (!q[i].empty()) {
      ans[++cnt] = q[i].front() + (long long)m * Q;
      q[i].pop();
    }
  sort(ans + 1, ans + cnt + 1);
  for (int i = cnt - T + 1; i >= 1; i -= T)
    printf("%lld ", ans[i]);
}
