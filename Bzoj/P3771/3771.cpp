#include <cmath>
#include <complex>
#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define cp complex<double>
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

const int Max_n = 4e5 + 5, Ml = 1.2e5;
const double pi = acos(-1);
cp ans[Max_n], A[Max_n], B[Max_n], C[Max_n];

namespace Input {
void main() {
  int n = read();
  for (int i = 1, x; i <= n; i++)
    x = read(), A[x] += 1, B[x * 2] += 1, C[x * 3] += 1;
}
}  // namespace Input

namespace Solve {
int bit, len, rev[Max_n];
void init() {
  int bit = log2(Ml + 1) + 1;
  len = 1 << bit;
  for (int i = 0; i < len; i++)
    rev[i] = rev[i >> 1] >> 1 | ((i & 1) << (bit - 1));
}
void dft(cp *f, int t) {
  for (int i = 0; i < len; i++)
    if (i < rev[i]) swap(f[i], f[rev[i]]);
  for (int l = 1; l < len; l <<= 1) {
    cp Wn(cos(t * pi / (double)l), sin(t * pi / (double)l));
    for (int i = 0; i < len; i += (l << 1)) {
      cp Wnk(1, 0);
      for (int k = i; k < i + l; k++, Wnk *= Wn) {
        cp x = f[k], y = f[k + l] * Wnk;
        f[k] = x + y, f[k + l] = x - y;
      }
    }
  }
}
void main() {
  init();
  dft(A, 1), dft(B, 1), dft(C, 1);
  for (int i = 0; i < len; i++) {
    ans[i] = (A[i] * A[i] * A[i] - A[i] * B[i] * 3.0 + 2.0 * C[i]) / 6.0;
    ans[i] += (A[i] * A[i] - B[i]) / 2.0 + A[i];
  }
  dft(ans, -1);
  for (int i = 0; i <= Ml; i++) ans[i] /= (double)len;
  for (int i = 0; i <= Ml; i++) {
    LL Ans = (LL)(ans[i].real() + 0.5);
    if (Ans) printf("%d %lld\n", i, Ans);
  }
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("3771.in", "r", stdin);
  freopen("3771.out", "w", stdout);
#endif
  Input::main();
  Solve::main();
}
