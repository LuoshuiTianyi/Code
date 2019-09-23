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
bool bk[21][21];
int p = 10;
int cnt, nx[10001], ny[10001];
int main() {
#ifndef ONLINE_JUDGE
  freopen("B.in", "w", stdout);
#endif
  srand(time(NULL)); 
  bk[p][p] = 1;
  for (int i = 1; i <= 1; i++) {
    int x = rand() % 5 + 5, y = rand() % 5 + 5;
    bk[x][y] ^= 1, bk[x][y - 1] ^= 1, bk[x + 1][y - 1] ^= 1;
  }
  for (int i = 0; i <= 20; i++)
    for (int j = 0; j <= 20; j++)
      if (bk[i][j])
       cnt++, nx[cnt] = i - p, ny[cnt] = j - p;
  cout << cnt << endl;
  for (int i = 1; i <= cnt; i++)
    cout << nx[i] << " " << ny[i] << endl;
}
