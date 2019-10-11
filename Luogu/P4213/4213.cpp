#include <cstdio>
#include <iostream>
#include <map>
using namespace std;
#define LL long long
#define go(x, i, v) for (int i = hd[x], v = to[i]; i; v = to[i = nx[i]])
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
const int Max_n = 5e6 + 5;
int T;
int n;
int cnt, pri[Max_n], mu[Max_n], phi[Max_n];
LL sumu[Max_n], suph[Max_n];
bool vis[Max_n];
inline void init() {
  vis[1] = mu[1] = phi[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!vis[i]) pri[++cnt] = i, phi[i] = i - 1, mu[i] = -1;
    for (int j = 1; j <= cnt && pri[j] * i <= n; j++) {
      vis[i * pri[j]] = 1, mu[i * pri[j]] = -mu[i];
      phi[i * pri[j]] = phi[i] * phi[pri[j]];
      if (i % pri[j] == 0) {
        phi[i * pri[j]] = phi[i] * pri[j], mu[i * pri[j]] = 0;
        break;
      }
    }
  }
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("4213.in", "r", stdin);
  freopen("4213.out", "w", stdout);
#endif
  T = read();
  while (T--) {
    n = read();
    
  }
}
