#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
int n, m, w[200001], v[200001], l[200001], r[200001], mid, L, R;
long long ans, Y, S, q[200001], sum[200001];
int main() {
  freopen("1314.in", "r", stdin);
  freopen("1314.out", "w", stdout);
  cin >> n >> m >> S;
  for (int i = 1; i <= n; i++)
    scanf("%d%d", &w[i], &v[i]);
  for (int i = 1; i <= m; i++)
    scanf("%d%d", &l[i], &r[i]);
  L = 1, R = 1e6, ans = 1e13;
  while (L <= R) {
    int mid = (L + R) / 2;
    sum[0] = 0;
    q[0] = 0;
    Y = 0;
    for (int i = 1; i <= n; i++) {
      sum[i] = sum[i - 1];
      q[i] = q[i - 1];
      if (w[i] >= mid) {
        sum[i] += v[i];
        q[i]++;
      }
    }
    for (int i = 1; i <= m; i++)
      Y += (sum[r[i]] - sum[l[i] - 1]) * (q[r[i]] - q[l[i] - 1]);
    // cout<<mid<<" "<<Y<<endl;
    if (Y < S)
      R = mid - 1;
    else
      L = mid + 1;
    if (abs(Y - S) < ans)
      ans = abs(Y - S);
  }
  cout << ans;
}
