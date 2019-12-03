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
const int Max_n = 3e6 + 5;
const double pi = acos(-1);
int n, m;
int lim = 1, bit;
int rev[Max_n];
cp a[Max_n], b[Max_n], c[Max_n];
void dft(cp *f, int t) {
  for (int i = 0; i < lim; i++)
    if (rev[i] > i) swap(f[i], f[rev[i]]);
  for (int len = 1; len < lim; len <<= 1) {
    cp Wn(cos(t * pi / (double)len), sin(t * pi / (double)len));
    for (int i = 0; i < lim; i += (len << 1)) {
      cp Wnk(1, 0);
      for (int k = i; k < i + len; k++) {
        cp x = f[k], y = Wnk * f[k + len];
        f[k] = x + y, f[k + len] = x - y;
        Wnk *= Wn;
      }
    }
  }
}
void FFT() {
  dft(a, 1), dft(b, 1);
  for (int i = 0; i < lim; i++) cout << a[i].read() << " ";
  for (int i = 0; i < lim; i++) c[i] = a[i] * b[i];
  dft(c, -1);
  for (int i = 0;  i < lim; i++) c[i] /= lim;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("3803.in", "r", stdin);
  freopen("3803.ans", "w", stdout);
#endif
  n = read(), m = read();
  for (int i = 0; i <= n; i++) a[i] = (double)read();
  for (int i = 0; i <= m; i++) b[i] = (double)read();
  while (lim <= n + m + 2) bit++, lim <<= 1;
  for (int i = 0; i < lim; i++)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));
  FFT();
  cout << endl;
  for (int i = 0; i <= n + m; i++)
    printf("%d ", (int)(c[i].real() + 0.5));
}
