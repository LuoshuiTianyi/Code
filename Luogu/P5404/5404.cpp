#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
long long read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 2e3 + 5, M = 26, mod = 998244353;
int n, m, ans;
int nx[Max_n], ch[Max_n][M], Min[Max_n];
int f[Max_n][Max_n], g[Max_n][Max_n];
int cntv, vis[Max_n];
char S[Max_n];
void dfs(int x) {
  if (vis[x]) {
    int size = cntv - vis[x] + 1;
    if (m % size == 0) ans += size;
    return;
  }
  vis[x] = ++cntv;
  dfs(ch[x][Min[x]]);
}
void Mod(int &x) { x %= mod; }
int main() {
#ifndef ONLINE_JUDGE
  freopen("5404.in", "r", stdin);
  freopen("5404.out", "w", stdout);
#endif
  m = read();
  scanf(" %s", S + 1);
  n = strlen(S + 1);
  nx[1] = 0;
  for (int i = 0; i < n; i++) ch[i][S[i + 1] - 'a'] = i + 1;
  for (int i = 1; i <= n; i++)
    for (int j = 0; j < M; j++)
      if (ch[i][j])
        nx[ch[i][j]] = ch[nx[i]][j];
      else
        ch[i][j] = ch[nx[i]][j];
  for (int i = 0; i <= n; i++)
    for (int j = M - 1; ~j; j--)
      if (ch[i][j]) {
        Min[i] = j;
        break;
      }
  dfs(0);
  f[0][0] = 1;
  for (int i = 0; i < m; i++)
    for (int j = 0; j <= n; j++) {
      Mod(f[i + 1][ch[j][Min[j]]] += f[i][j]);
      Mod(f[i + 1][0] += 1ll * f[i][j] * (25 - Min[j]) % mod);
    }
  for (int i = 0; i <= n; i++) g[1][i] = 25 - Min[i];
  for (int i = 2; i <= m; i++)
    for (int j = 0; j <= n; j++)
      Mod(g[i][j] += g[i - 1][ch[j][Min[j]]]);
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= m; j++)
      Mod(ans += 1ll * f[j][i] * g[m - j][i] % mod);
  int tot = 1;
  for (int i = 1; i <= m; i++) tot = 26ll * tot % mod;
  cout << (tot - ans + mod) % mod;
}
