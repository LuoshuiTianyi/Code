#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
const int Max_m = 25;
int n, m, ans, mod;
int F[1][Max_m], G[1][Max_m], nx[Max_m], P[Max_m];
char s[Max_m];
void Mod(int& x) { x %= mod; }
struct matrix {
  int a[Max_m][Max_m];
  matrix() {
    for (int i = 0; i <= m; i++)
      for (int j = 0; j <= m; j++) a[i][j] = 0;
  }
  matrix operator*(const matrix& b) const {
    matrix c;
    for (int i = 0; i <= m; i++)
      for (int j = 0; j <= m; j++)
        for (int k = 0; k <= m; k++) Mod(c.a[i][j] += a[i][k] * b.a[k][j]);
    return c;
  }
} f, g;
int main() {
#ifndef ONLINE_JUDGE
  freopen("3193.in", "r", stdin);
  freopen("3193.out", "w", stdout);
#endif
  scanf("%d%d%d%s", &n, &m, &mod, s + 1);
  nx[0] = -1;
  for (int i = 1; i <= m; i++) {
    P[i] = s[i] - '0';
    for (int j = nx[i - 1]; ~j; j = nx[j])
      if (P[j + 1] == P[i]) {
        nx[i] = j + 1;
        break;
      }
    for (int j = 0; j <= 9; j++) {
      bool flag = 0;
      for (int k = i - 1; ~k; k = nx[k])
        if (P[k + 1] == j && !flag) g.a[i - 1][k + 1]++, flag = 1;
      if (!flag) g.a[i - 1][0]++;
    }
  }
  f.a[0][0] = 1;
  while (n) {
    if (n & 1) f = f * g;
    g = g * g;
    n >>= 1;
  }
  for (int i = 1; i <= n; i++) f = f * g;
  for (int i = 0; i < m; i++) Mod(ans += f.a[0][i]);
  cout << ans;
}
