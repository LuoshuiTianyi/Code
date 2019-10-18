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
int s[Max_n];
int w;
struct node {
  int fa, v, size, cnt, s[2];
  void init() { fa = v = size = cnt = s[0] = s[1] = 0; }
};
struct Splay {
#define ls(x) k[x].s[0]
#define rs(x) k[x].s[1]
  vector<node> k;
  int rt, cntn = 0;
  inline bool kd(int x) { return rs(k[x].fa) == x; }
  inline void upd(int x) {
    if (!x) return;
    k[x].size = k[ls(x)].size + k[rs(x)].size + k[x].cnt;
  }
  inline int nx(int x) {
    if (k[x].v == w) return 0;
    return k[x].v > w ? ls(x) : rs(x);
  }
  inline void rotate(int x) {
    bool t = kd(x);
    int A = k[x].fa, B = k[A].fa, C = k[x].s[!t];
    k[A].s[t] = C, k[x].s[!t] = A, k[B].s[kd(A)] = x;
    k[A].fa = x, k[x].fa = B, k[C].fa = A;
    upd(A), upd(x), k[0].init();
  }
  inline void splay(int x, int to) {
    for (int fa; (fa = k[x].fa) != to; rotate(x))
      if (k[fa].fa != to) rotate(kd(x) ^ kd(fa) ? x : fa);
    if (!to) rt = x;
  }
  inline void add() {
    int x = rt;
    while (nx(x)) x = nx(x);
    if (k[x].v == w) {
      k[x].cnt++, k[x].size++, splay(x, 0);
      return;
    }
    cntn++, k.push_back((node){x, w, 1, 1, {0, 0}});
    if (!x)
      rt = cntn;
    else if (w < k[x].v)
      ls(x) = cntn;
    else
      rs(x) = cntn;
    upd(cntn), splay(cntn, 0);
  }
  inline void del() {
    int x = rt;
    while (nx(x)) x = nx(x);
    splay(x, 0);
    if (--k[x].cnt) {
      upd(x);
      return;
    }
    int q = ls(x);
    if (!q) {
      k[rt = rs(x)].fa = 0;
    } else {
      while (rs(q)) q = rs(q);
      splay(q, x);
      rt = q, rs(q) = rs(x), k[rs(x)].fa = q, k[q].fa = 0, upd(q);
    }
  }
  inline int pre() {
    int res = 0, x = rt;
    for (; nx(x); x = nx(x))
      if (k[x].v <= w) res += k[ls(x)].size + k[x].cnt;
    if (k[x].v <= w) res += k[ls(x)].size + k[x].cnt;
    if (x) splay(x, 0);
    return res;
  }
} c[Max_n];
inline void addr(int u, int v) {
  cntr++;
  nx[cntr] = hd[u], to[cntr] = v;
  hd[u] = cntr;
}
inline bool cmp(int x, int y) { return B[x] < B[y]; }
void build(int x, int f) {
  fa[x] = f;
  go(x, i, v) if (v != f) build(v, x);
}
inline void addc(int k, int x) {
  if (!k) return;
  w = x;
  for (int i = k; i <= n; i += i & -i) c[i].add();
}
inline void delc(int k, int x) {
  if (!k) return;
  w = x;
  for (int i = k; i <= n; i += i & -i) c[i].del();
}
inline int query(int R, int B) {
  w = B - 1;
  int ans = 0;
  for (int i = R; i > 0; i -= i & -i) ans += c[i].pre();
  return ans;
}
inline void ad(int k, int x) {
  if (!k) return;
  for (int i = k; i <= n; i += i & -i) s[i] += x;
}
inline int qry(int k) {
  int ans = 0;
  for (int i = k; i > 0; i -= i & -i) ans += s[i];
  return ans;
}
void Count(int x, int f, LL ans) {
  int now = dn[x], l = 1, r = 1e9 + n;
  ad(rk[x], 1);
  int sum = qry(rk[x] - 1);
  if (sum) {
    while (l <= r) {
      int mid = l + r >> 1;
      if (query(rk[x] - 1, mid) >= (sum + 1 >> 1))
        now = mid, r = mid - 1;
      else
        l = mid + 1;
    }
  }
  ans += now, addc(rk[x], now);
  Ans[x] = ans;
  go(x, i, v) if (v != f) Count(v, x, ans);
  delc(rk[x], now);
  ad(rk[x], -1);
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
  Count(0, 0, 0);
  for (int i = 1; i <= n; i++) printf("%lld ", Ans[i]);
}
