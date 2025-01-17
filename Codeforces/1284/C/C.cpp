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

const int Max_n = 2.5e5 + 5;
int n, ans, mod;
int fac[Max_n];

namespace Input {
void main() {
  n = read(), mod = read();
}
}  // namespace Input

namespace Init {
void main() {
  fac[0] = 1;
  for (int i = 1; i <= n; i++) fac[i] = 1ll * fac[i - 1] * i % mod;
}
}  // namespace Init

namespace Solve {
void main() {
  for (int i = 1; i <= n; i++)
    (ans += 1ll * (n - i + 1) * (n - i + 1) % mod * fac[i] % mod * fac[n - i] % mod) %= mod;
  cout << ans;
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("C.in", "r", stdin);
  freopen("C.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
