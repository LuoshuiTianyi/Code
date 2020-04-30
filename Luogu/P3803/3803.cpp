#include <cmath>
#include <cstdio>
#include <cstring>
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
  int& operator[](int x) { return f[x]; }
  void init() {
    memset(f, 0, sizeof (f));
  }
  void dft(int t) {
    for (int i = 0; i < len; i++)
      if (rev[i] > i) swap(f[i], f[rev[i]]);
    for (int l = 1; l < len; l <<= 1) {
      int Wn = ksm(3, (mod - 1) / (l << 1));
      if (t) Wn = ksm(Wn);
      for (int i = 0; i < len; i += l << 1) {
        int Wnk = 1;
        for (int j = i; j < i + l; j++, Wnk = (LL)Wnk * Wn % mod) {
          int x = f[j], y = f[j + l];
          f[j] = (x + y) % mod, f[j + l] = (x - y + mod) % mod;
        }
      }
    }
    if (t)
      for (int i = 0, Inv = ksm(len); i < len; i++) f[i] = (LL)f[i] * Inv % mod;
  }
};
}  // namespace Poly
using namespace Poly;

poly f, g;

void Mul(poly &f, poly &g, int N) {
  init(N);
  f.dft(0), g.dft(0);
  for (int i = 0; i < len; i++) f[i] = (LL)f[i] * g[i] % mod;
  f.dft(1), g.dft(1);
}

namespace Input {
void main() { 
  n = read(), m = read(); 
  for (int i = 0; i <= n; i++) f[i] = read();
  for (int i = 0; i <= m; i++) g[i] = read();
}
}  // namespace Input

namespace Solve {
void main() {
  Mul(f, g, n + m + 2);
  for (int i = 0; i <= n + m; i++) printf("%d ", f[i]);
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
