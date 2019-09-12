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
char S[Max_n];
inline void Input() {
  n = read(), m = read(), Q = read();
  scanf("%s", S + 1);
}
inline void DP() {
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
