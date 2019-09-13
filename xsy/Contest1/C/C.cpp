#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define LL long long
#define go(x, i, v) for (int i = hd[x], v = to[i]; i; v = to[i = nx[i]])
#define inline __inline__ __attribute__((always_inline))
inline LL read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 25, M = 26;
int n, m, w, p;
int nx[12], ch[Max_n][M];
double f[Max_n][11][51], g[Max_n * 12][Max_n * 12], ans[Max_n * 12];
char S[12], T[52];
inline void Init() {
  n = read(), m = read();
  int u, v;
  char c;
  for (int i = 1; i <= m; i++) {
    u = read(), v = read(), scanf(" %c", &c);
    ch[u][c - 'a'] = v;
  }
  scanf(" %s", S + 1), scanf(" %s", T);
  w = strlen(S + 1), p = strlen(T + 1);
  for (int i = 2; i <= w; i++) {
    nx[i] = S[i] == S[1] ? 1 : 0;
    for (int j = nx[i - 1]; j; j = nx[j])
      if (S[j + 1] == S[i]) {
        nx[i] = j + 1;
        break;
      }
  }
}
inline void Solve() {
  for (int k = p; k; i--) {
    
  }
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("C.in", "r", stdin);
  freopen("C.out", "w", stdout);
#endif
  Init();
  Solve();
}
