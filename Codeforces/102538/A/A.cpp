#include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace std;
using namespace __gnu_pbds;
typedef long long ll;
typedef pair<int, int> pr;
#define mp make_pair
#define int ll
inline ll read() {
  ll x = 0, w = 1;
  char ch = 0;
  while (ch < '0' || ch > '9') {
    ch = getchar();
    if (ch == '-') w = -1;
  }
  while (ch <= '9' && ch >= '0') {
    x = (x << 1) + (x << 3) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int N = 1e6 + 5;
const int Mod = 998244353;
const int inf = 1e9;
inline void ad(int &x, int y) {
  x += y;
  if (x >= Mod) x -= Mod;
}
inline int Pow(int x, int y) {
  int res = 1;
  while (y) {
    if (y & 1) res = 1ll * res * x % Mod;
    x = 1ll * x * x % Mod;
    y >>= 1;
  }
  return res;
}
int fac[N], inv[N];
inline void math_init(int nn) {
  fac[0] = 1;
  for (int i = 1; i <= nn; ++i) fac[i] = 1ll * fac[i - 1] * i % Mod;
  inv[nn] = Pow(fac[nn], Mod - 2);
  for (int i = nn; i; --i) inv[i - 1] = 1ll * inv[i] * i % Mod;
}
const int G = 3;
const int GI = Pow(G, Mod - 2);
namespace NTT {
int lim, lg;
int rev[N << 1];
inline void ntt(int *a, int flag) {
  for (int i = 0; i < lim; ++i)
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int len = 2; len <= lim; len <<= 1) {
    int wn = Pow((flag == 1) ? G : GI, (Mod - 1) / len);
    for (int l = 0; l + len - 1 < lim; l += len) {
      int r = l + len - 1, mid = (l + r >> 1);
      for (int i = 0, wnk = 1; i + l <= mid; ++i, wnk = 1ll * wnk * wn % Mod) {
        int x = a[i + l], y = 1ll * a[i + mid + 1] * wnk % Mod;
        ad(a[i + l], y), a[i + mid + 1] = (x - y + Mod) % Mod;
      }
    }
  }
  if (flag == 1) return;
  int inv = Pow(lim, Mod - 2);
  for (int i = 0; i < lim; ++i) a[i] = 1ll * a[i] * inv % Mod;
}
inline void init(int n, int m) {
  lim = 1, lg = 0;
  while (lim <= n + m) lim <<= 1, ++lg;
  for (int i = 0; i < lim; ++i)
    rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (lg - 1));
}
inline void mul(int *f, int *g) {
  ntt(f, 1), ntt(g, 1);
  for (int i = 0; i <= lim; ++i) f[i] = 1ll * f[i] * g[i] % Mod;
  ntt(f, -1);
}
inline void clear(int *f) {
  for (int i = 0; i < lim; ++i) f[i] = 0;
}
}  // namespace NTT
struct edge {
  int next, to;
} a[N << 1];
int head[N], cnt;
inline void add(int u, int v) {
  a[++cnt].to = v;
  a[cnt].next = head[u];
  head[u] = cnt;
}
int n, maxd, tim;
int dep[N], dfn[N];
int lg[N], mn[N][20];
inline void RMQ() {
  for (int i = 2; i <= tim; ++i) lg[i] = lg[i >> 1] + 1;
  for (int j = 1; j < 20; ++j)
    for (int i = 1; i + (1 << j) - 1 <= tim; ++i)
      mn[i][j] = min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
}
inline int lcadep(int u, int v) {
  int l = dfn[u], r = dfn[v];
  if (l > r) swap(l, r);
  int k = lg[r - l + 1];
  return min(mn[l][k], mn[r - (1 << k) + 1][k]);
}
inline int dist(int u, int v) { return dep[u] + dep[v] - (lcadep(u, v) << 1); }
void dfs_init(int x, int fa) {
  mn[dfn[x] = ++tim][0] = dep[x] = dep[fa] + 1;
  for (int i = head[x]; i; i = a[i].next) {
    int y = a[i].to;
    if (y == fa) continue;
    dfs_init(y, x);
    mn[++tim][0] = dep[x];
  }
}
int rt;
int mn_sub[N], vis[N];
int fa[N], sz[N], rk[N];
inline bool cmp(int u, int v) {
  return (dep[u] == dep[v]) ? (u < v) : (dep[u] < dep[v]);
}
void find_root(int x, int las, int tsz) {
  sz[x] = 1, mn_sub[x] = tsz;
  for (int i = head[x]; i; i = a[i].next) {
    int y = a[i].to;
    if (y == las || vis[y]) continue;
    find_root(y, x, tsz);
    mn_sub[x] = min(mn_sub[x], sz[y]);
    sz[x] += sz[y];
  }
  mn_sub[x] = min(mn_sub[x], tsz - sz[x]);
  if (!rt || mn_sub[x] < mn_sub[rt]) rt = x;
}
void build(int x, int las) {
  fa[x] = las, vis[x] = 1;
  for (int i = head[x]; i; i = a[i].next) {
    int y = a[i].to;
    if (vis[y]) continue;
    rt = 0;
    find_root(y, 0, sz[y]);
    find_root(rt, 0, sz[y]);
    build(rt, x);
  }
}
tree<pr, null_type, less<pr>, rb_tree_tag, tree_order_statistics_node_update>
    t1[N], t2[N];
inline void ins(int x) {
  for (int i = x; i; i = fa[i]) {
    t1[i].insert(mp(dist(x, i), x));
    if (fa[i]) t2[i].insert(mp(dist(x, fa[i]), x));
  }
}
inline int query(int x) {
  int res = 0;
  for (int i = x; i; i = fa[i]) {
    int now = dist(x, i);
    res += t1[i].order_of_key(mp(maxd - now, inf));
    if (fa[i]) res -= t2[i].order_of_key(mp(maxd - dist(fa[i], x), inf));
  }
  return res;
}
int val[N], f[N], g[N];
signed main() {
#ifndef ONLINE_JUDGE
  freopen("A.in", "r", stdin);
  freopen("A.out", "w", stdout);
#endif
  n = read(), maxd = read();
  math_init(n);
  for (int i = 1; i < n; ++i) {
    int u = read(), v = read();
    add(u, v), add(v, u);
  }
  dfs_init(1, 0);
  RMQ();
  find_root(1, 0, n);
  find_root(rt, 0, n);
  build(rt, 0);
  for (int i = 1; i <= n; ++i) rk[i] = i;

  sort(rk + 1, rk + n + 1, cmp);
  for (int i = 1; i <= n; ++i) {
    val[rk[i]] = query(rk[i]), ins(rk[i]);
    ad(f[val[rk[i]]], fac[val[rk[i]]]);
  }
  for (int i = 0; i <= n; ++i) g[i] = inv[n - i];
  NTT::init(n, n);
  NTT::mul(f, g);
  for (int i = 1; i <= n; ++i)
    printf("%lld ", 1ll * inv[i - 1] * f[n + i - 1] % Mod);
  puts("");
  return 0;
}
