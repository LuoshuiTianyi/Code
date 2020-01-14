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

const int Max_n = 101, mod = 1e9;
int n, m;
int b[Max_n][Max_n], dx[5] = {0, 1, -1, 0, 0}, dy[5] = {0, 0, 0, 1, -1};
int cntd, id[Max_n][Max_n];
char a[Max_n][Max_n];

namespace Input {
void main() {
  n = read(), m = read();
  for (int i = 1; i <= n; i++) scanf("%s", a[i] + 1);
}
}  // namespace Input

namespace Init {
void main() {
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      if (a[i][j] != '*') id[i][j] = cntd++;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++)
      for (int k = 1; k <= 4; k++) {
        if (a[i][j] == '*') continue;
        int x = i + dx[k], y = j + dy[k];
        if (x < 1 || x > n || y < 1 || y > m || a[x][y] == '*') continue;
        b[id[i][j]][id[i][j]]++, b[id[i][j]][id[x][y]]--;
      }
}
}

namespace Solve {
int Guess(int n) {
  int ans = 1;
  for (int i = 1; i <= n; i++) {
    for (int k = i + 1; k <= n; k++)
      while (b[k][i]) {
        int d = b[i][i] / b[k][i];
        for (int j = i; j <= n; j++) (b[i][j] -= 1ll * d * b[k][j] % mod) %= mod;
        swap(b[k], b[i]), ans = -ans;
      }
    ans = 1ll * ans * b[i][i] % mod;
  }
  return (ans + mod) % mod;
}
void main() {
  cout << Guess(cntd - 1);
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("4111.in", "r", stdin);
  freopen("4111.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
