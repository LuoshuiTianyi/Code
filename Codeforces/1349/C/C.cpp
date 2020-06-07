#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
#define LL long long
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])

char read_str[1 << 25], *CH = read_str;
#define getchar() (*CH++)
LL read() {
  char ch = getchar();
  int fl = 0;
  LL x = 0;
  while (!isdigit(ch)) {
    if (ch == '-') fl = 1;
    ch = getchar();
  }
  while (isdigit(ch)) x = (x << 1) + (x << 3) + ch - '0', ch = getchar();
  return fl ? -x : x;
}
void rstr(char *s) {
  char *x = s;
  char ch = getchar();
  while (ch == ' ' || ch == '\n' || ch == '\r') ch = getchar();
  while (ch != ' ' && ch != '\n' && ch != '\r') {
    *x++ = ch;
    ch = getchar();
  }
}

const int Max_n = 1e3 + 5;
const int dx[5] = {0, 1, -1, 0, 0}, dy[5] = {0, 0, 0, 1, -1};
int n, m, Q;
int a[Max_n][Max_n], col[Max_n][Max_n];
int vis[Max_n][Max_n];

namespace Input {
void main() { 
  fread(read_str, 1, 1 << 25, stdin); 
  n = read(), m = read(), Q = read();
  char s[Max_n];
  for (int i = 1; i <= n; i++) {
    rstr(s + 1);
    for (int j = 1; j <= m; j++) a[i][j] = s[j] == '1';
  }
}
}  // namespace Input

namespace Init {
queue<pair<int, int> > q;
void main() {
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      vis[i][j] = -1;
      for (int k = 1; k <= 4; k++) {
        int x = i + dx[k], y = j + dy[k];
        if (x < 0 || y < 0 || x > n || y > m) continue;
        if (a[x][y] == a[i][j]) 
          vis[i][j] = 0, col[i][j] = a[i][j], q.push(make_pair(i, j));
      }
    }
  while (!q.empty()) {
    int x = q.front().first, y = q.front().second;
    q.pop();
    for (int k = 1; k <= 4; k++) {
      int xx = x + dx[k], yy = y + dy[k];
      if (xx < 0 || yy < 0 || xx > n || yy > m) continue;
      if (vis[xx][yy] == -1) 
        vis[xx][yy] = vis[x][y] + 1, col[xx][yy] = col[x][y], q.push(make_pair(xx, yy));
    }
  }
}
}  // namespace Init

namespace Solve {
void main() {
  while (Q--) {
    int x = read(), y = read();
    LL p = read();
    printf("%d\n", );
  }
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("C.in", "r", stdin);
  freopen("C.out", "w", stdout);
#endif
  Input::main();
  Init::main();
  Solve::main();
}
