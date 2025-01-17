#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])

char read_str[1 << 25], *CH = read_str;
#define getchar() (*CH++)
LL read() {
  char ch = getchar();
  int fl = 0;
  LL x = 0;
  while (!isdigit(ch)) {
    if (ch == '-') fl = 1;
    ch = getchar();
  }
  while (isdigit(ch)) x = (x << 1) + (x << 3) + ch - '0', ch = getchar();
  return fl ? -x : x;
}
void rstr(char *s) {
  char *x = s;
  char ch = getchar();
  while (ch == ' ' || ch == '\n' || ch == '\r') ch = getchar();
  while (ch != ' ' && ch != '\n' && ch != '\r') {
    *x++ = ch;
    ch = getchar();
  }
}

const int Max_n = 1e5 + 5;
int n, m;

namespace LCT {
#define ls(x) k[x].s[0]
#define rs(x) k[x].s[1]
#define fa(x) k[x].fa
struct node {
  int fa, s[2], rev_tag, xor_sum, val;
} k[Max_n];
bool kd(int x) { return rs(fa(x)) == x; }
bool nrt(int x) { return kd(x) || ls(fa(x)) == x; }
void upd(int x) {
  k[x].xor_sum = k[x].val ^ k[ls(x)].xor_sum ^ k[rs(x)].xor_sum;
}
void roll(int x) {
  if (!x) return;
  swap(ls(x), rs(x)), k[x].rev_tag ^= 1;
}
void pushdown(int x) {
  if (k[x].rev_tag) roll(ls(x)), roll(rs(x)), k[x].rev_tag = 0;
}
void rotate(int x) {
  int y = fa(x), z = fa(y), s1 = kd(x), s2 = k[x].s[!s1];
  if (nrt(y)) k[z].s[kd(y)] = x;
  k[x].s[!s1] = y, k[y].s[s1] = s2;
  if (s2) k[s2].fa = y;
  fa(y) = x, fa(x) = z, upd(y);
}
void Push(int x) {
  if (nrt(x)) Push(fa(x));
  pushdown(x);
}
void splay(int x) {
  Push(x);
  for (int f = fa(x); nrt(x); rotate(x), f = fa(x))
    if (nrt(f)) rotate(kd(f) ^ kd(x) ? x : f);
  upd(x);
}
void access(int x) {
  for (int y = 0; x; x = fa(y = x)) splay(x), rs(x) = y;
}
void makert(int x) { access(x), splay(x), roll(x); }
int findrt(int x) {
  access(x), splay(x);
  while (ls(x)) x = ls(x);
  splay(x);
  return x;
}
void link(int u, int v) {
  makert(u);
  if (findrt(v) != u) fa(u) = v;
}
void cut(int u, int v) {
  makert(u);
  if (findrt(v) == u && fa(v) == u && !ls(v)) rs(u) = fa(v) = 0, upd(u);
}
int qry(int u, int v) {
  makert(u), access(v), splay(v);
  return k[v].xor_sum;
}
}  // namespace LCT
using namespace LCT;

namespace Input {
void main() { 
  fread(read_str, 1, 1 << 25, stdin); 
  n = read(), m = read();
}
}  // namespace Input

namespace Init {
void main() {
  for (int i = 1; i <= n; i++) k[i].val = read();
}
}  // namespace Init

namespace Solve {
void main() {
  while (m--) {
    int op = read(), u = read(), v = read();
    switch(op) {
    case 0:
      printf("%d\n", qry(u, v));
      break;
    case 1:
      link(u, v);
      break;
    case 2:
      cut(u, v);
      break;
    default:
      splay(u), k[u].val = v;
      break;
    }
  }
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("3690.in", "r", stdin);
  freopen("3690.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
