#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#define fr first
#define sc second
#include <map>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10, LOG = 10;
namespace Treap {
int ch[N * LOG * LOG][2], v[N * LOG * LOG], rd[N * LOG * LOG],
    ct[N * LOG * LOG], sz[N * LOG * LOG], cnt;
void updata(int x) { sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + ct[x]; }
void rotate(int &f, int k) {
  int x = ch[f][k];
  ch[f][k] = ch[x][k ^ 1];
  ch[x][k ^ 1] = f;
  updata(f);
  updata(x);
  f = x;
}
void insert(int &x, int cc) {
  if (!x) {
    x = ++cnt;
    sz[x] = 1;
    ct[x] = 1;
    v[x] = cc;
    rd[x] = rand();
    return;
  }
  sz[x]++;
  if (v[x] == cc) {
    ct[x]++;
    return;
  }
  int k = v[x] < cc;
  insert(ch[x][k], cc);
  if (rd[x] > rd[ch[x][k]]) rotate(x, k);
}
void del(int &x, int cc) {  // if(!x)return;
  if (v[x] == cc) {
    if (ct[x] > 1) {
      ct[x]--;
      sz[x]--;
      return;
    }
    bool k = rd[ch[x][0]] > rd[ch[x][1]];
    if (!ch[x][0] || !ch[x][1])
      x = ch[x][0] + ch[x][1];
    else
      rotate(x, k), del(x, cc);
    return;
  }
  sz[x]--;
  del(ch[x][v[x] < cc], cc);
}
int getrk(int x, int cc) {
  if (!x) return 0;
  if (v[x] == cc) return sz[ch[x][0]] + ct[x];
  if (v[x] > cc) return getrk(ch[x][0], cc);
  return sz[ch[x][0]] + ct[x] + getrk(ch[x][1], cc);
}
int getkth(int x, int kth) {
  if (kth <= sz[ch[x][0]]) return getkth(ch[x][0], kth);
  if (kth <= sz[ch[x][0]] + ct[x]) return v[x];
  return getkth(ch[x][1], kth - sz[ch[x][0]] - ct[x]);
}
};  // namespace Treap
struct path {
  int y, nxt, r, c;
} g[N << 1];
int h[N];
int n, rt[N], t[N];
void insert(int pos, int x) {
  for (; pos <= n; pos += pos & -pos) Treap::insert(rt[pos], x);
}
void del(int pos, int x) {
  for (; pos <= n; pos += pos & -pos) Treap::del(rt[pos], x);
}
int ask(int R, int C) {
  int ret = 0;
  if (C < 0) return 0;
  for (; R; R -= R & -R) ret += Treap::getrk(rt[R], C);
  return ret;
}
int qry(int R, int all) {
  static int l, r, mid;
  l = 0;
  r = 1e9 + N;
  while (l < r) {
    mid = l + r >> 1;
    if (ask(R, mid - 1) >= (all + 1) / 2)
      r = mid;
    else
      l = mid + 1;
  }
  return r;
}
ll ans[N];
void dfs(int x, int f, int d, ll s) {
  int cost = 0, all = d ? ask(g[f].r - 1, 1e9) : 0;
  if (!all && d) {
    cost = g[f].c;
    insert(g[f].r, cost);
  } else if (d > 1)
    cost = qry(g[f].r - 1, all), insert(g[f].r, cost);
  s += cost;
  ans[x] = s - d;
  for (int i = h[x]; i; i = g[i].nxt)
    if (i != (f ^ 1)) dfs(g[i].y, i, d + 1, s);
  if (d) del(g[f].r, cost);
}
int x, y, z, c;
int main() {
  freopen("C.in", "r", stdin);
  freopen("C.ans", "w", stdout);
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d%d%d%d", &x, &y, &z, &c);
    c++;
    g[i * 2] = path{y, h[x], z, c};
    h[x] = i * 2;
    g[i * 2 + 1] = path{x, h[y], z, c};
    h[y] = i * 2 + 1;
    t[i] = z;
  }
  sort(t + 1, t + n + 1);
  for (int i = 2; i <= n * 2 + 1; i += 2)
    g[i].r = g[i + 1].r = lower_bound(t + 1, t + n + 1, g[i].r) - t;
  dfs(0, 0, 0, 0);
  for (int i = 1; i <= n; i++) printf("%lld ", ans[i]);
}
