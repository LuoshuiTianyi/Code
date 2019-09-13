#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n, m, ls, lt, ch[1010][30], fa[1010];
int id[30][15], id2[30][15], du[30];
char s[1010], t[1010];
double f[230][230], tmp[230];
bool vis[30][15][60];
void kmp() {
  fa[1] = 0;
  for (int i = 2; i <= ls; i++) {
    int p = fa[i - 1];
    while (p && s[p + 1] != s[i]) p = fa[p];
    if (s[p + 1] == s[i]) fa[i] = p + 1;
  }
}
void gauss(int n) {
  for (int i = 0; i < n; i++) {
    int k = i;
    for (int j = i; j < n; j++)
      if (fabs(f[j][i]) > fabs(f[k][i])) k = j;
    if (k != i)
      for (int j = i; j <= n; j++) swap(f[i][j], f[k][j]);
    if (fabs(f[i][i]) < 1e-6) {
      puts("-1");
      exit(0);
    }
    for (int j = i + 1; j < n; j++) {
      long double del = (long double)f[j][i] / f[i][i];
      f[j][i] = 0;
      for (k = i + 1; k <= n; k++) f[j][k] -= f[i][k] * del;
    }
  }
  for (int i = n - 1; ~i; i--) {
    for (int j = n; j > i; j--) f[i][n] -= f[i][j] * f[j][n];
    f[i][n] /= f[i][i];
  }
}
void dfs(int x, int a, int b) {
  vis[x][a][b] = 1;
  if (a == ls || b == lt) return;
  for (int i = 0; i < 26; i++)
    if (ch[x][i]) {
      int la = a, lb = b;
      char c = i + 'a';
      while (la && s[la + 1] != c) la = fa[la];
      if (s[la + 1] == c) la++;
      lb += (c == t[lb + 1]);
      if (!vis[ch[x][i]][la][lb]) dfs(ch[x][i], la, lb);
    }
}

int main() {
  freopen("C.in", "r", stdin);
  freopen("C.ans", "w", stdout);
  scanf("%d%d", &n, &m);
  for (int i = 1, x, y; i <= m; i++)
    scanf("%d%d%s", &x, &y, s), ch[x][s[0] - 'a'] = y, du[x]++;
  scanf("%s%s", s + 1, t + 1);
  ls = strlen(s + 1);
  lt = strlen(t + 1);
  // check();
  kmp();
  dfs(1, 0, 0);
  for (int i = lt - 1; ~i; i--) {
    int sz = 0;
    for (int j = 1; j <= n; j++)
      for (int k = 0; k < ls; k++)
        if (vis[j][k][i]) id[j][k] = sz++;
    cout << sz << endl;
    for (int j = 1; j <= n; j++)
      for (int k = 0; k < ls; k++)
        if (vis[j][k][i]) {
          int x = id[j][k];
          f[x][x] = du[j];
          f[x][sz] = du[j];
          for (int l = 0; l < 26; l++)
            if (ch[j][l]) {
              int v = ch[j][l], l2 = k;
              char c = l + 'a';
              while (l2 && s[l2 + 1] != c) l2 = fa[l2];
              if (s[l2 + 1] == c) l2++;
              if (l2 == ls) continue;
              if (c == t[i + 1])
                f[x][sz] += tmp[id2[v][l2]];
              else
                f[x][id[v][l2]]--;
            }
        }
    gauss(sz);
    memcpy(id2, id, sizeof(id));
    for (int j = 0; j < sz; j++) tmp[j] = f[j][sz];
    memset(f, 0, sizeof(f));
  }
  printf("%.6lf\n", tmp[0]);
  return 0;
}
