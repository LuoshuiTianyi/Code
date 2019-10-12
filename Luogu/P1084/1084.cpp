#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n, m, start[100001], nx[100001], to[100001], w[100001], head[50001],
    fa[50001], deep[50001], f[50001][17], top, book[50001], two[50001],
    son[50001], sum[50001], top2, Del;
long long lz[50001], L, R, ans = 1e18, maxx;
void add(int u, int v, int z, int d) {
  nx[d] = head[u];
  w[d] = z;
  to[d] = v;
  head[u] = d;
}
struct node {
  int d, before;
  long long sc;
} k[50001];
struct no {
  int w;
} a[50001];
bool cmp(node x, node y) { return x.sc < y.sc; }
bool cmp2(no x, no y) { return x.w < y.w; }
void build(int x) {
  if (deep[x] == 1)
    two[x] = x;
  maxx = max(maxx, lz[x]);
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != fa[x]) {
      son[x]++;
      fa[to[i]] = x;
      lz[to[i]] = lz[x] + w[i];
      deep[to[i]] = deep[x] + 1;
      if (deep[x] >= 1)
        two[to[i]] = two[x];
      build(to[i]);
    }
}
void dfs(int x) {
  if (book[x])
    return;
  bool flag = true, flag2 = false;
  for (int i = head[x]; i; i = nx[i]) {
    if (to[i] != fa[x]) {
      flag2 = true;
      if (!book[to[i]])
        flag = false;
      dfs(to[i]);
    }
  }
  if (flag && flag2)
    book[x] = 1;
}
bool pd(long long limit) {
  for (int i = 1; i <= m; i++) {
    if (lz[start[i]] <= limit) {
      k[++top].d = i;
      k[top].sc = limit - lz[start[i]];
      k[top].before = two[start[i]];
    } else {
      int a = start[i];
      long long p = limit;
      for (int j = 16; j >= 0; j--)
        if (lz[a] - lz[f[a][j]] <= p) {
          p -= (lz[a] - lz[f[a][j]]);
          a = f[a][j];
        }
      book[a] = 1;
    }
  }
  dfs(1);
  sort(k + 1, k + top + 1, cmp);
  for (int i = 1; i <= top; i++)
    if (!book[k[i].before])
      if (k[i].sc < lz[k[i].before]) {
        Del++;
        k[i].sc = 1e10;
        book[k[i].before] = 1;
      }
  sort(k + 1, k + top + 1, cmp);
  top -= Del;
  for (int i = head[1]; i; i = nx[i])
    if (!book[to[i]])
      a[++top2].w = w[i];
  sort(a + 1, a + top2 + 1, cmp2);
  int l, r;
  if (top < top2)
    return false;
  for (l = 0, r = 1; r <= top2; r++) {
    l++;
    if (l > top)
      return false;
    while (k[l].sc < a[r].w) {
      l++;
      if (l > top)
        return false;
    }
  }
  return true;
}
int main() {
  freopen("1084.in", "r", stdin);
  freopen("1084.out", "w", stdout);
  cin >> n;
  for (int i = 1; i < n; i++) {
    int u, v, z;
    cin >> u >> v >> z;
    add(u, v, z, i);
    add(v, u, z, i + n);
  }
  cin >> m;
  for (int i = 1; i <= m; i++)
    cin >> start[i];
  build(1);
  if (m < son[1]) {
    cout << "-1";
    return 0;
  }
  lz[0] = -1e18;
  for (int i = 1; i <= n; i++)
    f[i][0] = fa[i];
  for (int j = 1; j <= 16; j++)
    for (int i = 1; i <= n; i++)
      f[i][j] = f[f[i][j - 1]][j - 1];
  L = 1;
  R = maxx * 2;
  long long mid;
  while (L <= R) {
    top = 0;
    top2 = 0;
    Del = 0;
    memset(book, 0, sizeof(book));
    memset(sum, 0, sizeof(sum));
    mid = (L + R) / 2;
    if (pd(mid)) {
      R = mid - 1;
      ans = min(ans, mid);
    } else
      L = mid + 1;
  }
  cout << ans;
}
