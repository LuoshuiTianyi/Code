#include <algorithm>
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

const int Max_n = 2e5 + 5;
int n, m, cnt;
struct edge {
  int u, v, a, b;
} e[Max_n];

struct node {
  int fa, v, Max, tag, s[2];
} k[Max_n];
namespace LCT {
bool kd(int x) { return rs(k[x].fa) == x; }
bool nrt(int x) { return kd(x) || ls(k[x].fa) == x; }
void upd(int x) {
  k[x].Max = max(k[ls(x)].Max, k[rs(x)].Max);
  k[x].Max = max(k[x].Max, k[x].v);
}
void roll(int x) { swap(ls(x), rs(x)), k[x].tag ^= 1; }
void pushdown(int x) {
  if (k[x].tag) {
  }
}
}  // namespace LCT

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
  freopen("2387.in", "r", stdin);
  freopen("2387.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
