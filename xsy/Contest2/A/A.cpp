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

const int Max_n = 405;
int n, m, s, ans;
int l[Max_n], r[Max_n];

namespace Input {
void main() {
  n = read(), m = read(), s = read();
  for (int i = 1; i <= n; i++) l[i] = read(), r[i] = read();
}
}  // namespace Input

namespace Solve {
void Solve2() {
  for (int i = 1; i <= n; i++)
    for (int j = i; j <= n; j++) {
      int L = max(l[i], s - r[j]), R = min(r[i], s - l[j]);
      if (R >= L) ans += R - L + 1;
    }
  cout << ans;
}
void Solve3() {
}
void Solve4() {
}
void main() {
  m == 2 ? Solve2() : m == 3 ? Solve3() : Solve4();
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("A.in", "r", stdin);
  freopen("A.out", "w", stdout);
#endif
  Input::main();
  Solve::main();
}
