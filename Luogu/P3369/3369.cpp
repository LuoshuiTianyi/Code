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
} k[Max_n];
bool kd(int x) { return rs(k[x].fa) == x; }
void upd(int x) {
  if (!x) return;
  k[x].size = k[ls(x)].size + k[rs(x)].size + k[x].cnt;
}
inline void rotate(int x) {
  bool t = kd(x);
  int A = k[x].fa, B = k[A].fa, C = k[x].s[!t];
  k[A].s[t] = C, k[B].s[kd(A)] = x, k[x].s[!t] = A;
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
  if (!x) x = rt = cnt + 1;
  for (; k[x].v != n && x;) x = k[x].v > n ? ls(x) : rs(x);
  if (x) {
    k[x].cnt++, k[x].size++;
    return;
  }
  cnt++, k[cnt].fa = x, k[cnt].v = n, k[cnt].size = 1;
  if (n < k[x].v)
    ls(x) = cnt;
  else
    rs(x) = cnt;
  upd(cnt), splay(cnt, rt);
}
inline void del() {
  int x = rt;
  for (; k[x].v != n;) x = k[x].v > n ? ls(x) : rs(x);
  if (--k[x].cnt) return;
  splay(x, 0);
  if (!ls(x))
    rt = rs(x);
  else {
    int q = ls(x);
    while (rs(q)) q = rs(q);
    splay(q, x);
    rt = q, rs(q) = rs(x), k[rs(x)].fa = q, upd(q);
  }
}
inline int rak() {
  int res = 0, x = rt;
  for (; k[x].v != n; x = k[x].v > n ? ls(x) : rs(x))
    if (k[x].v < n) res += k[ls(x)].size + 1;
  return res + k[ls(x)].size;
}
inline int num() {
  int x = rt;
  while (1)
    if (k[ls(x)].size < n) {
      n -= k[ls(x)].size;
      if (!(--n)) return k[x].v;
      x = rs(x);
    } else
      x = ls(x);
}
inline int pre() {
  int x = rt;
  for (; k[x].v != n;) x = k[x].v > n ? ls(x) : rs(x);
  splay(x, 0);
}
inline int nxt() {
  int x = rt;
  for (; k[x].v != n;) x = k[x].v > n ? ls(x) : rs(x);
  splay(x, 0);
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
    if (opt == 5) printf("%d\n", Splay::pre());
    if (opt == 6) printf("%d\n", Splay::nxt());
  }
}
