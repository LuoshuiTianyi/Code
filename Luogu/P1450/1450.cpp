#include <cstdio>
#include <iostream>
using namespace std;
int n, T, limit;
long long ans, f[100001];
int a[5], d[5];
int main() {
  freopen("1450.in", "r", stdin);
  freopen("1450.out", "w", stdout);
  for (int i = 1; i <= 4; i++)
    scanf("%d", &a[i]);
  f[0] = 1;
  for (int i = 1; i <= 4; i++)
    for (int j = a[i]; j <= 100000; j++)
      f[j] += f[j - a[i]];
  cin >> T;
  while (T--) {
    ans = 0;
    for (int i = 1; i <= 4; i++)
      scanf("%d", &d[i]);
    cin >> limit;
    for (int s = 0; s < 16; s++) {
      int sum = 0, pos = 0, now = s, num = limit;
      while (now > 0) {
        pos++;
        if (now & 1) {
          sum++;
          num -= (d[pos] + 1) * a[pos];
        }
        now >>= 1;
      }
      if (num >= 0) {
        if (sum & 1)
          ans -= f[num];
        else
          ans += f[num];
      }
    }
    printf("%lld\n", ans);
  }
}
