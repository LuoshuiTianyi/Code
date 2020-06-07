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

const int Max_n = 1e5 + 5;
int T;
int n, K, a[Max_n];
bool fl;

namespace Input {
void main() { 
  fread(read_str, 1, 1 << 25, stdin); 
  n = read(), K = read(), fl = 0;
  for (int i = 1; i <= n; i++) fl |= (a[i] = read()) == K;
}
}  // namespace Input

namespace Solve {
void main() {
  if (fl) {
    puts("no");
    return;
  }
  if (n == 1) {
    puts("yes");
    return;
  }
  for (int i = 1; i < n; i++)
    if (a[i] >= K && a[i + 1] >= K) {
      puts("yes");
      return;
    }
  for (int i = 1; i < n - 1; i++)
    if (a[i] >= K && a[i + 2] >= K) {
      puts("yes");
      return;
    }
  puts("no");
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
#endif
  T = read();
  while (T--) {
    Input::main();
    Solve::main();
  }
}
