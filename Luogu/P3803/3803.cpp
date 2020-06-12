#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define Mod(x) (x >= mod ? x -= mod : 0)
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])

char read_str[1 << 25], *CH = read_str;
#define getchar() (*CH++)
LL read() {
  char ch = getchar();
  int fl = 0;
  LL x = 0;
  while (!isdigit(ch)) {
    if (ch == '-') fl = 1;
    ch = getchar();
  }
  while (isdigit(ch)) x = (x << 1) + (x << 3) + ch - '0', ch = getchar();
  return fl ? -x : x;
}
void rstr(char *s) {
  char *x = s;
  char ch = getchar();
  while (ch == ' ' || ch == '\n' || ch == '\r') ch = getchar();
  while (ch != ' ' && ch != '\n' && ch != '\r') {
    *x++ = ch;
    ch = getchar();
  }
}

const int Max_n = 1 << 21 | 1, Len = 1 << 21;
const unsigned long long mod = 998244353;
int n, m;
int f[Max_n], g[Max_n];
int gp[Len | 1];

namespace Input {
void main() { 
  fread(read_str, 1, 1 << 25, stdin); 
  n = read(), m = read();
  for (int i = 0; i <= n; i++) f[i] = read();
  for (int i = 0; i <= m; i++) g[i] = read();
}
}  // namespace Input

int ksm(int a, int b = mod - 2) {
  int res = 1;
  for (; b; b >>= 1, a = (LL)a * a % mod)
    if (b & 1) res = (LL)res * a % mod;
  return res;
}
namespace Init {
void main() {
  gp[0] = 1;
  int g = ksm(3, (mod - 1) / Len);
  for (int i = 1; i <= Len; i++) gp[i] = (LL)gp[i - 1] * g % mod;
}
}  // namespace Init

namespace Poly {
int bit, len, rev[Max_n];
void init(int n) {
  len = 1 << (bit = log2(n) + 1);
  for (int i = 0; i < len; i++) rev[i] = rev[i >> 1] >> 1 | ((i & 1) << bit - 1);
}
void dft(int *f, bool t) {
  for (int i = 0; i < len; i++)
    if (rev[i] > i) swap(f[i], f[rev[i]]);
  for (int l = 1; l < len; l <<= 1) {
    int Wn = Len / (l << 1);
    for (int i = 0; i < len; i += l << 1) {
      for (int k = i; k < i + l; k++) {
        int x = f[k], p = (k - i) * Wn;
        int y = (LL)f[k + l] * (t ? gp[Len - p] : gp[p]) % mod;
        f[k] = x + y, Mod(f[k]);
        f[k + l] = x - y + mod, Mod(f[k + l]);
      }
    }
  }
  if (t)
    for (int i = 0, Inv = ksm(len); i < len; i++) 
      f[i] = (LL)f[i] * Inv % mod;
}
}  // namespace Poly
using namespace Poly;

namespace Solve {
void main() {
  init(n + m + 2);
  dft(f, 0), dft(g, 0);
  for (int i = 0; i < len; i++) f[i] = (LL)f[i] * g[i] % mod;
  dft(f, 1);
  for (int i = 0; i <= n + m; i++) printf("%d ", f[i]);
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("3803.in", "r", stdin);
  freopen("3803.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
