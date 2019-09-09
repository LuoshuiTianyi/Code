#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n, m, head[300001], book[300001], f[300001][20], ans, change[300001],
    jl[300001], num[300001], top[300001], son[300001], size[300001];
struct tree {
  int fa, deep;
} k[300001];
struct node {
  int u, v, lenth, lca;
} s[300001];
struct egde {
  int next, to, w;
} g[600001];
int cmp(node x, node y) { return x.lenth > y.lenth; }
void read(int &x) {
  x = 0;
  char number = getchar();
  while (!isdigit(number))
    number = getchar();
  while (isdigit(number)) {
    x = x * 10 + number - '0';
    number = getchar();
  }
}
void build1(int x) {
  top[x] = x;
  size[x] = 1;
  for (int p = head[x]; p; p = g[p].next)
    if (g[p].to != k[x].fa) {
      k[g[p].to].deep = k[x].deep + 1;
      k[g[p].to].fa = x;
      jl[g[p].to] = jl[x] + g[p].w;
      build1(g[p].to);
      size[x] += size[g[p].to];
      if (size[g[p].to] > size[son[x]])
        son[x] = g[p].to;
    }
}
void build2(int x) {
  if (son[x]) {
    top[son[x]] = top[x];
    build2(son[x]);
  }
  for (int i = head[x]; i; i = g[i].next)
    if (g[i].to != k[x].fa && g[i].to != son[x])
      build2(g[i].to);
}
int dfs(int x) {
  book[x] = 1;
  num[x] += change[x];
  int p = head[x];
  while (p) {
    if (!book[g[p].to])
      num[x] += dfs(g[p].to);
    p = g[p].next;
  }
  return num[x];
}
bool pd(int mid) {
  int top = 1;
  for (int i = 1; i <= n; i++) {
    num[i] = 0;
    change[i] = 0;
    book[i] = 0;
  }
  while (s[top].lenth > mid && top <= m)
    top++;
  top--;
  for (int i = 1; i <= top; i++) {
    change[s[i].u]++;
    change[s[i].v]++;
    change[s[i].lca] -= 2;
  }
  dfs(1);
  int maxx = 0;
  for (int i = 1; i <= n; i++)
    if (num[i] == top)
      maxx = max(maxx, jl[i] - jl[k[i].fa]);
  if (s[1].lenth - maxx <= mid)
    return true;
  return false;
}
int LCA(int a, int b) {
  while (top[a] != top[b]) {
    if (k[top[a]].deep < k[top[b]].deep)
      swap(a, b);
    a = k[top[a]].fa;
  }
  if (k[a].deep > k[b].deep)
    swap(a, b);
  return a;
}
int main() {
  freopen("2680.in", "r", stdin);
  freopen("2680.out", "w", stdout);
  read(n);
  read(m);
  int u, v, w;
  for (int i = 1; i < n; i++) {
    read(u);
    read(v);
    read(w);
    g[i].to = v;
    g[i].next = head[u];
    head[u] = i;
    g[i + n].to = u;
    g[i + n].next = head[v];
    head[v] = i + n;
    g[i].w = g[i + n].w = w;
  }
  k[1].deep = 1;
  build1(1);
  build2(1);
  for (int i = 1; i <= m; i++) {
    read(s[i].u);
    read(s[i].v);
    s[i].lca = LCA(s[i].u, s[i].v);
    s[i].lenth = jl[s[i].u] + jl[s[i].v] - jl[s[i].lca] * 2;
  }
  sort(s + 1, s + m + 1, cmp);
  int l = 1, r = s[1].lenth;
  ans = r;
  while (l <= r) {
    int mid = (l + r) / 2;
    if (pd(mid)) {
      ans = min(ans, mid);
      r = mid - 1;
    } else
      l = mid + 1;
  }
  cout << ans;
}
