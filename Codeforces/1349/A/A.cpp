#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
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
int n, a[Max_n];
LL ans;
vector<int> nu[Max_n << 1];

namespace Input {
void main() { 
  fread(read_str, 1, 1 << 25, stdin); 
  n = read();
  for (int i = 1; i <= n; i++) {
    a[i] = read();
    for (int j = 2; j * j <= a[i]; j++)
      if (a[i] % j == 0) {
        int now = 0;
        while (a[i] % j == 0) a[i] /= j, now++;
        nu[j].push_back(now);
      }
  }
}
}  // namespace Input

namespace Solve {
void main() {
  ans = 1;
  for (int i = 2; i <= 2e5; i++)
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
