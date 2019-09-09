#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
int n, cnt, Fa[500001], head[500001], nx[500001], to[500001];
int fa[500001], size[500001];
long long w[500001], ans;
bool vis[500001], flag;
struct node {
  int x, size;
  long long w;
  bool operator<(const node b) const { return w * b.size > b.w * size; }
};
priority_queue<node> q;
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
void Push(int x) { q.push(node{x, size[x], w[x]}); }
void Merge(int f, int x) {
  ans += 1ll * size[f] * w[x];
  w[f] += w[x];
  size[f] += size[x];
}
void dfs(int x) {
  if (flag)
    return;
  if (vis[x])
    flag = 1;
  vis[x] = 1, cnt++;
  for (int i = head[x]; i; i = nx[i])
    dfs(to[i]);
}
int main() {
  freopen("4437.in", "r", stdin);
  freopen("4437.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &Fa[i]);
    nx[i] = head[Fa[i]], to[i] = i;
    head[Fa[i]] = i;
  }
  dfs(0);
  if (cnt < n || flag) {
    cout << "-1";
    return 0;
  }
  for (int i = 1; i <= n; i++) {
    scanf("%lld", &w[i]);
    ans += w[i];
    fa[i] = i, size[i] = 1;
    Push(i);
  }
  int x, f;
  while (!q.empty()) {
    x = q.top().x;
    q.pop();
    if (x != find(x))
      continue;
    x = find(x);
    fa[x] = f = find(Fa[x]);
    Merge(f, x);
    if (f)
      Push(f);
  }
  cout << ans;
}
