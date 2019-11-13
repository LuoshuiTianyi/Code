#include <algorithm>
#include <cmath>
#include <cstdio>
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

const int Max_n = 1e5 + 5;
int n, Q, X, S;
int h[Max_n], nu[Max_n];
int bef[Max_n], nxt[Max_n], bel[Max_n];
int to1[Max_n], to2[Max_n];

struct sth {
  int Min, sMin;
};
struct jump {
  int to[18], v[18];
} A[Max_n], B[Max_n];

void Max(sth &a, int b, int c) {
  int v = abs(h[b] - h[c]);
  if (v < abs(h[a.Min] - h[c]))
    a.sMin = a.Min, a.Min = b;
  else if (v < abs(h[a.sMin] - h[c]))
    a.sMin = b;
}

namespace Input {
void main() {
  n = read();
  for (int i = 1; i <= n; i++) h[i] = read(), nu[i] = i;
  X = read(), Q = read();
}
}  // namespace Input

namespace Init {
bool cmp(int a, int b) { return h[a] < h[b]; }
void main() {
  sort(nu + 1, nu + n + 1, cmp);
  for (int i = 1; i <= n; i++)
    bef[nu[i]] = nu[i - 1], nxt[nu[i]] = nu[i + 1];
  nxt[nu[n]] = n + 1;
  h[0] = h[n + 1] = -1e9;
  for (int i = 1; i <= n; i++) {
    sth S = (sth){0, 0};
    Max(S, bef[i], i), Max(S, bef[bef[i]], i);
    Max(S, nxt[i], i), Max(S, nxt[nxt[i]], i);
    cout << S.Min << " " << S.sMin << " " << nxt[nxt[i]] << endl;
    to1[i] = S.Min, to2[i] = S.sMin;
    bef[nxt[i]] = bef[i], nxt[bef[i]] = nxt[i];
  }
}
}  // namespace Init

namespace Solve {
void main() {}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("1081.in", "r", stdin);
  freopen("1081.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
