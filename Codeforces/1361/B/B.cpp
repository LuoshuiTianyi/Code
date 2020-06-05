#include <algorithm>
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

const int Max_n = 1e6 + 5, mod = 1e9 + 7;
int T;
int n, p, ans, k[Max_n];
int top, stk[Max_n << 1], a[Max_n << 1];

namespace Input {
void main() {
  n = read(), p = read(), top = ans = 0;
  for (int i = 1; i <= n; i++) k[i] = read();
}
}  // namespace Input

namespace Init {
void main() {
  sort(k + 1, k + n + 1);
}
}  // namespace Init

namespace Solve {
int ksm(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = (LL)a * a % mod)
    if (b & 1) res = (LL)res * a % mod;
  return res;
}
void add(int x) {
  int now = x;
  while (a[now] == p - 1) a[now++] = 0;
  a[now]++, stk[++top] = now;
}
void main() {
  if (p == 1) {
    printf("%d\n", (n & 1));
    return;
  }
  int fl = 0;
  for (int i = n; i; i--) {
    if (!fl) {
      fl = k[i], ans = ksm(p, k[i]);
    } else {
      add(k[i]), stk[++top] = k[i], (ans += mod - ksm(p, k[i])) %= mod;
      if (a[fl]) a[fl] = 0, fl = top = 0;
    }
  }
  for (int i = 1; i <= top; i++) a[stk[i]] = 0;
  printf("%d\n", ans);
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
#endif
  fread(read_str, 1, 1 << 25, stdin);
  T = read();
  while (T--) {
    Input::main();
    Init::main();
    Solve::main();
  }
}
