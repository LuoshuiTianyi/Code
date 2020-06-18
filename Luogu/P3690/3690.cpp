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
int a[Max_n];

namespace Input {
void main() { fread(read_str, 1, 1 << 25, stdin); }
}  // namespace Input

namespace LCT {
#define ls(x) k[x].s[0]
#define rs(x) k[x].s[1]
struct node {
  int fa, val, rev_tag, xor_sum, s[2];
} k[Max_n];
bool kd(int x) { return rs(k[x].fa) == x; }
bool nrt(int x) { return ls(k[x].fa) == x || kd(x); }
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
  int y = k[x].fa, z = k[y].fa, s1 = kd(x), s2 = k[x].s[!s1];
  if (nrt(y)) k[z].s[kd(y)] = x;
  k[x].s[!s1] = y, k[y].s[s1] = s2;
  if (s2) k[s2].fa = y;
  k[y].fa = x, k[x].fa = z;
  upd(y);
}
void Push(int x) {
  if (nrt(x)) Push(k[x].fa);
  pushdown(x);
}
void splay(int x) {
  Push(x);
  for (int fa = k[x].fa; nrt(x); rotate(x), fa = k[x].fa)
    if (nrt(fa)) rotate(rotate(kd(fa) ^ kd(x) ? x : fa));
  upd(x);
}
}  // namespace LCT

namespace Init {
void main() {}
}  // namespace Init

namespace Solve {
void main() {}
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
