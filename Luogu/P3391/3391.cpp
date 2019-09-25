#include <cstdio>
#include <iostream>
using namespace std;
#define ls s[0]
#define rs s[1]
int n, m, cnt, a[100003], sum;
int rt, L, R;
struct tree {
  int s[2], fa, id, key, size;
  bool tag;
} k[100003];
void update(int x) { k[x].size = k[k[x].ls].size + k[k[x].rs].size + 1; }
void pushdown(int x) {
  if (!k[x].tag)
    return;
  k[k[x].ls].tag ^= 1, k[k[x].rs].tag ^= 1;
  swap(k[x].ls, k[x].rs);
  k[x].tag = false;
}
int build(int l, int r, int fa) {
  if (l > r)
    return 0;
  int mid = (l + r) >> 1, now = ++cnt;
  k[now].id = now, k[now].fa = fa, k[now].key = a[mid], k[now].size = 1;
  k[now].ls = build(l, mid - 1, now), k[now].rs = build(mid + 1, r, now);
  if (now)
    update(now);
  return now;
}
int find(int x) {
  int now = rt;
  while (1) {
    pushdown(now);
    if (x <= k[k[now].ls].size)
      now = k[now].ls;
    else {
      x -= k[k[now].ls].size + 1;
      if (!x)
        return now;
      now = k[now].rs;
    }
  }
}
bool kind(int x) { return k[k[x].fa].rs == x; }
void rotate(int x) {
  int f = k[x].fa, ff = k[f].fa;
  pushdown(x), pushdown(f);
  bool flag = kind(x);
  k[f].s[flag] = k[x].s[flag ^ 1];
  k[k[f].s[flag]].fa = f;
  k[f].fa = x;
  k[x].fa = ff;
  k[x].s[flag ^ 1] = f;
  if (ff)
    k[ff].s[k[ff].s[1] == f] = x;
  update(f);
}
void Splay(int x, int To) {
  for (int Fa; (Fa = k[x].fa) != To; rotate(x)) {
    if (k[Fa].fa != To)
      rotate(kind(x) ^ kind(Fa) ? x : Fa);
  }
  if (!To)
    rt = x;
}
void revers(int l, int r) {
  l = find(l), r = find(r + 2);
  Splay(l, 0);
  Splay(r, l);
  k[k[k[rt].rs].ls].tag ^= 1;
}
void print(int x) {
  pushdown(x);
  if (k[x].ls)
    print(k[x].ls);
  if (k[x].key != -1e9 && k[x].key != 1e9)
    printf("%d ", k[x].key);
  if (k[x].rs)
    print(k[x].rs);
}
int main() {
  freopen("3391.in", "r", stdin);
  freopen("3391.out", "w", stdout);
  cin >> n >> m;
  a[1] = -1e9, a[n + 2] = 1e9;
  for (int i = 1; i <= n; i++)
    a[i + 1] = i;
  rt = build(1, n + 2, 0);
  while (m--) {
    scanf("%d%d", &L, &R);
    revers(L, R);
  }
  print(rt);
}
