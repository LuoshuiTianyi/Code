#include <cstdio>
#include <iostream>
using namespace std;
#define LL long long
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
int m;
int opt, n;
namespace Splay {
int cnt, rt;
struct node {
  int fa, val, s[2];
} k[Max_n];
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("3369.in", "r", stdin);
  freopen("3369.out", "w", stdout);
#endif
  m = read();
  while (m--) {
    opt = read(), n = read();
  }
}
