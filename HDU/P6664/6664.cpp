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
int T;
int n, m, Q;
int pw[Max_n], f[Max_n][20];
char S[Max_n];
inline void Input() {
  n = read(), m = read(), Q = read();
  scanf("%s", S + 1);
}
inline void get_to(int i, int j, int k) {
  return (k * pw[i] + j) % m;
}
inline void DP() {
  pw[1] = 1, f[0][0] = 1;
  for (int i = 2; i <= n; i++) pw[i] = pw[i - 1] * 10 % m;
  for (int i = 1; i <= n; i++)
    for (int j = 0; j < m; j++)
      for (int k = 0; k <= 9; k++) {
        int to = get_to(i, j, k);
      }
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("6664.in", "r", stdin);
  freopen("6664.out", "w", stdout);
#endif
  T = read();
  while (T--) {
    Input();
    DP();
  }
}
