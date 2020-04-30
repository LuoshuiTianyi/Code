#include <cmath>
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

const int Max_n = 4e6 + 5, mod = 998244353;
int n, m;

int ksm(int a, int b = mod - 2) {
  int res = 1;
  for (; b; b >>= 1, a = (LL)a * a % mod)
    if (b & 1) res = (LL)res * a % mod;
  return res;
}

namespace Poly {
int len, bit, rev[Max_n];
void init(int n) {
  len = 1 << (bit = log2(n) + 1);
  for (int i = 0; i < len; i++)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << bit - 1);
}
struct poly {
  int f[Max_n];
  int& operator[](int x) {
    return f[x];
  }
  void dft(int t) {
    for (int l = 1; l < len; l <<= 1) {
    }
  }
};
}

namespace Input {
void main() {
  n = read(), m = read();
}
}  // namespace Input

namespace Solve {
void main() {
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("3803.in", "r", stdin);
  freopen("3803.out", "w", stdout);
#endif
  Input::main();
  Solve::main();
}
