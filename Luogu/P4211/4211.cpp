#include <cstdio>
#include <iostream>
#include <vector>
#define ls (o << 1)
#define rs ((o << 1) + 1)
#define mid ((l + r) >> 1)
using namespace std;
const int mod = 201314;
int n, Q, sum1[50001], sum2[50001];
int cntr, head[50001], nx[100001], to[100001];
int cntd, fa[50001], size[50001], son[50001], top[50001], d[50001];
int adv[200001], sum[200001];
int L, R, ans;
vector<int> Mount[2][50001];
void addr(int u, int v) {
  cntr++;
  nx[cntr] = head[u], to[cntr] = v;
  head[u] = cntr;
}
void build1(int x) {
  size[x] = 1, top[x] = x;
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != fa[x]) {
      build1(to[i]);
      size[x] += size[to[i]];
      if (size[to[i]] > size[son[x]])
        son[x] = to[i];
    }
}
void build2(int x) {
  d[x] = ++cntd;
  if (son[x])
    top[son[x]] = top[x], build2(son[x]);
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != fa[x] && to[i] != son[x])
      build2(to[i]);
}
void pushdown(int o, int l, int r) {
  adv[ls] += adv[o], adv[rs] += adv[o];
  sum[ls] += (mid - l + 1) * adv[o], sum[rs] += (r - mid) * adv[o];
  adv[o] = 0;
}
void pushup(int o) { sum[o] = sum[ls] + sum[rs]; }
void add(int o, int l, int r) {
  if (l >= L && r <= R) {
    adv[o]++, sum[o] += (r - l + 1);
    return;
  }
  pushdown(o, l, r);
  if (mid >= L)
    add(ls, l, mid);
  if (mid < R)
    add(rs, mid + 1, r);
  pushup(o);
}
void query(int o, int l, int r) {
  if (l >= L && r <= R) {
    ans += sum[o];
    return;
  }
  pushdown(o, l, r);
  if (mid >= L)
    query(ls, l, mid);
  if (mid < R)
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
void Query(int x) {
  ans = 0;
  while (x) {
    L = d[top[x]], R = d[x];
    query(1, 1, n);
    x = fa[top[x]];
  }
}
int main() {
  freopen("4211.in", "r", stdin);
  freopen("4211.out", "w", stdout);
  cin >> n >> Q;
  int u, v, z[50001];
  for (int i = 2; i <= n; i++) {
    scanf("%d", &fa[i]);
    fa[i]++, addr(i, fa[i]), addr(fa[i], i);
  }
  build1(1), build2(1);
  for (int i = 1; i <= Q; i++) {
    scanf("%d%d%d", &u, &v, &z[i]);
    z[i]++, v++, u++, Mount[0][u - 1].push_back(i), Mount[1][v].push_back(i);
  }
  for (int i = 1; i <= n; i++) {
    Add(i);
    for (int j = Mount[0][i].size() - 1; ~j; j--) {
      Query(z[Mount[0][i][j]]);
      sum1[Mount[0][i][j]] = ans;
    }
    for (int j = Mount[1][i].size() - 1; ~j; j--) {
      Query(z[Mount[1][i][j]]);
      sum2[Mount[1][i][j]] = ans;
    }
  }
  for (int i = 1; i <= Q; i++)
    printf("%d\n", (sum2[i] - sum1[i]) % mod);
}
