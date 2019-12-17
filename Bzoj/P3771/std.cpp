#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#define maxn 400000
using namespace std;
typedef long long ll;
const double pi = acos(-1.0);
struct com {
  double real;
  double imag;
  com() {}
  com(double _real, double _imag) {
    real = _real;
    imag = _imag;
  }
  com(double x) {
    real = x;
    imag = 0;
  }
  void operator=(const com x) {
    this->real = x.real;
    this->imag = x.imag;
  }
  void operator=(const double x) {
    this->real = x;
    this->imag = 0;
  }
  friend com operator+(com p, com q) {
    return com(p.real + q.real, p.imag + q.imag);
  }
  friend com operator+(com p, double q) { return com(p.real + q, p.imag); }
  friend com operator-(com p, com q) {
    return com(p.real - q.real, p.imag - q.imag);
  }
  friend com operator-(com p, double q) { return com(p.real - q, p.imag); }
  friend com operator*(com p, com q) {
    return com(p.real * q.real - p.imag * q.imag,
               p.real * q.imag + p.imag * q.real);
  }
  friend com operator*(com p, double q) { return com(p.real * q, p.imag * q); }
  friend com operator/(com p, double q) { return com(p.real / q, p.imag / q); }
  void print() { printf("%lf + %lf i ", real, imag); }
};
void fft(com *x, int n, int type) {
  static int rev[maxn + 5];
  int tn = 1, k = 0;
  while (tn < n) {
    k++;
    tn *= 2;
  }
  for (int i = 0; i < n; i++)
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (k - 1));
  for (int i = 0; i < n; i++)
    if (i < rev[i]) swap(x[i], x[rev[i]]);
  for (int len = 1; len < n; len *= 2) {
    int sz = len * 2;
    com wn1 = com(cos(2 * pi / sz), type * sin(2 * pi / sz));
    for (int l = 0; l < n; l += sz) {
      int r = l + len - 1;
      com wnk = 1;
      for (int i = l; i <= r; i++) {
        com tmp = x[i + len];
        x[i + len] = x[i] - wnk * tmp;
        x[i] = x[i] + wnk * tmp;
        wnk = wnk * wn1;
      }
    }
  }
  if (type == -1) {
    for (int i = 0; i < n; i++) x[i].real /= n;
  }
}
void mul(com *a, com *b, com *ans, int n) {
  //  fft(a,n,1);
  //  fft(b,n,1);
  //避免多次fft
  for (int i = 0; i < n; i++) ans[i] = a[i] * b[i];
  fft(ans, n, -1);
}

int n;
int val[maxn + 5];
com a[maxn + 5], b[maxn + 5], c[maxn + 5];
com ans[maxn + 5];
int main() {
  freopen("3771.in", "r", stdin);
  freopen("3771.ans", "w", stdout);
  scanf("%d", &n);
  int mv = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &val[i]);
    a[val[i]] = a[val[i]] + 1;
    b[val[i] * 2] = b[val[i] * 2] + 1;
    c[val[i] * 3] = c[val[i] * 3] + 1;
    mv = max(mv, val[i]);
  }
  int tn = 1, k = 0;
  while (tn < mv * 3) {
    k++;
    tn *= 2;
  }
  fft(a, tn, 1);
  fft(b, tn, 1);
  fft(c, tn, 1);
  for (int i = 0; i < tn; i++) {
    ans[i] = (a[i] * a[i] * a[i] - 3 * a[i] * b[i] + 2 * c[i]) / 6 +
             (a[i] * a[i] - b[i]) / 2 + a[i];
  }
  fft(ans, tn, -1);
  for (int i = 0; i <= mv * 3; i++) {
    if (ll(ans[i].real + 0.5)) {
      printf("%d %lld\n", i, ll(ans[i].real + 0.5));
    }
  }
}
