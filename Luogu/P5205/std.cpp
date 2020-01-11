#include <cmath>
#include <cstdio>
#include <iostream>
#define rep(i, a, n) for (int i = a; i <= n; i++)
#define per(i, n, a) for (int i = n; i >= a; i--)
#define enter putchar('\n')
#define I inline

using namespace std;
typedef long long ll;
const int M = 800005;
const int mod = 998244353;
const int G = 3;
const int invG = 332748118;

int read() {
  int ans = 0, op = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') op = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') ans = ans * 10 + ch - '0', ch = getchar();
  return ans * op;
}

int rev[M], A[M], B[M], C[M], D[M], F[M], n, inv2;

int inc(int a, int b) { return (a + b) % mod; }
int mul(int a, int b) { return 1ll * a * b % mod; }

int qpow(int a, int b) {
  int p = 1;
  while (b) {
    if (b & 1) p = mul(p, a);
    a = mul(a, a), b >>= 1;
  }
  return p;
}

void getrev(int l, int L) {
  rep(i, 0, l - 1) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
}

void NTT(int *a, int n, int f) {
  rep(i, 0, n - 1) if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int i = 1; i < n; i <<= 1) {
    int w1 = qpow(f ? G : invG, (mod - 1) / (i << 1));
    for (int j = 0; j < n; j += (i << 1)) {
      int w = 1;
      rep(k, 0, i - 1) {
        int kx = a[k + j], ky = mul(a[k + j + i], w);
        a[k + j] = inc(kx, ky), a[k + j + i] = inc(kx, mod - ky),
              w = mul(w, w1);
      }
    }
  }
  if (!f) {
    int inv = qpow(n, mod - 2);
    rep(i, 0, n - 1) a[i] = mul(a[i], inv);
  }
}

void getinv(int *a, int *b, int len) {
  if (len == 1) {
    b[0] = qpow(a[0], mod - 2);
    return;
  }
  getinv(a, b, (len + 1) >> 1);
  int l = 1, L = 0;
  while (l < (len << 1)) l <<= 1, L++;
  getrev(l, L);
  rep(i, 0, len - 1) C[i] = a[i];
  rep(i, len, l - 1) C[i] = 0;
  NTT(C, l, 1), NTT(b, l, 1);
  rep(i, 0, l - 1) b[i] = mul(inc(2, mod - mul(C[i], b[i])), b[i]);
  NTT(b, l, 0);
  rep(i, len, l - 1) b[i] = 0;
}

void getsqrt(int *a, int *b, int len) {
  if (len == 1) {
    b[0] = 1;
    return;
  }
  getsqrt(a, b, (len + 1) >> 1);
  rep(i, 0, len << 1) F[i] = 0;
  getinv(b, F, len);
  int l = 1, L = 0;
  while (l < len << 1) l <<= 1, L++;
  getrev(l, L);
  rep(i, 0, len - 1) D[i] = a[i];
  rep(i, len, l - 1) D[i] = 0;
  NTT(D, l, 1), NTT(b, l, 1), NTT(F, l, 1);
  rep(i, 0, l - 1) b[i] = mul(inc(b[i], mul(D[i], F[i])), inv2);
  NTT(b, l, 0);
  rep(i, len, l - 1) b[i] = 0;
}
int main() {
  freopen("5205.in", "r", stdin);
  freopen("5205.out", "w", stdout);
  n = read(), inv2 = qpow(2, mod - 2);
  rep(i, 0, n - 1) A[i] = read();
  getsqrt(A, B, n);
  rep(i, 0, n - 1) printf("%d ", B[i]);
  enter;
  return 0;
}
