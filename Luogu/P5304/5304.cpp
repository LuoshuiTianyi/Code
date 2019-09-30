#pragma GCC optimize(2)
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
#define LL long long
#define inline __inline__ __attribute__((always_inline))
inline LL read() {
  LL x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-') w = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 1e5 + 5, Max_m = 5e5 + 5;
int T;
int n, m, K;
int cr[2], hd[2][Max_n], nx[2][Max_m], to[2][Max_m], w[2][Max_m];
int fr[2][Max_n];
LL ans, dis[2][Max_n];
struct node {
  int id;
  LL dis;
  bool operator<(const node &b) const { return dis > b.dis; }
};
void addr(bool t, int u, int v, int W) {
  cr[t]++;
  nx[t][cr[t]] = hd[t][u], to[t][cr[t]] = v, w[t][cr[t]] = W;
  hd[t][u] = cr[t];
}
priority_queue<node> q[2];
void Dij(bool t) {
  while (!q[t].empty()) {
    int x = q[t].top().id;
    q[t].pop();
    for (int i = hd[t][x], v = to[t][i]; i; v = to[t][(i = nx[t][i])])
      if (dis[t][v] > dis[t][x] + w[t][i])
        q[t].push((node){v, dis[t][v] = dis[t][x] + w[t][i]}), fr[t][v] = x;
  }
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("5304.in", "r", stdin);
  freopen("5304.out", "w", stdout);
#endif
  T = read();
  while (T--) {
    memset(hd, 0, sizeof(hd)), memset(fr, 0, sizeof(fr));
    cr[0] = cr[1] = 0;
    n = read(), m = read(), K = read();
    int u, v, W;
    for (int i = 1; i <= m; i++) {
      u = read(), v = read(), W = read();
      addr(0, u, v, W), addr(1, v, u, W);
    }
    ans = 2e18, memset(dis, 0x7f, sizeof(dis));
    for (int i = 1; i <= K; i++) {
      u = read(), dis[0][u] = dis[1][u] = 0;
      q[0].push((node){u, 0ll}), q[1].push((node){u, 0ll});
    }
    Dij(0), Dij(1);
    for (int i = 1; i <= n; i++)
      for (int j = hd[0][i], v = to[0][j]; j; v = to[0][(j = nx[0][j])])
        if (fr[0][i] != fr[1][v]) ans = min(ans, w[0][j] + dis[0][i] + dis[1][v]);
    cout << ans << endl;
  }
}
