#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
#define cp complex<double>
const int Max_n = 3e5 + 5;
const double pi = acos(-1);
int n;
int rev[Max_n];
double dv[Max_n], ans[Max_n], q[Max_n];
cp f[Max_n], g[Max_n];
namespace FFT {
int lim, bit;
void dft(cp *f, int t) {
  for (int i = 0; i < lim; i++)
    if (rev[i] > i) swap(f[rev[i]], f[i]);
  for (int len = 1; len < lim; len <<= 1) {
    cp Wn = exp(cp(0, t * pi / len));
    for (int i = 0; i < lim; i += len << 1) {
      cp Wnk(1, 0);
      for (int k = i; k < i + len; k++, Wnk *= Wn) {
        cp x = f[k], y = Wnk * f[k + len];
        f[k] = x + y, f[k + len] = x - y;
      }
    }
  }
}
void fft(double *a, double *b, int tot) {
  lim = 1, bit = 0;
  while (lim <= tot) lim <<= 1, bit++;
  for (int i = 0; i < lim; i++)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
  for (int i = 0; i < lim; i++) f[i] = a[i], g[i] = b[i];
  dft(f, 1), dft(g, 1);
  for (int i = 0; i < lim; i++) f[i] *= g[i];
  dft(f, -1);
  for (int i = 0; i < lim; i++) f[i] /= lim;
}
}  // namespace FFT
using namespace FFT;
int main() {
#ifndef ONLINE_JUDGE
  freopen("3338.in", "r", stdin);
  freopen("3338.out", "w", stdout);
#endif
  cin >> n;
  for (int i = 1; i <= n; i++) scanf("%lf", &q[i]);
  for (int i = 1; i <= n; i++) dv[i] = (double)(1.0 / i / i);
  fft(q, dv, n << 1);
  for (int i = 1; i <= n; i++) ans[i] += f[i].real();
  reverse(q + 1, q + n + 1);
  fft(q, dv, n << 1);
  for (int i = 1; i <= n; i++)
    printf("%.2lf\n", (ans[i] -= f[n - i + 1].real()));
}
