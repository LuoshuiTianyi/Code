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

int T;
LL n;

namespace Input {
void main() {
  n = read();
  srand(time(0));
}
}  // namespace Input

namespace PR {
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
  
  LL b = n - 1, k = 0;
  while (!(b & 1)) b >>= 1, k++;
  int t = 5;
  while (t--) {
    LL a = rand() % (n - 1) + 1;
    a = ksm(a, b, n);
    for (int i = 1; i <= k; i++) {
      LL c = (__int128)a * a % n;
      if (c == 1 && a != 1 && a != n - 1) return 0;
      a = c;
    }
    if (a != 1) return 0;
  }
  return 1;
}
LL f(LL x, LL p, LL c) { return (__int128)(x * x + c) % p; }
LL find(LL n, LL c) {
  LL a = rand() % (n - 1) + 1, b = a;
  LL k = 1;
  int p = 0;
  while (1) {
    b = f(b, n, c);
    if (a == b) return 0;
    k = (__int128)abs(b - a) * k % n;
    if (!k) return 0;
  }
}
}

namespace Solve {

void main() {
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("4718.in", "r", stdin);
  freopen("4718.out", "w", stdout);
#endif
  T = read();
  while (T--) {
    Input::main();
    Solve::main();
  }
}
