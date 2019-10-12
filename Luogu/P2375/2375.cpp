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
const int Max_L = 1e6 + 5, mod = 1e9 + 7;
int T, n, ans, f[Max_L], s[Max_L], fa[Max_L][21];
char S[Max_L];
int main() {
#ifndef ONLINE_JUDGE
  freopen("2375.in", "r", stdin);
  freopen("2375.out", "w", stdout);
#endif
  scanf("%d", &T);
  f[0] = -1, s[1] = 1;
  while (T--) {
    scanf("%s", S + 1);
    int n = strlen(S + 1);
    ans = 1;
    for (int i = 1; i <= n; i++) {
      f[i] = 0, s[i] = 1;
      for (int j = f[i - 1]; ~j; j--)
        if (S[j + 1] == S[i]) {
          f[i] = j + 1, s[i] = s[j + 1] + 1;
          break;
        }
      fa[i][0] = f[i];
      for (int j = 1; j <= 20; j++) fa[i][j] = fa[fa[i][j - 1]][j - 1];
    }
    for (int i = 1; i <= n; i++) {
      int pos = i;
      for (int j = 20; ~j; j--)
        if ((fa[pos][j] << 1) > i) pos = fa[pos][j];
      ans = 1ll * ans * (s[f[pos]] + 1) % mod;
    }
    cout << ans << endl;
  }
}
