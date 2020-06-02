#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
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

const int Max_n = 100;
int T, N;
LL n, t, a[Max_n * 20];
LL f[Max_n];
map<LL, bool> M;
map<LL, bool>::iterator it;

namespace Input {
void main() { 
  fread(read_str, 1, 1 << 25, stdin); 
}
}  // namespace Input

namespace Init {
void Count(LL x) {
  LL c = 1;
  for (int i = 1; i <= 19; i++, c *= 10)
    M[(x / c / 10) * c + x % c] = 1;
}
void main() {
  N = 1, f[1] = 1;
  for (N = 2;; N++) {
    f[N] = f[N - 1] + f[N - 2];
    if (f[N] >= 1e18) break;
    M[f[N]] = 1;
    if (f[N] <= 1e17) Count(f[N]);
  }
  for (it = M.begin(); it != M.end(); it++)
    if (it->first <= 1e18) a[++t] = it->first;
}
}  // namespace Init

namespace Solve {
void main() {
  T = read();
  while (T--) {
    n = read();
    LL ans = n + 1 - (lower_bound(a + 1, a + t + 1, n) - a);
    printf("%lld\n", ans);
  }
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("H.in", "r", stdin);
  freopen("H.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
