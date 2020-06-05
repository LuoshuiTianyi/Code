#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
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

const int N = 1e6 + 7, mod = 1e9 + 7;
int n, p, a[N];

int ksm(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = (LL)a * a % mod)
    if (b & 1) res = (LL)res * a % mod;
  return res;
}
void solve() {
  n = read(), p = read();
  for (int i = 1; i <= n; i++) a[i] = read();
  if (p == 1) return void(printf("%d\n", (n & 1)));
  sort(a + 1, a + n + 1);
  reverse(a + 1, a + n + 1);
  int ans = ksm(p, a[1]) % mod;
  LL c = 1;
  int k = a[1], w = log(n) / log(p) + 1;
  for (int i = 2; i <= n; i++) {
    if (k - a[i] > w) {
      if (c > 0)
        c = n;
      else if (c < 0)
        c = -n;
      k = a[i];
    } else
      while (k > a[i]) {
        --k;
        c *= p;
        if (c > n) {
          c = n;
          break;
        }
        if (c < -n) {
          c = -n;
          break;
        }
      }
    if (c <= 0) {
      (ans += (p ^ a[i]) % mod) %= mod;
      ++c;
    } else {
      (ans += mod - (p ^ a[i]) % mod) %= mod;
      --c;
    }
  }
  printf("%d\n", ans);
}

int main() {
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
  fread(read_str, 1, 1 << 25, stdin);
  int T = read();
  while (T--) solve();
  return 0;
}
