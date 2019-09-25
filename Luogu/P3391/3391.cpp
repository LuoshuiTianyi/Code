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
#define ls k[x].s[0]
#define rs k[x].s[1]
struct node {
  int fa, val, s[2], size;
  bool tag;
} k[Max_n];
void upd(int x) { k[x].size = k[ls].size + k[rs].size + 1; }
int build(int l, int r, int fa) {
  if (l > r) return 0;
  int x = ++cnt, mid = l + r >> 1;
  k[x].fa = fa, k[x].val = a[mid], k[x].size = 1;
  ls = build(l, mid - 1, x), rs = build(mid + 1, r, x), upd(x);
  return x;
}
int find(int res) {
  int x = rt;
  while (1)
    if (k[ls].size < res)
      x = ls;
    else {
      res -= k[ls].size;
      if (!res) return x;
      res--, x = rs;
    }
}
int kd(int x) { return k[k[x].fa].rs == x; }
void pushdown(int x) {
  k[ls].tag ^= k[x].tag, k[rs].tag ^= k[x].tag;
  if (k[x].tag) swap(ls, rs), k[x].tag = 0;
}
void rotate(int x) {
  
}
void splay(int x, int to) {
  for (int i = fa; (fa = k[x].fa) != to; rotate(x))
    if (k[fa].fa != to) rotate(kd(x) ^ kd(fa) ? x : fa);
  if (!to) rt = x;
}
void Reverse() { 
  L = find(L), R = find(R + 2); 
  splay(L, 0), splay(R, L);
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
  Splay::rt = Splay::build(1, n, 0);
  while (m--) {
    L = read(), R = read();
    Splay::Reverse();
  }
}
