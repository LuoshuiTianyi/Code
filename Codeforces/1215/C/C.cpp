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
const int Max_n = 2e5 + 5;
int n;
int s[Max_n], t[Max_n];
char S[Max_n], T[Max_n];
int main() {
#ifndef ONLINE_JUDGE
  freopen("C.in", "r", stdin);
  freopen("C.out", "w", stdout);
#endif
  n = read();
  scanf("%s", S + 1), scanf("%s", T + 1);
  for (int i = 1; i <= n; i++) s[i] = S[i] == 'a' ? 0 : 1;
  for (int i = 1; i <= n; i++) t[i] = T[i] == 'a' ? 0 : 1;
  for (int i = 1; i <= n; i++)
    if (s[i] ^ t[i])
}
