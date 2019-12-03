#include <cmath>
#include <complex>
#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define inline __inline__ __attribute__((always_inline))
#define cp complex<double>
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

const int Max_n = 4e6 + 5;
const double pi = acos(-1);
int n, m;
cp f[Max_n], g[Max_n];

namespace Input {
void main() {
  n = read(), m = read();
  for (int i = 0; i <= n; i++) f[i] = read();
  for (int i = 0; i <= n; i++) g[i] = read();
}
}  // namespace Input

namespace FFT {
int bit, len, rev[Max_n];
void dft(cp *f, int t) {
}
void fft(cp *f, cp *g) {
  dft(f, 1), dft(g, 1);
  for (int i = 1; i <= len; i++) f[i] *= g[i];
  dft(f, -1);
}
void init(int n, int m) {
  bit = log2(n + m + 2) + 1;
  len = 1 << bit;
}
}  // namespace Init

namespace Solve {
void main() {}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("3803.in", "r", stdin);
  freopen("3803.out", "w", stdout);
#endif
  Input::main();
  Solve::main();
}
