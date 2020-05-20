#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
#define LL long long
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])

char read_str[1 << 25], *CH = read_str;
#define getchar() (*CH++)
template <typename T>
void read(T &x) {
  char ch = getchar();
  int fl = 0;
  x = 0;
  while (!isdigit(ch)) {
    if (ch == '-') fl = 1;
    ch = getchar();
  }
  while (isdigit(ch)) x = (x << 1) + (x << 3) + ch - '0', ch = getchar();
  if (fl) x = -x;
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
int n, Q;
int a[Max_n], l[Max_n], r[Max_n];
LL ans[Max_n];
priority_queue<pair<int, int> > q;

namespace Input {
void main() { 
  fread(read_str, 1, 1 << 25, stdin); 
  read(n), read(Q);
  for (int i = 1; i <= n; i++) a[i] = read(), l[i] = i - 1, r[i] = i + 1, q.push(make_pair(a[i], i));
  r[n] = 0;
}
}  // namespace Input

namespace Solve {
void main() {
  for (int i = 1; i <= (n + 1 >> 1); i++) {
  }
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
