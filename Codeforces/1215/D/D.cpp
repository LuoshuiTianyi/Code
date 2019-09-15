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
int n, s1, s2, d;
char s[Max_n];
bool check() {
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("D.in", "r", stdin);
  freopen("D.out", "w", stdout);
#endif
  n = read();
  scanf("%s", s + 1);
  for (int i = 1; i <= (n >> 1); i++)
    if (s[i] != '?')
      d += s[i] - '0';
    else
      s1++;
  for (int i = (n >> 1) + 1; i <= n; i++)
    if (s[i] != '?')
      d -= s[i] - '0';
    else
      s2++;
  if (check()) {
    cout << "Monocarp";
    return 0;
  }
  swap(s1, s2), d = -d;
  if (check()) {
    cout << "Monocarp";
    return 0;
  }
  cout << "Bicarp";
}
