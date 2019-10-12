#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
const int mod = 1e9 + 7;
int W, n, m;
int jc[100001], niv[100001];
int tot, cnt, d[100001], ls[100001], rs[100001], L[100001], R[100001],
    nx[100001], size[100001];
vector<int> G[100001];
int ans;
int Niv(int x) {
  int base = 1, b = mod - 2;
  while (b) {
    if (b & 1)
      base = 1ll * base * x % mod;
    x = 1ll * x * x % mod;
    b >>= 1;
  }
  return base;
}
int C(int a, int b) { return 1ll * jc[b] * niv[a] % mod * niv[b - a] % mod; }
void build(int l, int r) {
  if (r - l < 2)
    return;
  int id = ++cnt;
  size[id] = 1;
  L[cnt] = l, R[cnt] = r,
  nx[cnt] = *lower_bound(G[r].begin(), G[r].end(), l + 1);
  d[nx[cnt]] = id;
  ls[id] = cnt + 1, build(l, nx[id]), size[id] += size[ls[id]];
  rs[id] = cnt + 1, build(nx[id], r), size[id] += size[rs[id]];
  ans = (ans + C(size[ls[id]], size[id] - 1));
}
int main() {
  freopen("5288.in", "r", stdin);
  freopen("5288.out", "w", stdout);
  int u, v;
  cin >> W >> n;
  jc[0] = 1;
  for (int i = 1; i <= n; i++)
    jc[i] = 1ll * jc[i - 1] * i % mod, niv[i] = Niv(jc[i]),
    G[i].push_back((i - 1) % n), G[i].push_back(i % n + 1);
  tot = n - 3;
  for (int i = 1; i <= n - 3; i++) {
    scanf("%d%d", &u, &v);
    G[u].push_back(v);
    G[v].push_back(u);
    if (u == n || v == n)
      tot--;
  }
  cin >> m;
  for (int i = 1; i <= n; i++)
    sort(G[i].begin(), G[i].end());
  for (int i = G[n].size() - 1; i > 0; i--)
    build(G[n][i - 1], G[n][i]);
  cout << tot << " " << ans;
}
