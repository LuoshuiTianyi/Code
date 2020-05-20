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

const int Max_n = 2e5 + 5;
int n, Q;
int a[Max_n], l[Max_n], r[Max_n];
bool vis[Max_n];
LL ans[Max_n];
priority_queue<pair<int, LL> > q;

namespace Input {
void main() { 
  fread(read_str, 1, 1 << 25, stdin); 
  read(n);
  for (int i = 1; i <= n; i++) read(a[i]), l[i] = i - 1, r[i] = i + 1, q.push(make_pair(a[i], i));
  r[n] = 0;
}
}  // namespace Input

namespace Solve {
void main() {
  int x;
  for (int i = 1; i <= (n + 1 >> 1); i++) {
    ans[i] = ans[i - 1];
    for (x = q.top().second; vis[x]; q.pop(), x = q.top().second);
    q.pop(), ans[i] += a[x];
    a[x] = a[l[x]] + a[r[x]] - a[x], vis[l[x]] = vis[r[x]] = 1;
    if (l[x] && r[x]) {
      q.push(make_pair(a[x], x));
      l[x] = l[l[x]], r[x] = r[r[x]];
      r[l[x]] = x, l[r[x]] = x;
    } else if (l[x]) {
      r[l[l[x]]] = 0;
    } else if (r[x]) {
      l[r[r[x]]] = 0;
    }
  }
  read(Q);
  while (Q--) {
    read(x);
    printf("%lld\n", ans[x]);
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
