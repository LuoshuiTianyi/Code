#include <algorithm>
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

const int Max_n = 1e5 + 5;
int n;
LL x, M;

namespace Input {
void main() { n = read(); }
}  // namespace Input

namespace Solve {
void exgcd(LL a, LL b, LL &x, LL &y) {
  if (!b) {
    x = 1, y = 0;
    return;
  }
  exgcd(b, a % b, y, x), y = y - (a / b) * x;
}
void Mod(LL &x, LL mod) { x = x >= mod ? x - mod : x; }
LL Mul(LL a, LL b, LL mod) {
  LL res = 0;
  a %= mod;
  for (; b; b >>= 1ll, (a += a) %= mod)
    if (b & 1) (res += a) %= mod;
  return res;
}
void main() {
  M = 1, x = 0;
  while (n--) {
    LL b = read(), a = read(), c = (a - x % b + b) % b, x1, x2;
    LL gcd = __gcd(M, b);
    exgcd(M, b, x1, x2);
    x += Mul(x1, c / gcd, b / gcd) * M;
    M = M * (b / gcd);
    x = (x % M + M) % M;
  }
  cout << x;
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("4777.in", "r", stdin);
  freopen("4777.out", "w", stdout);
#endif
  Input::main();
  Solve::main();
}
