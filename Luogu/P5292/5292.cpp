#include <cstdio>
#include <iostream>
using namespace std;
int n, m, Q;
int cntr, head[5001], nx[1000001], to[1000001], col[5001];
int cr, hd[5001], Nx[1000001], To[1000001];
int h, t, u[25000001], v[25000001];
bool flag, f[5001][5001];
char S[5001];
void read(int &x) {
  x = 0;
  char ch = getchar();
  while (!isdigit(ch))
    ch = getchar();
  while (isdigit(ch))
    x = x * 10 + ch - '0', ch = getchar();
}
void addr(int u, int v) {
  cntr++;
  nx[cntr] = head[u], to[cntr] = v;
  head[u] = cntr;
}
void Addr(int u, int v) {
  cr++;
  Nx[cr] = hd[u], To[cr] = v;
  hd[u] = cr;
}
void Add(int U, int V) {
  t++;
  u[t] = U, v[t] = V;
}
void dye(int x, bool type) {
  for (int i = head[x]; i; i = nx[i]) {
    int p = to[i];
    if ((S[p] == S[x]) == type) {
      if (col[p] != -1)
        if (!(col[p] ^ col[x]))
          flag = 1;
      if (col[p] == -1) {
        col[p] = col[x] ^ 1, dye(p, type);
        Addr(x, p), Addr(p, x);
      }
    }
  }
}
void Read_Init() {
  read(n), read(m), read(Q);
  scanf("%s", S + 1);
  int u, v;
  while (m--) {
    read(u), read(v);
    if (S[u] == S[v])
      f[u][v] = f[v][u] = 1, Add(u, v);
    addr(u, v), addr(v, u);
  }
}
void Build_Init() {
  for (int i = 1; i <= n; i++)
    f[i][i] = 1, Add(i, i);
  for (int k = 0; k < 2; k++) {
    for (int i = 1; i <= n; i++)
      col[i] = -1;
    for (int i = 1; i <= n; i++)
      if (col[i] == -1) {
        flag = 0;
        col[i] = 0, dye(i, k);
        if (flag)
          Addr(i, i);
      }
  }
}
void DP() {
  while (h < t) {
    h++;
    for (int i = hd[u[h]]; i; i = Nx[i])
      for (int j = hd[v[h]]; j; j = Nx[j])
        if (S[To[i]] == S[To[j]] && !f[To[i]][To[j]])
          f[To[i]][To[j]] = f[To[j]][To[i]] = 1, Add(To[i], To[j]);
  }
}
void Answer() {
  int u, v;
  while (Q--) {
    read(u), read(v);
    if (f[u][v])
      printf("YES\n");
    else
      printf("NO\n");
  }
}
int main() {
  freopen("5292.in", "r", stdin);
  freopen("5292.out", "w", stdout);
  Read_Init();
  Build_Init();
  DP();
  Answer();
}
