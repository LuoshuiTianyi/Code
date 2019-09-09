#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
#define ls (o << 1)
#define rs ((o << 1) + 1)
#define mid ((l + r) >> 1)
const int mod = 998244353;
int n, Q, K, que[50001], Ans[50001];
int cntr, dep[50001], head[50001], nx[50001], to[50001];
int fa[50001], size[50001];
int cntd, q[50001], d[50001], key[50001], top[50001], son[50001];
int L, R, ans, adv[200001], sum[200001];
vector<int> Mount[50001];
void Mod(int &x) { x %= mod; }
int ksm(int a, int b) {
  int base = 1;
  while (b) {
    if (b & 1)
      base = 1ll * base * a % mod;
    a = 1ll * a * a % mod;
    b >>= 1;
  }
  return base;
}
void addr(int u, int v) {
  cntr++;
  nx[cntr] = head[u], to[cntr] = v;
  head[u] = cntr;
}
void build1(int x) {
  dep[x] = dep[fa[x]] + 1, size[x] = 1, top[x] = x;
  for (int i = head[x]; i; i = nx[i]) {
    build1(to[i]);
    if (size[to[i]] > size[son[x]])
      son[x] = to[i];
    size[x] += size[to[i]];
  }
}
void build2(int x) {
  d[x] = ++cntd, key[cntd] = x;
  if (son[x])
    top[son[x]] = top[x], build2(son[x]);
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != son[x])
      build2(to[i]);
}
void Upd(int o, int l, int r, int x) {
  Mod(sum[o] += 1ll * x * (q[dep[key[r]]] - q[dep[key[l]] - 1] + mod) % mod);
}
void pushdown(int o, int l, int r) {
  Upd(ls, l, mid, adv[o]), Upd(rs, mid + 1, r, adv[o]);
  adv[ls] += adv[o], adv[rs] += adv[o];
  adv[o] = 0;
}
void pushup(int o) { Mod(sum[o] = sum[ls] + sum[rs]); }
void add(int o, int l, int r) {
  if (l >= L && r <= R) {
    adv[o]++;
    Upd(o, l, r, 1);
    return;
  }
  pushdown(o, l, r);
  if (L <= mid)
    add(ls, l, mid);
  if (R > mid)
    add(rs, mid + 1, r);
  pushup(o);
}
void query(int o, int l, int r) {
  if (l >= L && r <= R) {
    Mod(ans += sum[o]);
    return;
  }
  pushdown(o, l, r);
  if (L <= mid)
    query(ls, l, mid);
  if (R > mid)
    query(rs, mid + 1, r);
  pushup(o);
}
void Add(int x) {
  while (x) {
    L = d[top[x]], R = d[x];
    add(1, 1, n);
    x = fa[top[x]];
  }
}
int Query(int x) {
  ans = 0;
  while (x) {
    L = d[top[x]], R = d[x];
    query(1, 1, n);
    x = fa[top[x]];
  }
  return ans;
}
int main() {
  freopen("5305.in", "r", stdin);
  freopen("5305.out", "w", stdout);
  cin >> n >> Q >> K;
  for (int i = 2; i <= n; i++) {
    scanf("%d", &fa[i]);
    addr(fa[i], i);
  }
  build1(1), build2(1);
  for (int i = 1; i <= n; i++)
    q[i] = ksm(i, K);
  int pos;
  for (int i = 1; i <= Q; i++) {
    scanf("%d%d", &pos, &que[i]);
    Mount[pos].push_back(i);
  }
  for (int i = 1; i <= n; i++) {
    Add(i);
    for (int j = Mount[i].size() - 1; ~j; j--) {
      int To = Mount[i][j];
      Ans[To] = Query(que[To]);
    }
  }
  for (int i = 1; i <= Q; i++)
    printf("%d\n", Ans[i]);
}
