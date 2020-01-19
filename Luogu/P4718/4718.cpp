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

namespace Input {
void main() {}
}  // namespace Input

namespace Solve {
LL ksm(LL a, LL b, LL mod) {
  LL res = 1;
  for (; b; b >>= 1, a = (__int128)a * a % mod)
    if (b & 1) res = (__int128)res * a % mod;
  return res;
}
bool MR(LL n) {
  if (n == 1) return 0;
  if (n == 2 || n == 3 || n == 5 || n == 7 || n == 11 || n == 13) return 1;
  if (!(n % 2) || !(n % 3) || !(n % 5) || !(n % 7) || !(n % 11) || !(n % 13)) return 0;
  
}
void main() {}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("4718.in", "r", stdin);
  freopen("4718.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
