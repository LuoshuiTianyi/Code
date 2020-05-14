#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
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

const int Max_n = 1.6e6 + 5, mod = 998244353;
int T;
int n, a[Max_n];
vector<int> f[800000];

namespace Input {
void main() {
  n = read();
  for (int i = 1; i <= n; i++) a[i] = read();
}
}  // namespace Input

namespace Poly {
int len, bit, rev[Max_n];
int ksm(int a, int b = mod - 2) {
  int res = 1;
  for (; b; b >>= 1, a = (LL)a * a % mod)
    if (b & 1) res = (LL)res * a % mod;
  return res;
}
void init(int n) {
  len = 1 << (bit = log2(n) + 1);
  for (int i = 0; i < len; i++)
    rev[i] = rev[i >> 1] >> 1 | ((i & 1) << bit - 1);
}
void dft(vector<int> &f, bool t) {
  for (int i = 0; i < len; i++)
    if (rev[i] > i) swap(f[i], rev[i]);
  for (int l = 1; l < len; l <<= 1) {
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
void Mul(vector<int> &f, vector<int> &g, vector<int> &res, int N) {
  init(N + 1);
  static vector<int> G;
  res.resize(len, 0), G.resize(len, 0);
  for (int i = 0; i < f.size(); i++) res[i] = f[i];
  for (int i = 0; i < g.size(); i++) G[i] = g[i];
  dft(res, 0), dft(G, 0);
  for (int i = 0; i < len; i++) res[i] = (LL)res[i] * G[i] % mod;
  dft(res, 1);
}
void Inv(vector<int> &f, vector<int> &res, int N) {
  init(N * 3);
  res.resize(len, 0);
  static vector<int> F;
  F.resize(len, 0);
  res[0] = ksm(f[0]);
  for (int deg = 2; deg < (N << 1); deg <<= 1) {
    init(deg * 3);
    for (int i = 0; i < min(deg, ); i++) F[i] = f[i];
  }
}
}  // namespace Poly

namespace Solve {
void main() {}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("2409.in", "r", stdin);
  freopen("2409.out", "w", stdout);
#endif
  //T = read();
  //while (T--) {
  //  Input::main();
  //  Solve::main();
  //}
}
