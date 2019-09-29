#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
#define LL long long
#define go(x, i, v) for (int i = hd[x], v = to[i]; i; v = to[i = nx[i]])
#define inline __inline__ __attribute__((always_inline))
inline LL read() {
  LL x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-') w = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 1e5 + 5;
int n;
LL Ans[Max_n];
int cntr = 1, hd[Max_n], nx[Max_n << 1], to[Max_n << 1];
int num[Max_n], U[Max_n], V[Max_n], B[Max_n], C[Max_n];
int fa[Max_n], rk[Max_n], dn[Max_n];
int w;
struct node {
  int fa, v, size, cnt, s[2];
};
struct Splay {
#define ls(x) k[x].s[0]
#define rs(x) k[x].s[1]
  vector<node> k;
  int rt;
  bool kd(int x) { return rs(k[x].fa) == x; }
  int nx(int x) {
    if (k[x].v == w) return 0;
    return k[x].v < w ? rs(x) : ls(x);
  }
  void update(int x) {
    if (!x) return;
    k[x].size = k[ls(x)].size + k[rs(x)].size;
  }
  void rotate(int x) {
    bool t = kd(x);
    int A = k[x].fa, B = k[A].fa, C = k[x].s[!t];
    k[x].s[!t] = A, k[A].s[t] = C, k[B].s[kd(A)] = x;
    k[x].fa = B, k[A].fa = x, k[C].fa = A;
    update(A), update(x);
  }
  void splay(int x, int to) {
    if (!x) return;
    for (int fa; (fa = k[x].fa) != to; rotate(x))
      if (k[fa].fa != to) rotate(kd(x) ^ kd(fa) ? x : fa);
    if (!to) rt = x;
  }
  void add() {
    int x = rt;
    while (nx(x)) x = nx(x);
    if (w == k[x].v) {
      k[x].cnt++, k[x].size++, splay(x, 0);
      return;
    }
    k.push_back((node){x, w, 1, 1, {0, 0}});
    if (w < k[x].v)
      ls(x) = k.size() - 1;
    else
      rs(x) = k.size() - 1;
    update(k.size() - 1);
    splay(k.size() - 1, 0);
  }
  void del() {
    int x = rt;
    while (nx(x)) x = nx(x);
    splay(x, 0);
    if (--k[x].cnt) {
      update(x);
      return;
    }
    int q = ls(x);
    if (!q) {
      rt = rs(x), k[rs(x)].fa = 0;
    } else {
      while (rs(q)) q = rs(q);
      splay(q, x);
      k[rs(x)].fa = q, rs(q) = rs(x), rt = q, update(q);
    }
    k.pop_back();
  }
  int pre() {
    int x = rt, ans = 0;
    for (; nx(x); x = nx(x))
      if (k[x].v < n) ans += k[ls(x)].size + k[x].cnt;
    int tp = ans + k[ls(x)].size + k[x].cnt;
    splay(x, 0);
    return tp;
  }
  void Print(int x) {
    if (!x) return;
    Print(ls(x));
    printf("%d ", k[x].v);
    Print(rs(x));
  }
} c[Max_n];
void addr(int u, int v) {
  cntr++;
  nx[cntr] = hd[u], to[cntr] = v;
  hd[u] = cntr;
}
bool cmp(int x, int y) { return B[x] < B[y]; }
void build(int x, int f) {
  fa[x] = f;
  go(x, i, v) if (v != f) build(v, x);
}
void addc(int k, int x) {
  if (!k) return;
  w = x;
  for (int i = k; i <= n; i += i & -i) c[i].add();
}
void delc(int k, int x) {
  w = x;
  for (int i = k; i <= n; i += i & -i) c[i].del();
}
int query(int R, int B) {
  w = B;
  int ans = 0;
  for (int i = R; i > 0; i -= i & -i) ans += c[i].pre();
  return ans;
}
void Count(int x, int f, LL ans, int tot) {
  int now = dn[x], p = 0, l = dn[x], r = dn[x] + n;
  for (int i = 1; i <= n; i++) c[i].Print(c[i].rt);
  cout << endl;
  while (l <= r) {
    int mid = l + r >> 1;
    if (query(rk[x] - 1, mid) >= (tot + 1 >> 1))
      p = mid, r = mid - 1;
    else
      l = mid + 1;
  }
  now = max(now, p);
  ans += now, addc(rk[x], now);
  go(x, i, v) if (v != f) Count(v, x, ans, tot + 1);
  delc(rk[x], now);
  Ans[x] += ans;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("C.in", "r", stdin);
  freopen("C.out", "w", stdout);
#endif
  n = read();
  int tp[Max_n];
  for (int i = 1; i <= n; i++) {
    U[i] = read(), V[i] = read(), tp[i] = B[i] = read(), C[i] = read();
    num[i] = i, addr(U[i], V[i]), addr(V[i], U[i]);
  }
  sort(num + 1, num + n + 1, cmp);
  int cnt = 0;
  tp[0] = -1;
  for (int i = 1; i <= n; i++) {
    if (tp[num[i]] != tp[num[i - 1]]) cnt++;
    B[num[i]] = cnt;
  }
  for (int i = 1; i <= n; i++) c[i].k.push_back((node){0, 0, 0, 0, {0, 0}});
  build(0, 0);
  for (int i = 1; i <= n; i++) {
    if (fa[U[i]] == V[i]) swap(U[i], V[i]);
    rk[V[i]] = B[i], dn[V[i]] = C[i];
  }
  Count(0, -1, 0, 0);
}
