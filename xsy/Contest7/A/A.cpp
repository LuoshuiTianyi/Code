#include <cmath>
#include <cstdio>
#include <iostream>
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

const int Max_n = 1e7 + 5;
LL n;
int cnt, pri[Max_n], phi[Max_n];
bool vis[Max_n];

namespace Input {
void main() {
  fread(s, 1, 1 << 25, stdin);
  read(n);
}
}  // namespace Input

namespace Init {
void main() {
  n = 1e7;
  int ans = 0;
  for (int i = 1; i <= n; i++) {
    //ans += !vis[(int)((int)sqrt(n) / (int)sqrt(i))];
    //vis[(int)sqrt(n / i)] = 1;
  }
  cout << ans;
  //phi[1] = 1;
  //for (int i = 2; i <= 1e7; i++) {
  //  if (!vis[i]) pri[++cnt] = i, phi[i] = i - 1;
  //  for (int j = 1; j <= cnt && pri[j] * i <= 1e7; j++) {
  //    vis[i * pri[j]] = 1;
  //    phi[i * pri[j]] = phi[i] * (pri[j] - 1);
  //    if (i % pri[j] == 0) {
  //      phi[i * pri[j]] = phi[i] * pri[j];
  //      break;
  //    }
  //  }
  //}
}
}  // namespace Init

namespace Solve {
void main() {}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("A.in", "r", stdin);
  freopen("A.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
