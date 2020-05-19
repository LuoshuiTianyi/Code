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

const int Max_n =  3e5 + 5;
int n, m;
int ql[Max_n], qr[Max_n];
int L[Max_n], R[Max_n];
char S[Max_n];
LL Ans[Max_n];
vector<int> M1[Max_n], M2[Max_n];

LL c1[Max_n], c2[Max_n], c3[Max_n];

namespace Input {
void main() { 
  fread(read_str, 1, 1 << 25, stdin); 
  read(n), read(m);
  scanf("%s", S + 1);
  for (int i = 1; i <= m; i++) read(ql[i]), read(qr[i]), M2[qr[i]].push_back(i);
}
}  // namespace Input

namespace Init {
int top, stk[Max_n], sum[Max_n];
void main() {
  for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + (S[i] == '(' ? 2 : -1);
  for (int i = 1; i <= n; i++) {
    while (top && sum[stk[top]] <= sum[i]) top--;
    L[i] = stk[top] + 1;
    stk[++top] = i;
  }
  for (int i = n; i >= 1; i--) sum[i] = sum[i + 1] + (S[i] == ')' ? 2 : -1);
  stk[top = 0] = n + 1;
  for (int i = n; i >= 1; i--) {
    while (top && sum[stk[top]] <= sum[i]) top--;
    R[i] = stk[top] - 1;
    stk[++top] = i;
  }
  for (int i = 1; i <= n; i++) cout << L[i] << " " << R[i] << endl;
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
