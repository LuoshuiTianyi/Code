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

struct splay {
  int fa, tag, v, sum, s[2];
} k[Max_n];
namespace LCT {
#define ls(x) k[x].s[0]
#define rs(x) k[x].s[1]
bool Nrt(int x) {
  return ls(k[x].fa) == x || rs(k[x].fa) == x;
}
void pushup(int x) {
  k[x].sum = k[ls(x)].sum ^ k[rs(x)].sum ^ k[x].v;
}
void roll(int x) {
  if (!x) return;
  k[x].tag ^= 1, swap(ls(x), rs(x));
}
void pushdown(int x) {
  if (k[x].tag) {
    k[x].tag = 0;
    roll(ls(x)), roll(rs(x));
  }
}
void rotate(int x) {
}
}

namespace Input {
void main() {}
}  // namespace Input

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
