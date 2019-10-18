#include <cstdio>
#include <iostream>
using namespace std;
int n;
int cntr, head[1000001], to[1000001], nx[1000001], w[1000001];
int Q[1000001];
int que[1000001], h, t;
long long P[1000001], lj[1000001], f[1000001];
void addr(int u, int v, int W) {
  cntr++;
  to[cntr] = v, nx[cntr] = head[u], w[cntr] = W;
  head[u] = cntr;
}
double slope(int a, int b) { return (double)(f[b] - f[a]) / (lj[b] - lj[a]); }
void DP(int x) {
  int p, tph = h, tpt = t, tpw, l = h + 1, r = t, ans = h;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (slope(que[mid - 1], que[mid]) <= P[x])
      l = mid + 1, ans = mid;
    else
      r = mid - 1;
  }
  h = ans, p = que[h];
  f[x] = f[p] + (lj[x] - lj[p]) * P[x] + Q[x];
  l = h, r = t - 1, ans = t;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (slope(que[mid], que[mid + 1]) >= slope(que[mid + 1], x))
      r = mid - 1, ans = mid;
    else
      l = mid + 1;
  }
  t = ans;
  tpw = que[++t], que[t] = x;
  for (int i = head[x]; i; i = nx[i]) {
    lj[to[i]] = lj[x] + w[i];
    DP(to[i]);
  }
  que[t] = tpw;
  h = tph, t = tpt;
}
int main() {
  freopen("3994.in", "r", stdin);
  freopen("3994.out", "w", stdout);
  cin >> n;
  int F, W;
  for (int i = 2; i <= n; i++) {
    scanf("%d%d%lld%d", &F, &W, &P[i], &Q[i]);
    addr(F, i, W);
  }
  t = -1;
  DP(1);
  for (int i = 2; i <= n; i++)
    printf("%lld\n", f[i]);
}
