#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
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
int m;
int opt, n;
int p;
namespace Splay {
int cnt, rt;
#define ls(x) k[x].s[0]
#define rs(x) k[x].s[1]
struct node {
  int fa, v, size, cnt, s[2];
  void init() { fa = v = size = cnt = s[0] = s[1] = 0; }
} k[Max_n];
inline bool kd(int x) { return rs(k[x].fa) == x; }
inline void upd(int x) {
  if (!x) return;
  k[x].size = k[ls(x)].size + k[rs(x)].size + k[x].cnt;
}
inline int nx(int x) {
  if (k[x].v == n) return 0;
  return k[x].v > n ? ls(x) : rs(x);
}
inline void rotate(int x) {
  bool t = kd(x);
  int A = k[x].fa, B = k[A].fa, C = k[x].s[!t];
  // if (m == 25787) cerr << x << " " << A << " " << B << endl;
  k[A].s[t] = C, k[x].s[!t] = A, k[B].s[kd(A)] = x;
  k[A].fa = x, k[x].fa = B, k[C].fa = A;
  upd(A), upd(x);
}
inline void splay(int x, int to) {
  for (int fa; (fa = k[x].fa) != to; rotate(x))
    if (k[fa].fa != to) rotate(kd(x) ^ kd(fa) ? x : fa);
  if (!to) rt = x;
}
inline void add() {
  int x = rt;
  while (nx(x)) x = nx(x);
  if (k[x].v == n) {
    k[x].cnt++, k[x].size++, splay(x, 0);
    return;
  }
  cnt++, k[cnt].fa = x, k[cnt].v = n, k[cnt].size = k[cnt].cnt = 1;
  if (n < k[x].v)
    ls(x) = cnt;
  else
    rs(x) = cnt;
  upd(cnt), splay(cnt, 0);
}
inline void del() {
  int x = rt;
  while (nx(x)) x = nx(x);
  splay(x, 0);
  if (--k[x].cnt) {
    upd(x);
    return;
  }
  if (!ls(x))
    rt = rs(x), k[rs(x)].fa = 0;
  else {
    int q = ls(x);
    while (rs(q)) q = rs(q);
    splay(q, x);
    rt = q, rs(q) = rs(x), k[rs(x)].fa = q, k[q].fa = 0, upd(q);
  }
}
inline int rak() {
  int res = 0, x = rt;
  for (; nx(x); x = nx(x))
    if (k[x].v < n) res += k[ls(x)].size + k[x].cnt;
  int tp = res + k[ls(x)].size + 1;
  if (x) splay(x, 0);
  return tp;
}
inline int num() {
  int x = rt;
  while (1)
    if (k[ls(x)].size < n) {
      n -= k[ls(x)].size;
      if ((n -= k[x].cnt) <= 0) {
        if (x) splay(x, 0);
        return k[x].v;
      }
      x = rs(x);
    } else
      x = ls(x);
}
inline int pre() {
  int x = rt, res = -1e9;
  while (x) {
    if (k[x].v <= n) res = max(res, k[x].v);
    x = nx(x);
  }
  return res;
}
inline int nxt() {
  int x = rt, res = 1e9;
  while (x) {
    if (k[x].v >= n) res = min(res, k[x].v);
    x = nx(x);
  }
  return res;
}
}  // namespace Splay
int main() {
#ifndef ONLINE_JUDGE
  freopen("3369.in", "r", stdin);
  freopen("3369.out", "w", stdout);
#endif
  m = read();
  while (m--) {
    opt = read(), n = read();
    if (opt == 1) Splay::add();
    if (opt == 2) Splay::del();
    if (opt == 3) printf("%d\n", Splay::rak());
    if (opt == 4) printf("%d\n", Splay::num());
    if (opt == 5) n--, printf("%d\n", Splay::pre());
    if (opt == 6) n++, printf("%d\n", Splay::nxt());
  }
}
