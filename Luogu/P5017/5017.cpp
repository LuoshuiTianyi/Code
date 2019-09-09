#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
int n, m, t[502], sum[100101], cnt, limit, tot[100101], f[100101];
int main() {
  freopen("5017.in", "r", stdin);
  freopen("5017.out", "w", stdout);
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    cin >> t[i];
  sort(t + 1, t + n + 1);
  for (int i = 1; i <= n; i++) {
    t[i] -= cnt;
    if (t[i] - t[i - 1] > 2 * m) {
      cnt += t[i] - t[i - 1] - 2 * m;
      t[i] = t[i - 1] + 2 * m;
    }
  }
  limit = t[n] + m - 1;
  int pos = 1;
  for (int i = 0; i <= limit; i++) {
    sum[i] = sum[i - 1];
    tot[i] = tot[i - 1];
    while (i == t[pos]) {
      sum[i] += t[pos++];
      tot[i]++;
    }
    f[i] = 2e9;
  }
  f[0] = 0;
  for (int i = 1; i <= limit; i++) {
    if (tot[i] - tot[i - 1] == 0)
      f[i] = f[i - 1];
    if (i >= m)
      for (int j = i - m; j >= i - 2 * m && j >= 0; j--)
        f[i] = min(f[i], f[j] + i * (tot[i] - tot[j]) - sum[i] + sum[j]);
    else
      f[i] = min(f[i], tot[i] * i - sum[i]);
  }
  cout << f[limit];
}
