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

const int Max_n = 2005, mod = 998244353;
int n, K;
int x[Max_n], y[Max_n];

namespace Input {
void main() {
  n = read(), K = read();
  for (int i = 1; i <= n; i++) x[i] = read(), y[i] = read();
}
}  // namespace Input

namespace Solve {
int ksm(int a, int b = mod - 2) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % mod)
    if (b & 1) res = 1ll * res * a % mod;
  return res;
}
void main() {
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    int s = 1;
    for (int j = 1; j <= n; j++)
      if (i != j) s = 1ll * s * (x[i] - x[j] + mod) % mod;
    s = ksm(s);
    for (int j = 1; j <= n; j++)
      if (i != j) s = 1ll * s * (K - x[j] + mod) % mod;
    (ans += 1ll * s * y[i] % mod) %= mod;
  }
  cout << ans;
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("4781.in", "r", stdin);
  freopen("4781.out", "w", stdout);
#endif
  Input::main();
  Solve::main();
}
