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
int T;
int n;
char s[1005];
int main() {
#ifndef ONLINE_JUDGE
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
#endif
  T = read();
  while (T--) {
    n = read();
    scanf("%s", s + 1);
    int l = 0, r = 0;
    for (int i = 1; i <= n; i++)
      if (!l && s[i] == '1') l = i;
    for (int i = n; i >= 1; i--)
      if (!r && s[i] == '1') r = i;
    if (!l) {
      cout << n << endl;
    } else {
      if (n - l + 1 > l) l = n - l + 1;
      if (n - r + 1 > r) r = n - r + 1;
      cout << max(n + 1, max((l << 1), (r << 1))) << endl;
    }
  }
}
