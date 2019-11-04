#include <algorithm>
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

const int Max_n = 1e6 + 5, Max = 1 << 20, mod = 1e9 + 7;
int n, ans;
int a[Max_n], f[Max + 1], g[100];
int top, stk[20], nx[Max_n][20];
void Mod(int &x) { x = x >= mod ? x - mod : x < 0 ? x + mod : x; }

namespace Input {
void main() {
  n = read();
  for (int i = 1; i <= n; i++) a[i] = read();
}
}  // namespace Input

namespace Init {
int pos_now;
bool cmp(int a, int b) { return nx[pos_now][a] < nx[pos_now][b]; }
void main() {
  for (int j = 0; j < 20; j++)
    for (int i = n + 1; i; i--) nx[i][j] = (a[i] >> j & 1) ? nx[i + 1][j] : i;
  for (int i = 1; i <= n; i++) {
    top = 0, pos_now = i;
    for (int j = 0; j < 20; j++)
      if (a[i] >> j & 1) {
        stk[++top] = j;
        cout << i << " " << a[i] << " " << j << " " << nx[i][j] << endl;
      }
    stable_sort(stk + 1, stk + top + 1, cmp);
    int now = a[i];
    f[now] += nx[i][stk[1]] - i, now ^= (1 << stk[1]);
    for (int j = 2; j <= top; j++) {
      if (nx[i][stk[j]] != nx[i][stk[j - 1]]) {
        f[now] += nx[i][stk[j]] - nx[i][stk[j - 1]];
        //cout << i << " " << now << " " << stk[j - 1] << " " << nx[stk[j]] << endl;
      }
      now ^= (1 << stk[j]);
    }
  }
  for (int j = 0; j < 20; j++)
    for (int i = 0; i < Max; i++)
      if (!(i >> j & 1)) Mod(f[i] += f[i | (1 << j)]);
}
}  // namespace Init

namespace Solve {
void main() {
  for (int i = 0; i < Max; i++) Mod(g[__builtin_popcount(i)] += f[i]);
  for (int i = 0; i <= 20; i++)
    if (i & 1)
      Mod(ans -= g[i]);
    else
      Mod(ans += g[i]);
  cout << ans;
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("D.in", "r", stdin);
  freopen("D.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
