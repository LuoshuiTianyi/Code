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

const int Max_n = 130000 << 2, mod = 1004535809;
int n;
int F[Max_n], G[Max_n], f[Max_n], g[Max_n];

namespace Poly {
int ksm(int a, int b = mod - 2) {
  int res = 1;
  for (; b; b >>= 1, a = (LL)a * a % mod)
    if (b & 1) res = (LL)res * a % mod;
  return res;
}
int len, bit, rev[Max_n];
void init(int n) {
  len = 1 << (bit = log2(n) + 1);
  for (int i = 0; i < len; i++)
    rev[i] = rev[i >> 1] >> 1 | ((i & 1) << bit - 1);
}
void dft(int *f, bool t) {
  for (int i = 0; i < len; i++)
    if (rev[i] > i) swap(f[i], f[rev[i]]);
  for (int l = 1; l < len; l <<= 1) {
    int Wn = ksm(3, (mod - 1) / (l << 1));
    if (t) Wn = ksm(Wn);
    for (int i = 0; i < len; i += l << 1) {
      int Wnk = 1;
      for (int k = i; k < i + l; k++, Wnk = (LL)Wnk * Wn % mod) {
        int x = f[k], y = (LL)f[k + l] * Wnk % mod;
        f[k] = (x + y) % mod, f[k + l] = (x + mod - y) % mod;
      }
    }
  }
  if (t)
    for (int i = 0, Inv = ksm(len); i < len; i++) f[i] = (LL)f[i] * Inv % mod;
}
void Mul(int *f, int *g, int N) {
  init(N);
  dft(f, 0), dft(g, 0);
  for (int i = 0; i < len; i++) f[i] = (LL)f[i] * g[i] % mod;
  dft(g, 1), dft(f, 1);
}
}  // namespace Poly

namespace Input {
void main() {
  n = read();
}
}  // namespace Input

namespace Init {
void main() {
  for (int i = 0; i <= n; i++) G[i] = ksm(2, (LL)n * (n - 1) / 2 % (mod - 1));
}
}  // namespace Init

namespace Solve {
void Solve(int l, int r) {
  if (l == r) {
    F[l] = (G[l] + mod - F[l]) % mod;
    return;
  }
  int mid = l + r >> 1;
  Solve(l, mid);
  int l1 = 0, l2 = 0;
  for (int i = l; i <= mid; i++) f[l1++] = F[i];
  for (int i = 1; i <= r - l; i++) g[l2++] = G[i];
  for (int i = l1; i < len; i++) f[i] = 0;
  for (int i = l2; i < len; i++) g[i] = 0;
  Mul(f, g, l1 + l2);
  Solve(mid + 1, r);
}
void main() {
  Solve(1, n);
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("4841.in", "r", stdin);
  freopen("4841.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
