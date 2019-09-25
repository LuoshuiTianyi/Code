#include <cstdio>
#include <iostream>
using namespace std;
int n, K, pre[16], a[16];
double f[101][1 << 15];
int main() {
  freopen("2473.in", "r", stdin);
  freopen("2473.out", "w", stdout);
  cin >> K >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    int x;
    cin >> x;
    for (; x; cin >> x)
      pre[i] |= (1 << (x - 1));
  }
  for (int j = K; j >= 1; j--)
    for (int S = 0; S < (1 << n); S++) {
      for (int i = 1; i <= n; i++)
        if ((S & pre[i]) == pre[i])
          f[j][S] += max(f[j + 1][S], f[j + 1][S | (1 << (i - 1))] + a[i]);
        else
          f[j][S] += f[j + 1][S];
      f[j][S] /= n;
    }
  printf("%.6lf", f[1][0]);
}
