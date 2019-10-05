#include <cstdio>
#include <iostream>
using namespace std;
int n, m, cnt, opt, head[100001], nx[200001], to[200001];
int fa[100001][18], size[100001], deep[100001], d[100001];
int mid, now, c[200001], num[200001], tmp[200001], Ans[200001];
struct Que {
  int u, v, w, id, type;
} q[200001], q1[200001], q2[200001];
void addroad(int u, int v, int d) {
  nx[d] = head[u], to[d] = v;
  head[u] = d;
}
void build(int x, int pa) {
  size[x] = 1, fa[x][0] = pa, deep[x] = deep[pa] + 1, d[x] = ++cnt;
  for (int i = 1; i <= 17; i++)
    fa[x][i] = fa[fa[x][i - 1]][i - 1];
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != pa) {
      build(to[i], x);
      size[x] += size[to[i]];
    }
}
int get_lca(int u, int v) {
  if (deep[u] < deep[v])
    swap(u, v);
  for (int i = 17; i >= 0; i--)
    if (deep[fa[u][i]] >= deep[v])
      u = fa[u][i];
  for (int i = 17; i >= 0; i--)
    if (fa[u][i] != fa[v][i])
      u = fa[u][i], v = fa[v][i];
  return u == v ? u : fa[u][0];
}
void add(int k, int x) {
  if (!k)
    return;
  k = d[k];
  for (int i = k; i <= n; i += i & -i)
    c[i] += x;
}
int query(int k) {
  int ans = 0;
  for (int i = k; i > 0; i -= i & -i)
    ans += c[i];
  return ans;
}
void Add(int u, int v, int x) {
  int lca = get_lca(u, v);
  add(u, x), add(v, x);
  add(lca, -x), add(fa[lca][0], -x);
  now += x;
}
void Solve(int L, int R, int l, int r) {
  if (L > R)
    return;
  if (l == r) {
    for (int i = L; i <= R; i++)
      if (q[i].type == 2)
        Ans[q[i].id] = l;
    return;
  }
  mid = (l + r) >> 1, now = 0;
  for (int i = L; i <= R; i++)
    if (q[i].type != 2 && q[i].w >= mid)
      Add(q[i].u, q[i].v, q[i].type == 1 ? -1 : 1);
    else if (q[i].type == 2)
      num[i] = now,
      tmp[i] = query(d[q[i].u] + size[q[i].u] - 1) - query(d[q[i].u] - 1);
  int len1 = 0, len2 = 0;
  for (int i = L; i <= R; i++) {
    if (q[i].type != 2) {
      if (q[i].w >= mid)
        Add(q[i].u, q[i].v, q[i].type == 1 ? 1 : -1), q2[++len2] = q[i];
      else
        q1[++len1] = q[i];
    } else if (tmp[i] == num[i])
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
  freopen("3250.in", "r", stdin);
  freopen("3250.out", "w", stdout);
  cin >> n >> m;
  int u, v;
  for (int i = 1; i < n; i++) {
    scanf("%d%d", &u, &v);
    addroad(u, v, i), addroad(v, u, i + n);
  }
  build(1, 0);
  cnt = 0;
  for (int i = 1; i <= m; i++) {
    scanf("%d", &opt);
    q[i].type = opt;
    if (opt == 0)
      scanf("%d%d%d", &q[i].u, &q[i].v, &q[i].w);
    if (opt == 1) {
      scanf("%d", &u);
      q[i].u = q[u].u, q[i].v = q[u].v, q[i].w = q[u].w;
    }
    if (opt == 2)
      scanf("%d", &q[i].u), q[i].id = ++cnt;
  }
  Solve(1, m, 0, 1e9 + 1);
  for (int i = 1; i <= cnt; i++)
    if (!Ans[i])
      printf("-1\n");
    else
      printf("%d\n", Ans[i] - 1);
}
