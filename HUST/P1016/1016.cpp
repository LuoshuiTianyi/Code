#include <cstdio>
#include <iostream>
#include <set>
using namespace std;
int n, m, opt, pos, ans, Ans[1000001];
int head[1000001], nx[2000001], to[2000001], fa[1000001], size[1000001];
int cnt, top[1000001], son[1000001], id[1000001];
bool black[1000001];
pair<int, int> tree[1000001];
set<pair<int, int>> s[1000001];
void add(int u, int v, int d) {
  to[d] = v, nx[d] = head[u];
  head[u] = d;
}
void build1(int x) {
  size[x] = 1;
  top[x] = x;
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != fa[x]) {
      fa[to[i]] = x;
      tree[to[i]].first = tree[x].first + 1;
      build1(to[i]);
      size[x] += size[to[i]];
      if (size[to[i]] > size[son[x]])
        son[x] = to[i];
    }
}
void build2(int x) {
  id[x] = ++cnt;
  if (son[x]) {
    top[son[x]] = top[x];
    build2(son[x]);
  }
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != fa[x] && to[i] != son[x])
      build2(to[i]);
}
void Query() {
  ans = 1e9;
  int now = pos;
  while (now != 0) {
    int nx = Ans[top[now]];
    if (nx < 1e9 && id[nx] <= id[now])
      ans = min(ans, nx);
    now = fa[top[now]];
  }
}
int main() {
  freopen("1016.in", "r", stdin);
  freopen("1016.out", "w", stdout);
  cin >> n >> m;
  int u, v;
  for (int i = 1; i < n; i++) {
    scanf("%d%d", &u, &v);
    add(u, v, i), add(v, u, i + n);
  }
  tree[1].first = 1;
  build1(1);
  build2(1);
  for (int i = 1; i <= n; i++) {
    tree[i].second = i;
    Ans[i] = 1e9;
  }
  while (m--) {
    scanf("%d%d", &opt, &pos);
    if (!opt) {
      black[pos] ^= 1;
      if (black[pos])
        s[top[pos]].insert(tree[pos]);
      else
        s[top[pos]].erase(tree[pos]);
      Ans[top[pos]] = (*s[top[pos]].begin()).second;
      if (!s[top[pos]].size())
        Ans[top[pos]] = 1e9;
    } else {
      Query();
      if (ans != 1e9)
        printf("%d\n", ans);
      else
        printf("-1\n");
    }
  }
}
