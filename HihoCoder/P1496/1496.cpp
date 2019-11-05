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

const int Max = 1 << 20;
int T;
int n;
LL ans;
struct sum {
  int mx, cmx;
} f[Max + 1];
void chkmax(sum &a, int b) {
  if (b > a.mx)
    a.cmx = a.mx, a.mx = b;
  else if (b > a.cmx)
    a.cmx = b;
}
void chkmax(sum &a, sum b) { chkmax(a, b.mx), chkmax(a, b.cmx); }

namespace Input {
void main() {
  n = read(), ans = 0;
  for (int i = 0; i < Max; i++) f[i] = (sum){0, 0};
  int x;
  for (int i = 1; i <= n; i++) x = read(), chkmax(f[x], x);
}
}  // namespace Input

namespace Init {
void main() {
  for (int j = 0; j < 20; j++)
    for (int i = Max - 1; i; i--)
      if (!(i >> j & 1)) chkmax(f[i], f[i | (1 << j)]);
}
}  // namespace Init

namespace Solve {
void main() {
  for (int i = 1; i < Max; i++)
    ans = max(ans, 1ll * i * f[i].mx * f[i].cmx);
  printf("%lld\n", ans);
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("1496.in", "r", stdin);
  freopen("1496.out", "w", stdout);
#endif
  T = read();
  while (T--) {
    Input::main();
    Init::main();
    Solve::main();
  }
}
