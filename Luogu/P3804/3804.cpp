#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define LL long long
#define inline __inline__ __attribute__((always_inline))
inline LL read() {
  LL x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-') w = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}

const int Max_n = 2e6 + 5, M = 26;
int n;
LL ans;
char S[Max_n];

namespace SAM {
int cnt = 1, las = 1;
struct node {
  int fa, len, nu, to[M];
} k[Max_n];
inline void add(int c) {
  int p = las, np = las = ++cnt;
  k[np].nu = 1, k[np].len = k[p].len + 1;
  for (; !k[p].to[c]; p = k[p].fa) k[p].to[c] = np;
  if (!p) {
    k[np].fa = 1;
  } else {
    int q = k[p].to[c];
    if (k[q].len == k[p].len + 1) {
      k[np].fa = q;
    } else {
      int nq = ++cnt;
      k[nq] = k[q], k[nq].len = k[p].len + 1, k[nq].nu = 0;
      k[q].fa = k[np].fa = nq;
      for (; p && k[p].to[c] == q; p = k[p].fa) k[p].to[c] = nq;
    }
  }
}
int buk[Max_n];
int stk[Max_n];
void Sort() {
  for (int i = 1; i <= cnt; i++) buk[k[i].len]++;
  for (int i = 1; i <= n; i++) buk[i] += buk[i - 1];
  for (int i = 1; i <= cnt; i++) stk[buk[k[i].len]--] = i;
}
void Count() {
  Sort();
  for (int i = cnt; i; i--) {
    int x = stk[i];
    k[k[x].fa].nu += k[x].nu;
    if (k[x].nu > 1) ans = max(ans, 1ll * k[x].nu * k[x].len);
  }
}
}  // namespace SAM

namespace Input {
void main() { scanf("%s", S + 1); }
}  // namespace Input

namespace Init {
void main() {
  n = strlen(S + 1);
  for (int i = 1; i <= n; i++) SAM::add(S[i] - 'a');
}
}  // namespace Init

namespace Solve {
void main() {
  SAM::Count();
  cout << ans;
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("3804.in", "r", stdin);
  freopen("3804.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
