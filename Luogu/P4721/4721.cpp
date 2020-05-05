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

const int Max_n = 4e5 + 5, Mod = 998244353;

int n;
int f[Max_n], g[Max_n];

namespace Poly {
int ksm(int a, int b = mod - 2) {
  int res = 1;
  for (; b; b >>= 1, a = (LL)a * a % mod)
    if (b & 1) a = (LL)a * a % mod;
  return res;
}
int len, bit, rev[Max_n];
void init(int n) {
  len = 1 << (bit = log2(n) + 1);
  for (int i = 0; i < len; i++)
    rev[i] = rev[i >> 1] >> 1 | ((i & 1) << bit - 1);
}
void dft(int *f, int t) {
  for (int i = 0; i < len; i++)
    if (rev[i] > i) swap(f[rev[i]], f[i]);
  for (int l = 1; l < len; l++) {
    int Wn = ksm(3, (mod - 1) / (l << 1));
    if (t) Wn = ksm(Wn);
    for (int i = 0; i < len; i += l << 1) {
      int Wnk = 1;
      for (int j = i; j < i + l; j++, Wnk = (LL)Wnk * Wn % mod) {
        int x = f[j], y = (LL)f[j + l] * Wnk % mod;
        f[j] = (x + y) % mod, f[j + l] = (x - y + mod) % mod;
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
  dft(f, 1), dft(g, 1);
}
}  // namespace Poly

namespace Input {
void main() {
  n = read();
  for (int i = 1; i < n; i++) g[i] = read();
  f[0] = 1;
}
}  // namespace Input

namespace Solve {
void main() {
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("4721.in", "r", stdin);
  freopen("4721.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
