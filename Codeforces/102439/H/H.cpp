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

const int Max_n = 100;
int T, N;

namespace Input {
void main() { 
  fread(read_str, 1, 1 << 25, stdin); 
}
}  // namespace Input

namespace Solve {
int top, nu[Max_n];
LL f[Max_n][2][2];
bool pd(int x) { return (x == 1) || (x == 2) || (x == 3) || (x == 5) || (x == 8); }
LL DP(int len, bool lim, bool m) {
  if (!len) return !m;
  LL &res = f[len][lim][m];
  if (res != -1) return res;
  res = 0;
  for (int i = 0; i <= (lim ? nu[len] : 9); i++)
    res += DP(len - 1, lim && (i == nu[len]), m | pd(i));
  return res;
}
void main() {
  T = read();
  while (T--) {
    LL n = read();
    top = 0;
    while (n) nu[++top] = n % 10, n /= 10;
    for (int i = 1; i <= top; i++)
      f[i][0][0] = f[i][0][1] = f[i][1][0] = f[i][1][1] = -1;
    cout << DP(top, 1, 0) << endl;
  }
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("H.in", "r", stdin);
  freopen("H.out", "w", stdout);
#endif
  Input::main();
  Solve::main();
}
