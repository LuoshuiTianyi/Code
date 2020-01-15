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

const int Max_n = 55;
const double eps = 1e-8;
int n;
double ans, b[Max_n][Max_n];

namespace Input {
void main() {
  n = read();
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      scanf("%lf", &b[i][j]);
      ans *= (1.0 - b[i][j]);
      if (b[i][j] > 1 - eps) b[i][j] = 1 - eps;
      b[i][j] = -(b[i][j] / (1.0 - b[i][j]));
      if (i == j) b[i][j] += 1.0;
    }
}
}  // namespace Input

namespace Solve {
double Guess(int n) {
  double ans = 1;
  for (int i = 1; i <= n; i++) {
    int mx = i;
    for (int j = i + 1; j <= n; j++)
      if (b[j][i] > b[mx][i]) mx = j;
    if (mx != i) swap(b[i], b[mx]), ans = -ans;
    if (b[i][i] < eps || b[i][i] > 1 - eps) return 0;
    for (int j = i + 1; j <= n; j++) {
      double d = b[j][i] / b[i][i];
    }
  }
}
void main() {
  ans *= Guess(n - 1);
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("3317.in", "r", stdin);
  freopen("3317.out", "w", stdout);
#endif
  Input::main();
  Solve::main();
}
