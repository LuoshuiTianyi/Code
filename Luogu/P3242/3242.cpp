#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
int n, cnt, P, Q, Ans[40001];
int cntr, head[40001], nx[80001], to[80001];
int cntd, dfn[40001], deep[40001], size[40001], f[40001][17];
int c[40001], tmp[200001];
struct node {
  int type, w, d, v, tmp, X, cl, cr;
} q[200001], q1[200001], q2[200001];
void addr(int u, int v) {
  cntr++;
  nx[cntr] = head[u], to[cntr] = v;
  head[u] = cntr;
}
void Add(int t, int cl, int cr, int w, int x) {
  cnt++;
  q[cnt].type = t, q[cnt].cl = cl, q[cnt].cr = cr, q[cnt].w = w, q[cnt].X = x;
}
bool cmp(node a, node b) { return a.X == b.X ? a.type < b.type : a.X < b.X; }
void build(int x, int fa) {
  size[x] = 1, deep[x] = deep[fa] + 1, dfn[x] = ++cntd, f[x][0] = fa;
  for (int i = 1; i <= 16; i++)
    f[x][i] = f[f[x][i - 1]][i - 1];
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != fa)
      build(to[i], x), size[x] += size[to[i]];
}
int get_fir(int u, int v) {
  for (int i = 16; i >= 0; i--)
    if (deep[f[v][i]] > deep[u])
      v = f[v][i];
  return v;
}
void add(int k, int x) {
  for (int i = k; i <= n; i += i & -i)
    c[i] += x;
}
int query(int k) {
  int ans = 0;
  for (int i = k; i > 0; i -= i & -i)
    ans += c[i];
  return ans;
}
void Solve(int L, int R, int l, int r) {
  if (L > R)
    return;
  if (l == r) {
    for (int i = L; i <= R; i++)
      if (q[i].type == 2)
        Ans[q[i].d] = l;
    return;
  }
  int mid = (l + r) >> 1;
  for (int i = L; i <= R; i++) {
    if (q[i].type == 1 && q[i].w <= mid)
      add(q[i].cl, 1), add(q[i].cr, -1);
    if (q[i].type == 2)
      tmp[i] = query(dfn[q[i].v]);
    if (q[i].type == 3 && q[i].w <= mid)
      add(q[i].cl, -1), add(q[i].cr, 1);
  }
  int len1 = 0, len2 = 0;
  for (int i = L; i <= R; i++) {
    if (q[i].type == 1 && q[i].w <= mid)
      add(q[i].cl, -1), add(q[i].cr, 1);
    if (q[i].type == 3 && q[i].w <= mid)
      add(q[i].cl, 1), add(q[i].cr, -1);
    if (q[i].type == 2)
      if (tmp[i] + q[i].tmp >= q[i].w)
        q1[++len1] = q[i];
      else
        q[i].tmp += tmp[i], q2[++len2] = q[i];
    else if (q[i].w <= mid)
      q1[++len1] = q[i];
    else
      q2[++len2] = q[i];
  }
  for (int i = 1; i <= len1; i++)
    q[L + i - 1] = q1[i];
  for (int i = 1; i <= len2; i++)
    q[L + len1 + i - 1] = q2[i];
  Solve(L, L + len1 - 1, l, mid);
  Solve(L + len1, R, mid + 1, r);
}
int main() {
  freopen("3242.in", "r", stdin);
  freopen("3242.out", "w", stdout);
  cin >> n >> P >> Q;
  int u, v, w;
  for (int i = 1; i < n; i++) {
    scanf("%d%d", &u, &v);
    addr(u, v), addr(v, u);
  }
  build(1, 0);
  for (int i = 1; i <= P; i++) {
    scanf("%d%d%d", &u, &v, &w);
    if (dfn[u] > dfn[v])
      swap(u, v);
    if (dfn[v] >= dfn[u] && dfn[v] <= dfn[u] + size[u] - 1) {
      int z = get_fir(u, v);
      Add(1, dfn[v], dfn[v] + size[v], w, 1);
      Add(3, dfn[v], dfn[v] + size[v], w, dfn[z] - 1);
      Add(1, dfn[z] + size[z], n + 1, w, dfn[v]);
      Add(3, dfn[z] + size[z], n + 1, w, dfn[v] + size[v] - 1);
    } else {
      Add(1, dfn[v], dfn[v] + size[v], w, dfn[u]);
      Add(3, dfn[v], dfn[v] + size[v], w, dfn[u] + size[u] - 1);
    }
  }
  for (int i = 1; i <= Q; i++) {
    scanf("%d%d%d", &u, &v, &w);
    if (dfn[u] > dfn[v])
      swap(u, v);
    cnt++;
    q[cnt].type = 2, q[cnt].X = dfn[u], q[cnt].v = v, q[cnt].w = w,
    q[cnt].d = i;
  }
  sort(q + 1, q + cnt + 1, cmp);
  Solve(1, cnt, 0, 1e9 + 1);
  for (int i = 1; i <= Q; i++)
    printf("%d\n", Ans[i]);
}
