#include <cstdio>
#include <iostream>
#include <vector>
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

const int Max_n =  3e5 + 5;
int n, m;
int ql[Max_n], qr[Max_n], p[Max_n];
char S[Max_n];
LL Ans[Max_n];
vector<int> M1[Max_n], M2[Max_n];

namespace Input {
void main() { 
  fread(read_str, 1, 1 << 25, stdin); 
  read(n), read(m), rstr(S + 1);
  for (int i = 1; i <= m; i++) read(ql[i]), read(qr[i]), M2[qr[i]].push_back(i);
}
}  // namespace Input

namespace Init {
int top, stk[Max_n], sum[Max_n];
void main() {
  for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + (S[i] == '(' ? 2 : -1);
  for (int i = 1; i <= n; i++) {
    while (top && sum[stk[top] - 1] > sum[i]) p[stk[top--]] = i - 1;
    if (S[i] == '(') stk[++top] = i;
  }
  while (top) p[stk[top--]] = n;
  for (int i = n; i >= 1; i--) sum[i] = sum[i + 1] + (S[i] == ')' ? 2 : -1);
  stk[top = 0] = n + 1;
  for (int i = n; i >= 1; i--) {
    while (top && sum[stk[top] + 1] > sum[i]) p[stk[top--]] = i + 1;
    if (S[i] == ')') stk[++top] = i;
  }
  while (top) p[stk[top--]] = 1;
}
}  // namespace Init

namespace SegTree {
int nu[Max_n << 2], tag[Max_n << 2];
LL sum[Max_n << 2];
int L, R;
#define ls (o << 1)
#define rs (o << 1 | 1)
#define mid (l + r >> 1)
void pushdown(int o) {
  sum[ls] += (LL)tag[o] * nu[ls], sum[rs] += (LL)tag[o] * nu[rs];
  tag[ls] += tag[o], tag[rs] += tag[o];
  tag[o] = 0;
}
void pushup(int o) {
  nu[o] = nu[ls] + nu[rs], sum[o] = sum[ls] + sum[rs];
}
void add(int o, int l, int r) {
}
}

namespace Solve {
void main() {
  for (int i = 1; i <= n; i++) if (S[i] == '(') M1[p[i]].push_back();
  for (int i = 1; i <= n; i++) {
    
  }
}
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
