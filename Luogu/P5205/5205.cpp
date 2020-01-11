#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])
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

const int Max_n = 6e5 + 5, mod = 998244353, G = 3;
int n;
int a[Max_n];

namespace Input {
void main() {
  n = read();
  for (int i = 0; i < n; i++) a[i] = read();
}
}  // namespace Input

namespace Solve {
int bit, len, rev[Max_n];
int invF[Max_n], sqrF[Max_n], inv[Max_n], sqr[Max_n];
int ksm(int a, int b = mod - 2) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % mod)
    if (b & 1) res = 1ll * res * a % mod;
  return res;
}
void init(int n) {
  len = 1 << (bit = log2(n * 3) + 1);
  for (int i = 0; i < len; i++)
    rev[i] = rev[i >> 1] >> 1 | ((i & 1) << (bit - 1));
}
void dft(int *f, int t) {
  for (int i = 0; i < len; i++)
    if (rev[i] > i) swap(f[rev[i]], f[i]);
  for (int l = 1; l < len; l <<= 1) {
    int Wn = ksm(G, (mod - 1) / (l << 1));
    if (t == -1) Wn = ksm(Wn);
    for (int i = 0; i < len; i += (l << 1)) {
      int Wnk = 1;
      for (int k = i; k < i + l; k++, Wnk = 1ll * Wnk * Wn % mod) {
        int x = f[k], y = 1ll * f[k + l] * Wnk % mod;
        f[k] = (x + y) % mod, f[k + l] = (x - y + mod) % mod;
      }
    }
  }
  if (t == -1)
    for (int inv = ksm(len), i = 0; i < len; i++) f[i] = 1ll * f[i] * inv % mod;
}
void Pinv(int deg, int *f, int *g) {
  if (deg == 1) {
    g[0] = ksm(f[0]);
    return;
  }
  Pinv(deg + 1 >> 1, f, g), init(deg);
  for (int i = 0; i < deg; i++) invF[i] = f[i];
  for (int i = deg; i < len; i++) invF[i] = 0;
  dft(invF, 1), dft(g, 1);
  for (int i = 0; i < len; i++)
    g[i] = (2ll * g[i] % mod - 1ll * g[i] * g[i] % mod * invF[i] % mod + mod) % mod;
  dft(g, -1);
  for (int i = deg; i < len; i++) g[i] = 0;
}
void Psqr(int deg, int *f, int *g) {
  if (deg == 1) {
    g[0] = 1;
    return;
  }
  Psqr(deg + 1 >> 1, f, g);
  for (int i = 0; i < deg << 1; i++) inv[i] = 0;
  Pinv(deg, g, inv);
  for (int i = 0; i < deg; i++) sqrF[i] = f[i];
  for (int i = 0; i < deg; i++) cout << sqrF[i] << " ";
  cout << endl;
  for (int i = 0; i < deg; i++) cout << inv[i] << " ";
  cout << endl;
  dft(sqrF, 1), dft(g, 1), dft(inv, 1);
  for (int i = 0; i < len; i++)
    g[i] = 1ll * (1ll * g[i] * g[i] % mod + sqrF[i]) * inv[i] % mod;
  dft(g, -1);
  for (int i = 0, Inv = ksm(2); i < deg; i++) {
    g[i] = 1ll * g[i] * Inv % mod;
    cout << g[i] << " ";
  }
  cout << endl;
  for (int i = deg; i < len; i++) g[i] = 0;
}
void main() { 
  Psqr(n, a, sqr);
  //init(n), dft(sqr, 1);
  //for (int i = 0; i < len; i++) sqr[i] = 1ll * sqr[i] * sqr[i] % mod;
  //dft(sqr, -1);
  for (int i = 0; i < n; i++) printf("%d ", sqr[i]);
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("5205.in", "r", stdin);
  freopen("5205.out", "w", stdout);
#endif
  Input::main();
  Solve::main();
}
