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
long long read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
#define cp complex<double>
const int Max_n = 5e5 + 5;
const double pi = acos(-1);
int n, m, ans;
int sx, sy, Max, mid, x[Max_n], y[Max_n];
int lim = 1, bit, rev[Max_n];
cp f[Max_n], g[Max_n];
void dft(cp *f, int t) {
  for (int i = 0; i < lim; i++)
    if (rev[i] > i) swap(f[i], f[rev[i]]);
  for (int len = 1; len < lim; len <<= 1) {
    cp Wn(cos(t * pi / len), sin(t * pi / len));
    for (int i = 0; i < lim; i += len << 1) {
      cp Wnk(1, 0);
      for (int k = i; k < i + len; k++) {
        cp a = f[k], b = Wnk * f[k + len];
        f[k] = a + b, f[k + len] = a - b;
        Wnk *= Wn;
      }
    }
  }
}
void FFT() {
  dft(f, 1), dft(g, 1);
  for (int i = 0; i < lim; i++) f[i] *= g[i];
  dft(f, -1);
  for (int i = 0; i < lim; i++) f[i] /= lim;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("3723.in", "r", stdin);
  freopen("3723.out", "w", stdout);
#endif
  n = read(), m = read();
  for (int i = 0; i < n; i++) {
    f[i] = x[i] = read();
    sx += x[i], ans += x[i] * x[i];
  }
  for (int i = 0; i < n; i++) {
    g[i] = y[i] = read();
    sy += y[i], ans += y[i] * y[i];
  }
  reverse(f, f + n);
  for (int i = 0; i < n; i++) f[i + n] = f[i];
  while (lim <= n * 3) bit++, lim <<= 1;
  for (int i = 0; i < lim; i++)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
  FFT();
  for (int i = n; i < 2 * n; i++) Max = max(Max, (int)(f[i].real() + 0.5));
  double tp = double(sy - sx) / n;
  mid = (int)(tp += tp < 0 ? -0.5 : 0.5);
  cout << (ans += n * mid * mid + 2 * (sx - sy) * mid - 2 * Max);
}
