#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])

char s[1 << 25], *S = s;
#define getchar() (*S++)
template <typename T>
void read(T &x) {
  char ch = getchar();
  int fl = 0;
  x = 0;
  while (!isdigit(ch)) {
    if (ch == '-') fl = 1;
    ch = getchar();
  }
  while (isdigit(ch)) x = (x << 1) + (x << 3) + ch - '0', ch = getchar();
  if (fl) x = -x;
}

const int Max_n = 1e5 + 5, mod = 998244353;
int n, m;
int f[Max_n], g[Max_n];
int dp[Max_n][2];

namespace Input {
void main() { 
  fread(s, 1, 1 << 25, stdin); 
  read(n), read(m);
}
}  // namespace Input

namespace Init {
void main() {
  for (int i = 1; i <= n; i++) f[i] = 1;
  g[1] = m;
  for (int j = 2; j <= 17; j++) {
    for (int i = m; i; i--) {
      if (!f[i]) continue;
      for (int j = i << 1; j <= m; j += i) (f[j] += f[i]) %= mod;
      f[i] = 0;
    }
    for (int i = 1; i <= m; i++) (g[j] += f[i]) %= mod;
  }
}
}  // namespace Init

namespace Solve {
void main() {
  dp[0][0] = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 1; j <= min(17, n - i); j++) {
      (dp[i + j][(j & 1) ^ 1] += (LL)dp[i][0] * g[j] % mod) %= mod;
      (dp[i + j][j & 1] += (LL)dp[i][1] * g[j] % mod) %= mod;
    }
  }
  cout << (dp[n][0] - dp[n][1] + mod) % mod;
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
