#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])

char read_str[1 << 25], *CH = read_str;
#define getchar() (*CH++)
LL read() {
  char ch = getchar();
  int fl = 0;
  LL x = 0;
  while (!isdigit(ch)) {
    if (ch == '-') fl = 1;
    ch = getchar();
  }
  while (isdigit(ch)) x = (x << 1) + (x << 3) + ch - '0', ch = getchar();
  return fl ? -x : x;
}
void rstr(char *s) {
  char *x = s;
  char ch = getchar();
  while (ch == ' ' || ch == '\n' || ch == '\r') ch = getchar();
  while (ch != ' ' && ch != '\n' && ch != '\r') {
    *x++ = ch;
    ch = getchar();
  }
}

const int Max_n = 205, mod = 998244353;
int n, K, ans;
LL a[Max_n];
bool vis[Max_n];

namespace Input {
void main() { 
  fread(read_str, 1, 1 << 25, stdin); 
  n = read(), K = read();
  for (int i = 1; i <= n; i++) a[i] = read();
}
}  // namespace Input

namespace Solve {
void main() {
  for  (int i = 1; i <= n; i++) {
    int s1 = 1, s2 = i;
    for (int j = 0; j < K; j++) {
      if ((a[i] >> j & 1) && !vis[j]) vis[j] = 1, s1 = (s1 << 1) % mod;
      if (!(a[i] >> j & 1) && !vis[j]) s2 = (s2 << 1) % mod;
    }
    (ans += (LL)s1 * s2 % mod) %= mod;
    (ans += mod - (LL)s2) %= mod;
  }
  cout << ans << endl;
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("I.in", "r", stdin);
  freopen("I.out", "w", stdout);
#endif
  Input::main();
  Solve::main();
}
