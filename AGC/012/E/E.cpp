#include <bits/stdc++.h>
using namespace std;
#define LL long long
#define go(x, i, v) for (int i = hd[x], v = to[i]; i; v = to[i = nx[i]])
LL read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 2e5 + 5;
int n, v;
int a[Max_n];
int cntl, l[Max_n][18], r[Max_n][18];
int f[Max_n], g[Max_n], h[Max_n];
void Max(int &a, int b) { a = a < b ? b : a; }
void Min(int &a, int b) { a = a < b ? a : b; }
int main() {
#ifndef ONLINE_JUDGE
  freopen("E.in", "r", stdin);
  freopen("E.out", "w", stdout);
#endif
  n = read(), v = read();
  for (int i = 1; i <= n; i++) a[i] = read(), h[i] = n + 2;
  h[0] = h[n + 1] = n + 2;
  v <<= 1;
  do {
    cntl++, v >>= 1;
    l[1][cntl] = l[0][cntl] = 1;
    for (int i = 2; i <= n; i++) {
      l[i][cntl] = i;
      if (a[i] - a[i - 1] <= v)
        l[i][cntl] = l[i - 1][cntl];
    }
    r[n][cntl] = r[n + 1][cntl] = n;
    for (int i = n - 1; i; i--) {
      r[i][cntl] = i;
      if (a[i + 1] - a[i] <= v)
        r[i][cntl] = r[i + 1][cntl];
    }
  } while (v);
  for (int s = 0; s < (1 << cntl); s++) g[s] = n + 1;
  for (int s = 0; s < (1 << cntl); s++) {
    if (s & 1) continue;
    for (int i = 2; i <= cntl; i++)
      if (!((1 << i - 1) & s)) {
        Max(f[s | (1 << i - 1)], r[f[s] + 1][i]);
        Min(g[s | (1 << i - 1)], l[g[s] - 1][i]);
      }
  }
  for (int s = 0; s < (1 << cntl); s++) {
    if (s & 1) continue;
    Min(h[f[s]], g[(1 << cntl) - 2 - s]);
  }
  for (int i = 1; i <= n; i++)
    if (h[l[i][1] - 1] <= r[i][1] + 1)
      printf("Possible\n");
    else
      printf("Impossible\n");
}
