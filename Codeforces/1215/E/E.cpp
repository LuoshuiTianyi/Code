#include <cstdio>
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
const int Max_n = 4e5 + 5;
int n;
int a[Max_n], num[21];
LL g[21][Max_n], f[1 << 20], len[1 << 20];
int main() {
#ifndef ONLINE_JUDGE
  freopen("", "r", stdin);
  freopen("", "w", stdout);
#endif
  n = read();
  for (int i = 1; i <= n; i++) g[a[i] = read()][0] += a[i], num[a[i]]++;
  for (int j = 1; j <= 20; j++) {
    int sl = 0, sr = 0;
    for (int i = 1; i <= n; i++)
      if (a[i] == j) sr++;
    for (int i = 1; i <= n; i++) {
      g[j][i] = g[j][i - 1] + sl - sr;
      if (a[i] == j) sl++, sr--;
    }
  }
  for (int s = 0; s < (1 << 20); s++) {
  }
}
