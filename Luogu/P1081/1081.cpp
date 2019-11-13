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
long double minn = 2e18;

struct sth {
  int Min, sMin;
};
struct jump {
  int to;
  LL A, B;
} f[Max_n][18];

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
  for (int i = 1; i <= n; i++) bef[nu[i]] = nu[i - 1], nxt[nu[i]] = nu[i + 1];
  h[0] = -1e9;
  for (int i = 1; i <= n; i++) {
    sth S = (sth){0, 0};
    Max(S, bef[i], i), Max(S, bef[bef[i]], i);
    Max(S, nxt[i], i), Max(S, nxt[nxt[i]], i);
    to1[i] = S.Min, to2[i] = S.sMin;
    bef[nxt[i]] = bef[i], nxt[bef[i]] = nxt[i], bef[0] = nxt[0] = 0;
  }
}
}  // namespace Init

namespace Solve {
pair<int, int> Jump(int start, int lim) {
  int p = start;
  LL A = 0, B = 0;
  for (int j = 17; ~j; j--)
    if (f[p][j].to && f[p][j].A + f[p][j].B <= lim) {
      lim -= f[p][j].A + f[p][j].B, p = f[p][j].to;
      A += f[p][j].A, B += f[p][j].B;
    }
  //cout << p << endl;
  if (to2[p] && abs(h[p] - h[to2[p]]) <= lim) A += abs(h[p] - h[to2[p]]);
  return make_pair(A, B);
}
pair<int, int> Ans;
void main() {
  for (int i = 1; i <= n; i++) {
    int a = to2[i], b = to1[a];
    f[i][0].to = b, f[i][0].A = abs(h[a] - h[i]), f[i][0].B = abs(h[b] - h[a]);
    cout << a << " " << b << endl;
  }
  for (int j = 1; j <= 17; j++)
    for (int i = 1; i <= n; i++) {
      int To = f[i][j - 1].to;
      f[i][j].to = f[To][j - 1].to;
      f[i][j].A = f[i][j - 1].A + f[To][j - 1].A;
      f[i][j].B = f[i][j - 1].B + f[To][j - 1].B;
    }
  int ans = n;
  for (int i = 1; i <= n; i++) {
    Ans = Jump(i, X);
    LL A = Ans.first, B = Ans.second;
    if (B)
      if ((long double)A / B < minn) minn = (long double)A / B, ans = i;
  }
  cout << ans << endl;
}
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
