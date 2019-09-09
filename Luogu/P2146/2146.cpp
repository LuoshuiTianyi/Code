#include <cstdio>
#include <iostream>
using namespace std;
int n, m, head[100001], to[100001], nx[100001];
int fa[100001], deep[100001], top[100001], size[100001], son[100001], x,
    d[100001], cnt;
int sum[400001], adv[400001], ans, L, R, opt;
char s[10];
void add(int u, int v) {
  to[v] = v, nx[v] = head[u];
  head[u] = v;
}
void build1(int x) {
  top[x] = x;
  size[x] = 1;
  for (int i = head[x]; i; i = nx[i]) {
    deep[to[i]] = deep[x] + 1;
    build1(to[i]);
    size[x] += size[to[i]];
    if (size[to[i]] > size[son[x]])
      son[x] = to[i];
  }
}
void build2(int x) {
  d[x] = ++cnt;
  if (son[x]) {
    top[son[x]] = top[x];
    build2(son[x]);
  }
  for (int i = head[x]; i; i = nx[i])
    if (to[i] != son[x])
      build2(to[i]);
}
void pushdown(int o, int l, int r) {
  int mid = (l + r) >> 1;
  if (adv[o] != -1) {
    sum[o * 2] = adv[o] * (mid - l + 1);
    sum[o * 2 + 1] = adv[o] * (r - mid);
    adv[o * 2] = adv[o * 2 + 1] = adv[o];
    adv[o] = -1;
  }
}
void pushup(int o) { sum[o] = sum[o * 2] + sum[o * 2 + 1]; }
void query(int o, int l, int r) {
  if (l >= L && r <= R) {
    ans += sum[o];
    return;
  }
  pushdown(o, l, r);
  int mid = (l + r) >> 1;
  if (mid >= L)
    query(o * 2, l, mid);
  if (mid < R)
    query(o * 2 + 1, mid + 1, r);
  pushup(o);
}
void add(int o, int l, int r) {
  if (l >= L && r <= R) {
    adv[o] = x;
    sum[o] = adv[o] * (r - l + 1);
    return;
  }
  pushdown(o, l, r);
  int mid = (l + r) >> 1;
  if (mid >= L)
    add(o * 2, l, mid);
  if (mid < R)
    add(o * 2 + 1, mid + 1, r);
  pushup(o);
}
void Query(int p) {
  while (p != 0) {
    L = d[top[p]], R = d[p];
    query(1, 1, n);
    p = fa[top[p]];
  }
}
void And(int p) {
  while (p != 0) {
    L = d[top[p]], R = d[p];
    add(1, 1, n);
    p = fa[top[p]];
  }
}
int main() {
  freopen("2146.in", "r", stdin);
  freopen("2146.out", "w", stdout);
  cin >> n;
  for (int i = 2; i <= n; i++) {
    scanf("%d", &fa[i]);
    fa[i] += 1;
    add(fa[i], i);
  }
  for (int i = 1; i <= n * 4; i++)
    adv[i] = -1;
  deep[1] = 1;
  build1(1);
  build2(1);
  cin >> m;
  for (int i = 1; i <= m; i++) {
    cin >> s;
    scanf("%d", &opt);
    opt++;
    if (s[0] == 'i') {
      ans = 0;
      Query(opt);
      printf("%d\n", deep[opt] - ans);
      x = 1;
      And(opt);
    } else {
      ans = 0;
      L = d[opt], R = d[opt] + size[opt] - 1;
      query(1, 1, n);
      printf("%d\n", ans);
      x = 0;
      add(1, 1, n);
    }
  }
}
