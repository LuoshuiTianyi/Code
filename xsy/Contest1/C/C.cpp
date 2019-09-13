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
int out[Max_n], id[2][Max_n][12];
double f[Max_n][12][51], g[Max_n * 12][Max_n * 12], ans[Max_n * 12];
bool vis[Max_n][12][51], inf[Max_n * 12];
char S[12], T[52];
inline int get_to(int now, char c) {
  for (int i = now; ; i = nx[i]) {
    if (S[i + 1] == c)
      return i + 1;
    if (!i) return 0;
  }
}
void dfs(int x, int ls, int lt) {
  if (vis[x][ls][lt]) return;
  vis[x][ls][lt] = 1;
  if (ls == w || lt == p) return;
  for (int i = 0; i < M; i++)
    if (ch[x][i]) {
      char c = i + 'a';
      int to = get_to(ls, c);
      dfs(ch[x][i], to, lt + c == T[lt + 1]);
    }
}
inline void Init() {
  n = read(), m = read();
  int u, v;
  char c;
  for (int i = 1; i <= m; i++) {
    u = read(), v = read(), scanf(" %c", &c);
    out[u]++, ch[u][c - 'a'] = v;
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
  dfs(1, 0, 0);
}
inline void Solve() {
  for (int k = p; k; k--) {
    int cnt = 0, no = k & 1, ol = (k + 1) & 1;
    for (int i = 1; i <= n; i++)
      for (int j = 0; j < w; j++) 
        if (vis[i][j][k]) id[no][i][j] = cnt++;
    for (int i = 1 ; i <= n; i++)
      for (int j = 0; j < w; j++)
        if (vis[i][j][k]) {
          int x = id[no][i][j];
          g[x][x] = 1, g[x][cnt] = 1;
          for (int t = 0; t < M; t++)
            if (ch[i][t]) {
              char c = i + 'a';
              int to = get_to(j, c);
            }
        }
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
