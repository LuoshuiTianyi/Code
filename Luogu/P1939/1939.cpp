#include <cstdio>
#include <iostream>
using namespace std;
const int mod = 1e9 + 7;
int T, n, now[4][4], pow[4][4], F[2][4];
int main() {
  freopen("1939.in", "r", stdin);
  freopen("1939.out", "w", stdout);
  cin >> T;
  while (T--) {
    now[1][1] = 0, now[1][2] = 0, now[1][3] = 1;
    now[2][1] = 1, now[2][2] = 0, now[2][3] = 0;
    now[3][1] = 0, now[3][2] = 1, now[3][3] = 1;
    for (int i = 1; i <= 3; i++)
      for (int j = 1; j <= 3; j++)
        pow[i][j] = now[i][j];
    F[0][1] = 1, F[0][2] = 1, F[0][3] = 1;
    cin >> n;
    n--;
    while (n > 0) {
      if (n & 1) {
        for (int i = 1; i <= 3; i++) {
          F[1][i] = 0;
          for (int j = 1; j <= 3; j++)
            F[1][i] = (F[1][i] + 1ll * F[0][j] * now[j][i] % mod) % mod;
        }
        for (int i = 1; i <= 3; i++)
          F[0][i] = F[1][i];
      }
      for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 3; j++) {
          now[i][j] = 0;
          for (int k = 1; k <= 3; k++)
            now[i][j] = (now[i][j] + 1ll * pow[i][k] * pow[k][j] % mod) % mod;
        }
      for (int i = 1; i <= 3; i++)
        for (int j = 1; j <= 3; j++)
          pow[i][j] = now[i][j];
      n >>= 1;
    }
    cout << F[0][1] << endl;
  }
}
