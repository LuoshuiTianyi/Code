#include <algorithm>
#include <cmath>
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

const int Max_n = 1e3;
LL n, ans;
LL top, stk[Max_n];
LL f[Max_n];

int main() {
#ifndef ONLINE_JUDGE
  freopen("2303.in", "r", stdin);
  freopen("2303.out", "w", stdout);
#endif
  n = read();
  for (LL i = sqrt(n); i; i--)
    if (n % i == 0) {
      stk[++top] = i, stk[++top] = n / i;
      if (i * i == n) top--;
    }
  sort(stk + 1, stk + top + 1);
  for (int i = top; i; i--) {
    f[i] = n / stk[i];
    for (int j = i + 1; j <= top; j++)
      if (stk[j] % stk[i] == 0) f[i] -= f[j];
    ans += f[i] * stk[i];
  }
  cout << ans;
}
