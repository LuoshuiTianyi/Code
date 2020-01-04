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

const int Maxx = 1e6 + 5;
LL ans;
int n, siz;
int minn[Maxx], nu[Maxx];

namespace Input {
void main() {
  n = read();
  for (int i = 1; i <= n; i++) {
    int Min = 1e9, Max = -1e9, tot = read();
    bool fl = 0;
    for (int j = 1; j <= tot; j++) {
      int x = read();
      fl |= x > Min;
      Max = max(Max, x), Min = min(Min, x);
    }
    siz += fl;
    if (!fl) minn[i] = Min, nu[Max]++;
    else minn[i] = -1;
  }
  for (int i = 1e6; ~i; i--) nu[i] += nu[i + 1];
}
}  // namespace Input

namespace Solve {
void main() {
  for (int i = 1; i <= n; i++) {
    if (minn[i] == -1) ans += n;
    else ans += siz + nu[minn[i] + 1];
  }
  cout << ans;
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
#endif
  Input::main();
  Solve::main();
}
