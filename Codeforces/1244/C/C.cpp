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
LL n, p, w, d;
int main() {
#ifndef ONLINE_JUDGE
  freopen("C.in", "r", stdin);
  freopen("C.out", "w", stdout);
#endif
  n = read(), p = read(), w = read(), d = read();
  LL x = p / w;
  while ((p - x * w) % d != 0 && x > 0) x--;
  LL y = (p - x * w) / d;
  if (x + y <= n)
    cout << x << " " << y << " " 
}
