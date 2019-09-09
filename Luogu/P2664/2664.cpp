#include <cstdio>
#include <iostream>
using namespace std;
int n, col[100001];
int rt, sum, top, Y, maxs[100001], size[100001], now[100001], cbook[100001],
    cnt[100001];
int head[100001], nx[200001], to[200001];
bool vis[100001], Book[100001];
long long Sum, ans[100001];
void add(int u, int v, int d) {
  to[d] = v, nx[d] = head[u];
  head[u] = d;
}
void getrt(int x, int fa) {
  size[x] = 1, maxs[x] = 0;
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != fa && !vis[to[i]]) {
      getrt(to[i], x);
      size[x] += size[to[i]];
      maxs[x] = max(maxs[x], size[to[i]]);
    }
  maxs[x] = max(maxs[x], sum - size[x]);
  if (maxs[x] < maxs[rt]) rt = x;
}
void getsize(int x, int fa) {
  size[x] = 1;
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != fa && !vis[to[i]]) getsize(to[i], x), size[x] += size[to[i]];
}
void getcol(int x, int fa) {
  if (!now[col[x]]) {
    cnt[col[x]] += size[x];
    Sum += size[x];
  }
  if (!Book[col[x]]) cbook[++top] = col[x], Book[col[x]] = true;
  now[col[x]]++;
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != fa && !vis[to[i]]) getcol(to[i], x);
  now[col[x]]--;
}
void delcol(int x, int fa) {
  if (!now[col[x]]) {
    cnt[col[x]] -= size[x];
    Sum -= size[x];
  }
  now[col[x]]++;
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != fa && !vis[to[i]]) delcol(to[i], x);
  now[col[x]]--;
}
void Count(int x, int fa, int num, long long tot) {
  if (!now[col[x]]) num++, tot += cnt[col[x]];
  now[col[x]]++;
  ans[x] += Sum - tot + num * Y;
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != fa && !vis[to[i]]) Count(to[i], x, num, tot);
  now[col[x]]--;
}
void work(int x) {
  getsize(x, 0);
  Sum = 0, top = 0;
  getcol(x, 0);
  for (int i = head[x]; i; i = nx[i])
    if (!vis[to[i]]) {
      now[col[x]]++, delcol(to[i], x), cnt[col[x]] -= size[to[i]],
          Sum -= size[to[i]];
      Y = size[x] - size[to[i]], Count(to[i], x, 0, 0);
      getcol(to[i], x), now[col[x]]--, cnt[col[x]] += size[to[i]],
          Sum += size[to[i]];
    }
  ans[x] += Sum - cnt[col[x]] + size[x];
  for (int i = 1; i <= top; i++) Book[cbook[i]] = false, cnt[cbook[i]] = 0;
}
void solve(int x) {
  vis[x] = true;
  work(x);
  for (int i = head[x]; i; i = nx[i])
    if (!vis[to[i]]) {
      rt = 0, sum = size[to[i]];
      getrt(to[i], x);
      solve(rt);
    }
}
int main() {
  freopen("2664.in", "r", stdin);
  freopen("2664.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++) scanf("%d", &col[i]);
  int u, v;
  for (int i = 1; i < n; i++) {
    scanf("%d%d", &u, &v);
    add(u, v, i);
    add(v, u, i + n);
  }
  maxs[rt = 0] = sum = n;
  getrt(1, 0);
  solve(rt);
  for (int i = 1; i <= n; i++) printf("%lld\n", ans[i]);
}
