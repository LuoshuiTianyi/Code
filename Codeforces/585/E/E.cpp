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

const int Max_n = 1e7 + 5;
int n;
int cnt, pri[Max_n], mu[Max_n];
int f[Max_n], c[Max_n], s[Max_n];
bool vis[Max_n];

namespace Input {
void main() { 
  fread(read_str, 1, 1 << 25, stdin); 
  n = read();
  for (int i = 1; i <= n; i++) c[read()]++;
}
}  // namespace Input

namespace Init {
void main() {
  mu[1] = 1;
  for (int i = 2; i <= 1e7; i++) {
    if (!vis[i]) pri[++cnt] = i, mu[i] = -1;
    for (int j = 1; j <= cnt && pri[j] * i <= 1e7; j++) {
      vis[pri[j] * i] = 1, mu[pri[j] * i] = -mu[i];
      if (i % pri[j] == 0) {
        mu[pri[j] * i] = 0;
        break;
      }
    }
  }
}
}  // namespace Init

namespace Solve {
void main() {
  for (int i = 1; i <= 1e7; i++)
    for (int j = i << 1; j <= 1e7; j += i) c[i] += c[j];
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
