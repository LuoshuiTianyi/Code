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

const int Max_n = 55;
int n, mod, k, r;
int a[Max_n], ans[Max_n];

namespace Input {
void main() {
  n = read(), mod = read(), k = read(), r = read();
}
}  // namespace Input

namespace Solve {
void mul(int *a, int b[]) {
  int res[Max_n] = {0};
  for (int i = 0; i < k; i++)
    for (int j = 0; j < k; j++)
      (res[(i + j) % k] += (LL)a[i] * b[j] % mod) %= mod;
  for (int i = 0; i < k; i++) a[i] = res[i];
}
void main() {
  LL N = (LL)n * k;
  a[0] = a[1] = 1, ans[0] = 1;
  if (k == 1) a[0] = 2 % mod, a[1] = 0;
  for (; N; N >>= 1, mul(a, a))
    if (N & 1) mul(ans, a);
  cout << ans[r] << endl;
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("2143.in", "r", stdin);
  freopen("2143.out", "w", stdout);
#endif
  Input::main();
  Solve::main();
}
