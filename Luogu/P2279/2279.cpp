#include <cstdio>
#include <iostream>
using namespace std;
int f[1001][6], n, head[1001], nx[1001], to[1001], fa[1001];
void DP(int x) {
  f[x][0] = 1;
  f[x][1] = f[x][2] = 1e9;
  for (int i = head[x]; i; i = nx[i]) {
    DP(to[i]);
    f[x][0] += f[to[i]][4];
    f[x][3] += f[to[i]][2];
    f[x][4] += f[to[i]][3];
    int p = f[to[i]][0] - f[to[i]][3], p2 = f[to[i]][1] - f[to[i]][2];
    f[x][1] = min(f[x][1], p);
    f[x][2] = min(f[x][2], p2);
  }
  f[x][2] += f[x][3];
  f[x][1] += f[x][4];
  for (int i = 2; i <= 4; i++)
    for (int j = 0; j < i; j++)
      f[x][i] = min(f[x][i], f[x][j]);
}
int main() {
  freopen("2279.in", "r", stdin);
  freopen("2279.out", "w", stdout);
  cin >> n;
  for (int i = 2; i <= n; i++) {
    cin >> fa[i];
    to[i] = i, nx[i] = head[fa[i]], head[fa[i]] = i;
  }
  DP(1);
  cout << f[1][2];
}
