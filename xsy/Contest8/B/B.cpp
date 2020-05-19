#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
#define LL long long
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])

char s[1 << 25], *S = s;
#define getchar() (*S++)
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

const int Max_n =  3e5 + 5;
int n, m;
int ql[Max_n], qr[Max_n];
char S[Max_n];
LL Ans[Max_n];
vector<int> M1, M2;

int c1[Max_n], c2[Max_n], c3[Max_n];

namespace Input {
void main() { 
  fread(s, 1, 1 << 25, stdin); 
  n = read(), m = read();
  scanf("%s", S + 1);
  for (int i = 1; i <= m; i++) read(ql[i]), read(qr[i]), M2[qr[i]].push_back(i);
}
}  // namespace Input

namespace Init {
void main() {
}
}  // namespace Init

namespace Solve {
void main() {}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
