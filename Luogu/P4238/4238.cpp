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

const int Max_n = 6e5 + 5;
const unsigned long long mod = 998244353;
int n, a[Max_n], ans[Max_n];

namespace Input {
void main() { 
  fread(read_str, 1, 1 << 25, stdin); 
  n = read();
  for (int i = 0; i < n; i++) a[i] = read();
}
}  // namespace Input

int ksm(int a, int b = mod - 2) {
  int res = 1;
  for (; b; b >>= 1, a = (LL)a * a % mod)
    if (b & 1) res = (LL)res * a % mod;
  return res;
}

namespace Poly {
int bit, len, rev[Max_n];
void init(int n) {
  len = 1 << (bit = log2(n - 1) + 1);
  for (int i = 0; i < len; i++) rev[i] = rev[i >> 1] >> 1 | ((i & 1) << bit - 1);
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
        int x = f[k];
        int y = (LL)f[k + l] * Wnk % mod;
        f[k] = x + y, Mod(f[k]);
        f[k + l] = x - y + mod, Mod(f[k + l]);
      }
    }
  }
  if (t)
    for (int i = 0, Inv = ksm(len); i < len; i++) 
      f[i] = 1ll * f[i] * Inv % mod;
}
void Inv(int *f, int *inv, int N) {
  static int F[Max_n];
  inv[0] = ksm(f[0]), inv[1] = 0;
  for (int deg = 2; deg < (N << 1); deg <<= 1) {
    init(deg * 2);
    for (int i = 0; i < deg; i++) F[i] = f[i];
    for (int i = deg; i < len; i++) F[i] = inv[i] = 0;
    dft(F, 0), dft(inv, 0);
    for (int i = 0; i < len; i++) 
      inv[i] = (LL)inv[i] * (mod + 2 - (LL)F[i] * inv[i] % mod) % mod;
    dft(inv, 1);
    for (int i = deg; i < len; i++) inv[i] = 0;
  }
}
}  // namespace Poly
using namespace Poly;

namespace Solve {
void main() {
  Inv(a, ans, n);
  for (int i = 0; i < n; i++) printf("%d ", ans[i]);
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("4238.in", "r", stdin);
  freopen("4238.out", "w", stdout);
#endif
  Input::main();
  Solve::main();
}
