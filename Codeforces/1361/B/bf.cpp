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

const int Max_n = 1e6 + 5, Max = 1e8 + 5, mod = 1e9 + 7;
int T;
int n, p, ans, tot;
int a[Max_n];
bool f[Max];

namespace Input {
int ksm(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = (LL)a * a % mod)
    if (b & 1) res = (LL)res * a % mod;
  return res;
}
void main() {
  n = read(), p = read(), tot = 0;
  for (int i = 1; i <= n; i++) tot += (a[i] = ksm(p, read()));
}
}  // namespace Input

namespace Solve {
void main() {
  f[0] = 1;
  for (int i = 1; i <= tot; i++) f[i] = 0;
  for (int i = 1; i <= n; i++)
    for (int j = tot; j >= a[i]; j--) f[j] |= f[j - a[i]];
  int ans = 1e9;
  for (int i = 1; i <= tot; i++)
    if (f[i]) ans = min(ans, abs(tot - i - i));
  cout << ans << endl;
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("B.in", "r", stdin);
  freopen("B.ans", "w", stdout);
#endif
  fread(read_str, 1, 1 << 25, stdin);
  T = read();
  while (T--) {
    Input::main();
    Solve::main();
  }
}
