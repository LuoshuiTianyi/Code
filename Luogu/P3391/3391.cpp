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
int n, m;
int L, R, a[Max_n];
namespace Splay {
int cnt, rt;
#define ls(x) k[x].s[0]
#define rs(x) k[x].s[1]
struct node {
  int fa, val, s[2], size;
  bool tag;
} k[Max_n];
void upd(int x) { k[x].size = k[ls(x)].size + k[rs(x)].size + 1; }
void pushdown(int x) {
  k[ls(x)].tag ^= k[x].tag, k[rs(x)].tag ^= k[x].tag;
  if (k[x].tag) swap(ls(x), rs(x)), k[x].tag = 0;
}
int build(int l, int r, int fa) {
  if (l > r) return 0;
  int x = ++cnt, mid = l + r >> 1;
  k[x].fa = fa, k[x].val = a[mid], k[x].size = 1;
  ls(x) = build(l, mid - 1, x), rs(x) = build(mid + 1, r, x), upd(x);
  return x;
}
int find(int res) {
  int x = rt;
  while (1) {
    pushdown(x);
    if (k[ls(x)].size >= res) {
      x = ls(x);
    } else {
      res -= k[ls(x)].size;
      if (!(--res)) return x;
      x = rs(x);
    }
  }
}
int kd(int x) { return k[k[x].fa].s[1] == x; }
void rotate(int x) {
  bool t = kd(x);
  int A = k[x].fa, B = k[A].fa, C = k[x].s[!t];
  pushdown(A), pushdown(x);
  if (B) k[B].s[kd(A)] = x;
  k[A].fa = x, k[x].fa = B, k[C].fa = A, k[A].s[t] = C, k[x].s[!t] = A;
  upd(A), upd(x);
}
void splay(int x, int to) {
  for (int fa; (fa = k[x].fa) != to; rotate(x))
    if (k[fa].fa != to) rotate(kd(x) ^ kd(fa) ? x : fa);
  if (!to) rt = x;
}
void Print(int);
void Reverse() {
  L = find(L), R = find(R + 2);
  splay(L, 0), splay(R, L);
  k[ls(R)].tag ^= 1;
}
void Print(int x) {
  if (!x) return;
  pushdown(x), Print(ls(x));
  if (k[x].val > 0 && k[x].val < 1e9) printf("%d ", k[x].val);
  Print(rs(x));
}
}  // namespace Splay
int main() {
#ifndef ONLINE_JUDGE
  freopen("3391.in", "r", stdin);
  freopen("3391.out", "w", stdout);
#endif
  n = read(), m = read();
  a[1] = -1e9, a[n + 2] = 1e9;
  for (int i = 2; i <= n + 1; i++) a[i] = i - 1;
  Splay::rt = Splay::build(1, n + 2, 0);
  while (m--) {
    L = read(), R = read();
    Splay::Reverse();
  }
  Splay::Print(Splay::rt);
}
