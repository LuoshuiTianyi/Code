#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n, m, head[50001], nx[100001], to[100001], w[100001], book[50001],
    sum[50001], up[50001];
long long f[50001], l, r, ans;
bool flag1, flag2;
struct tree {
  int fa, deep, d;
} k[50001];
void add(int u, int v, int W, int d) {
  to[d] = v;
  nx[d] = head[u];
  w[d] = W;
  head[u] = d;
}
void build(int x) {
  k[x].d = x;
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != k[x].fa) {
      k[to[i]].deep = k[x].deep + 1;
      k[to[i]].fa = x;
      up[to[i]] = w[i];
      build(to[i]);
    }
}
bool cmp(tree a, tree b) { return a.deep > b.deep; }
bool pd(long long num) {
  memset(f, 0, sizeof(f));
  int tot = 0;
  for (int i = 1; i <= n; i++) {
    int p = k[i].d, cnt = 0;
    long long b[50001];
    for (int j = head[p]; j; j = nx[j])
      if (to[j] != k[i].fa)
        b[++cnt] = f[to[j]] + up[to[j]];
    sort(b + 1, b + cnt + 1);
    int topl = 1, topr = cnt, top, maxx = 0;
    while (b[topr] >= num) {
      topr--;
      maxx++;
    }
    while (topl < topr) {
      if (b[topl] + b[topr] >= num) {
        topr--;
        maxx++;
      }
      topl++;
    }
    tot += maxx;
    int L = 1, R = cnt;
    while (L <= R) {
      int mid = (L + R) / 2;
      topl = 1, topr = cnt, top = 0;
      while (b[topr] >= num) {
        if (topr == mid) {
          topr--;
          continue;
        }
        topr--;
        top++;
      }
      while (topl < topr) {
        if (topl == mid)
          topl++;
        if (topr == mid)
          topr--;
        if (topl >= topr)
          break;
        if (b[topl] + b[topr] >= num) {
          topr--;
          top++;
        }
        topl++;
      }
      if (top == maxx) {
        f[p] = max(f[p], b[mid]);
        L = mid + 1;
      } else
        R = mid - 1;
    }
  }
  if (tot >= m)
    return true;
  return false;
}
int main() {
  freopen("5021.in", "r", stdin);
  freopen("5021.out", "w", stdout);
  cin >> n >> m;
  int u, v, W;
  for (int i = 1; i < n; i++) {
    scanf("%d%d%d", &u, &v, &W);
    add(u, v, W, i);
    add(v, u, W, i + n);
  }
  build(1);
  sort(k + 1, k + n + 1, cmp);
  l = 1, r = 1e12;
  while (l <= r) {
    long long mid = (l + r) / 2;
    if (pd(mid)) {
      l = mid + 1;
      ans = max(ans, mid);
    } else
      r = mid - 1;
  }
  cout << ans;
}
