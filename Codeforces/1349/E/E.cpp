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

const int Max_n = 2e5 + 5;
int n, nu;
bool ans[Max_n];
LL Max, fnl, a[Max_n], b[Max_n];

namespace Input {
void main() { 
  fread(read_str, 1, 1 << 25, stdin); 
  n = read();
  for (int i = 1; i <= n; i++) {
    a[i] = read();
    if (a[i] > Max) Max = a[i], nu = 0;
    nu += a[i] == Max;
  }
}
}  // namespace Input

namespace Init {
void main() {
  for (int i = 1; i <= n; i++) b[i] = b[i - 1] + i - 1;
}
}

namespace Solve {
void main() {
  if (Max <= 1) {
    for (int i = 1; i <= n; i++) printf("0");
    return;
  }
  if (nu >= 2) fnl = Max;
  int bef = 0;
  for (int i = 1; i <= n; i++)
    if (a[i] != fnl) {
      ans[i] = 1;
      LL res = a[i] - a[bef] - (n - i + 1), lim = i - 1;
      int num = i - bef - 1;
      for (int j = 1; j <= num; j++) {
        res -= bef + 1;
        if (b[j] <= res && res <= b[num]) {
          while (j--) {
            int now = min(res, lim);
            if (now == lim) lim--;
            ans[now + bef] = 1, res -= now;
          }
          break;
        }
      }
      bef = i;
    }
  if (fnl)
  for (int i = 1; i <= n; i++) printf("%d",  ans[i]);
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("E.in", "r", stdin);
  freopen("E.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
