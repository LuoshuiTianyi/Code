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
long long read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 5e5 + 5;
double f[Max_n][51];
int n;
int top, stk[Max_n];
int cnt, fa[Max_n];
void node_init() {
  for (int i = 0; i <= 50; i++) f[cnt][i] = 1;
}
void dfs(int x, int len) {
  if (!fa[x] || len >= 50) return;
  dfs(fa[x], len + 1);
  f[fa[x]][len + 1] /= (f[x][len] + 1);
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("E.in", "r", stdin);
  freopen("E.out", "w", stdout);
#endif
  n = read();
  cnt = 1;
  node_init();
  while (n--) {
    if (read() == 1) {
      fa[++cnt] = read(), node_init();
      dfs(fa[cnt], 0);
      f[fa[cnt]][0] *= 0.5;
      for (int x = fa[cnt], to = 1; fa[x] && to <= 50; to++, x = fa[x])
        f[fa[x]][to] *= (f[x][to - 1] + 1);
    } else {
      double ans = 0;
      int x = read();
      for (int i = 1; i <= 50; i++) ans += (double)i * (f[x][i] - f[x][i - 1]);
      printf("%.6lf\n", ans);
    }
  }
}
