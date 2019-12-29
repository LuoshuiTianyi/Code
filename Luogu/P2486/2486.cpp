#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])
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

const int Max_n = 1e4 + 5;
int n, m;

struct node {
  int fa, t1, t2, c, c1, c2, sum, s[2];
} k[Max_n];
namespace LCT {
#define ls(x) k[x].s[0]
#define rs(x) k[x].s[1]
bool kd(int x) { return rs(k[x].fa) == x; }
bool nrt(int x) { return kd(x) || ls(k[x].fa) == x; }
void upd(int x) {
  if (!x) return;
  k[x].c1 = ls(x) ? k[ls(x)].c1 : k[x].c;
  k[x].c2 = rs(x) ? k[rs(x)].c2 : k[x].c;
  k[x].sum = k[ls(x)].sum + k[rs(x)].sum + 1;
  k[x].sum -= (k[x].c == k[ls(x)].c2) + (k[x].c == k[rs(x)].c1);
}
void roll(int x) {
  if (!x) return;
  swap(ls(x), rs(x)), k[x].t1 ^= 1;
}
void col(int x, int c) {
  if (!x || !c) return;
  k[x].c = k[x].t2 = c;
}
void pushdown(int x) {
  if (k[x].t1) k[x].t1 = 0, roll(ls(x)), roll(rs(x));
  col(ls(x), k[x].t2), col(rs(x), k[x].t2), k[x].t2 = 0;
}
void rotate(int x) {
  int y = k[x].fa, z = k[y].fa, s1 = kd(x), s2 = k[x].s[!s1];
  if (nrt(y)) k[z].s[kd(y)] = x;
  k[x].s[!s1] = y, k[y].s[s1] = z;
  if (s2) k[s2].fa = y;
  k[x].fa = z, k[y].fa = x, upd(y);
}
void Push(int x) {
  if (nrt(x)) Push(k[x].fa);
  pushdown(x);
}
void splay(int x) {
  Push(x);
  for (int fa = k[x].fa; nrt(x); rotate(x), fa = k[x].fa)
    if (nrt(fa)) rotate(kd(fa) ^ kd(x) ? x : fa);
  upd(x);
}
void access(int x) {
  for (int y = 0; x; x = k[y = x].fa) splay(x), rs(x) = y, upd(x);
}
void makert(int x) { access(x), splay(x), roll(x); }
void link(int x, int y) { 
  cout << x << " " << y << endl;
  makert(x), k[x].fa = y; 
}
void modify(int x, int y, int c) {
  makert(x), access(y), splay(y);
  col(y, c);
}
void Print(int x) {
  if (!x) return;
  Print(ls(x)), cout << x << " " << k[x].c1 << " " << k[x].c2 << " " << k[x].sum << " " << k[x].c << endl, Print(rs(x));
}
int query(int x, int y) {
  makert(x), access(y), splay(y); 
  //Print(y);
  return k[y].sum;
}
}  // namespace LCT

namespace Input {
void main() {
  n = read(), m = read();
  for (int i = 1; i <= n; i++) k[i].c = read();
  for (int i = 1; i < n; i++) {
    int u = read(), v = read();
    LCT::link(u, v);
  }
}
}  // namespace Input

namespace Solve {
void main() {
  char op;
  while (m--) {
    scanf(" %c", &op);
    int a = read(), b = read();
    if (op == 'C')
      LCT::modify(a, b, read());
    else
      printf("%d\n", LCT::query(a, b));
  }
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("2486.in", "r", stdin);
  freopen("2486.out", "w", stdout);
#endif
  Input::main();
  Solve::main();
}
