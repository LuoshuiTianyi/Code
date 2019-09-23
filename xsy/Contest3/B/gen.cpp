#include <cstdio>
#include <ctime>
#include <iostream>
#include <queue>
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
struct node {
  int x, y;
};
queue<node> q;
bool bk[1001][1001];
int main() {
#ifndef ONLINE_JUDGE
  freopen("B.in", "w", stdout);
#endif
  srand(time(NULL)); 
  bk[0][0] = 1;
}
