#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int T, n, b[1001], a[1001], f[1002][256][16], limit = 256, inf = 2139062143;
void Min(int &a, int b) { a = b < a ? b : a; }
int main() {
  freopen("2157.in", "r", stdin);
  freopen("2157.out", "w", stdout);
  cin >> T;
  while (T--) {
    cin >> n;
    for (int i = 1; i <= n; i++)
      cin >> a[i] >> b[i];
    memset(f, 0x7f, sizeof(f));
    f[1][0][7] = 0;
    for (int i = 1; i <= n; i++)
      for (int j = 0; j < limit; j++)
        for (int k = -8; k <= 7; k++)
          if (f[i][j][k + 8] != inf) {
            if (j & 1)
              Min(f[i + 1][j >> 1][k + 7], f[i][j][k + 8]);
            else {
              int far = inf;
              for (int l = 0; l <= 7; l++)
                if (!(j & (1 << l))) {
                  if (i + l > far)
                    break;
                  Min(far, i + l + b[i + l]);
                  Min(f[i][j | (1 << l)][l + 8],
                      f[i][j][k + 8] + (i + k ? (a[i + k] ^ a[i + l]) : 0));
                }
            }
          }
    int minn = inf;
    for (int i = 0; i <= 15; i++)
      Min(minn, f[n + 1][0][i]);
    cout << minn << endl;
  }
}
