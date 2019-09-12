#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define go(x, i, v) for (int i = hd[x], v = to[i]; i; v = to[i = nx[i]])
#define inline __inline__ __attribute__((always_inline))
inline LL read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int mod = 1e9 + 7, Max_n = 5e4 + 5;
const LL inf = 1e18;
int T;
int n, m, Q;
int pw[Max_n], son[Max_n][21];
int jp[17][Max_n][21];
LL f[Max_n][21];
char S[Max_n];
inline void Init() {
  n = read(), m = read(), Q = read();
  scanf("%s", S + 1);
  for (int i = 1; i <= n >> 1; i++) swap(S[i], S[n - i + 1]);
}
inline int get_to(int i, int j, int k) { return (k * pw[i] + j) % m; }
inline void Fix(LL &x) { x > inf ? x = inf + 1 : x; }
inline void DP() {
  pw[1] = 1, f[0][0] = 1;
  for (int i = 2; i <= n; i++) pw[i] = pw[i - 1] * 10 % m;
  for (int i = 1; i <= n; i++)
    for (int j = 0; j < m; j++) {
      son[i][j] = m + 1, f[i - 1][m + 1] = -inf;
      if (S[i] == '?') {
        for (int k = 0; k <= 9; k++) {
          int to = get_to(i, j, k);
          Fix(f[i][j] += f[i - 1][to]);
          if (f[i - 1][to] > f[i - 1][son[i][j]]) son[i][j] = to;
        }
      } else {
        int to = son[i][j] = get_to(i, j, S[i] - '0');
        Fix(f[i][j] += f[i - 1][to]);
      }
    }
}
void Solve() {
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("6664.in", "r", stdin);
  freopen("6664.out", "w", stdout);
#endif
  T = read();
  while (T--) {
    Init();
    DP();
    Solve();
  }
}
