#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define LL long long
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])
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

const int Max_n = 5e5 + 5, M = 26;
int n, K, t;
char S[Max_n];

namespace SAM {
int cnt = 1, las = 1;
struct node {
  int fa, len, to[M];
  int nu;
  LL sum;
};
node k[Max_n << 1];
void add(int c) {
  int p = las, np = las = ++cnt;
  k[np].len = k[p].len + 1, k[np].nu = 1;
  for (; p && !k[p].to[c]; p = k[p].fa) k[p].to[c] = np;
  if (!p) {
    k[np].fa = 1;
  } else {
    int q = k[p].to[c];
    if (k[q].len == k[p].len + 1) {
      k[np].fa = q;
    } else {
      int nq = ++cnt;
      k[nq] = k[q], k[nq].nu = k[nq].sum = 0, k[nq].len = k[p].len + 1;
      k[np].fa = k[q].fa = nq;
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
  for (int i = cnt; i > 1; i--) {
    int x = stk[i];
    if (!t) k[x].nu = 1;
    k[k[x].fa].nu += (k[x].sum = k[x].nu);
    for (int j = 0; j < M; j++) k[x].sum += k[k[x].to[j]].sum;
  }
  for (int j = 0; j < M; j++) k[1].sum += k[k[1].to[j]].sum;
  k[0].sum = 0;
}
void Print(int x) {
  if (!K) return;
  for (int i = 0; i < M; i++) {
    int v = k[x].to[i];
    if (v)
      if (k[v].sum < K)
        K -= k[v].sum;
      else {
        printf("%c", (char)(i + 'a')), K -= k[v].nu, Print(v);
        break;
      }
  }
}
}  // namespace SAM

namespace Input {
void main() {
  scanf("%s", S + 1);
  t = read(), K = read();
}
}  // namespace Input

namespace Init {
void main() {
  n = strlen(S + 1);
  for (int i = 1; i <= n; i++) SAM::add(S[i] - 'a');
  SAM::Count();
}
}  // namespace Init

namespace Solve {
void main() {
  if (SAM::k[1].sum - 1 < K) {
    puts("-1");
    return;
  }
  SAM::Print(1);
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("3975.in", "r", stdin);
  freopen("3975.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
