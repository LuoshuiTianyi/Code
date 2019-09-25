#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int T, n, m, line[19][19], limit, f[1 << 18], zj[1 << 18];
double x[19], y[19];
int main() {
  freopen("2831.in", "r", stdin);
  freopen("2831.out", "w", stdout);
  cin >> T;
  for (int i = 0; i < (1 << 18); i++) {
    int j = 1;
    for (; j <= 18 && i & (1 << (j - 1)); j++)
      ;
    zj[i] = j;
  }
  while (T--) {
    memset(f, 0x7f, sizeof(f));
    memset(line, 0, sizeof(line));
    cin >> n >> m;
    limit = 1 << n;
    for (int i = 1; i <= n; i++)
      cin >> x[i] >> y[i];
    for (int i = 1; i <= n; i++)
      for (int j = i + 1; j <= n; j++) {
        double a = ((y[i] * x[j]) - (y[j] * x[i])) * 1.0 /
                   (x[i] * x[i] * x[j] - x[j] * x[j] * x[i]);
        double b = (y[i] - a * x[i] * x[i]) * 1.0 / x[i];
        if (a >= 0)
          continue;
        for (int k = 1; k <= n; k++)
          if (abs(x[k] * x[k] * a + x[k] * b - y[k]) <= 0.0000001)
            line[i][j] |= (1 << (k - 1));
      }
    f[0] = 0;
    for (int S = 0; S < limit - 1; S++) {
      int i = zj[S];
      for (int j = i + 1; j <= n; j++)
        if (!((1 << (j - 1)) & S))
          if (f[S | line[i][j]] > f[S] + 1)
            f[S | line[i][j]] = f[S] + 1;
      if (f[S | (1 << (i - 1))] > f[S] + 1)
        f[S | (1 << (i - 1))] = f[S] + 1;
    }
    cout << f[limit - 1] << endl;
  }
}
