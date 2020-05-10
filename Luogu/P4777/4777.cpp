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
void main() {
  n = read();
}
}  // namespace Input

namespace Solve {
void exgcd(LL a, LL b, LL &x, LL &y) {
  if (!b) {
    x = 1, y = 0;
    return;
  }
  exgcd(b, a % b, y, x);
  y = y - (a / b) * x;
}
void main() {
  M = 1, x = 0;
  while (n--) {
    LL b = read(), a = read(), c = (a - x % b + b) % b, x1, x2;
    exgcd(M, b, x1, x2);
    x += M * x1 * c / __gcd(M, b);
    M = M * b / __gcd(M, b);
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
