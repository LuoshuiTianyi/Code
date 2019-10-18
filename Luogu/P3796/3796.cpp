#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
void read(char *a) {
  int Cnt = 0;
  char ch = getchar();
  while (ch < 'a' || ch > 'z')
    ch = getchar();
  while (ch >= 'a' && ch <= 'z') {
    a[Cnt++] = ch;
    ch = getchar();
  }
}
struct Ans {
  int d, sum;
} ans[151];
struct S {
  char s[72];
} S[151];
int n, M = 26;
int cntc, ch[20001][26], End[20001], sur[20001];
int cntr, head[20001], nx[20001], to[20001], f[20001];
char T[1000002];
queue<int> q;
void addr(int u, int v) {
  cntr++;
  to[cntr] = v, nx[cntr] = head[u];
  head[u] = cntr;
}
void Build() {
  for (int i = 0; i < M; i++)
    if (ch[0][i])
      q.push(ch[0][i]);
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    if (x)
      addr(sur[x], x);
    for (int i = 0; i < M; i++) {
      if (ch[x][i])
        sur[ch[x][i]] = ch[sur[x]][i], q.push(ch[x][i]);
      else
        ch[x][i] = ch[sur[x]][i];
    }
  }
}
void Count(int x) {
  for (int i = head[x]; i; i = nx[i])
    Count(to[i]), f[x] += f[to[i]];
  ans[End[x]].sum += f[x];
}
bool cmp(Ans a, Ans b) { return a.sum == b.sum ? a.d > b.d : a.sum < b.sum; }
int main() {
  freopen("3796.in", "r", stdin);
  freopen("3796.out", "w", stdout);
  while (1) {
    cin >> n;
    if (!n)
      return 0;
    cntc = 0, cntr = 0;
    memset(ch, 0, sizeof(ch));
    for (int i = 1; i <= n; i++)
      ans[i].d = i, ans[i].sum = 0;
    for (int p = 1; p <= n; p++) {
      scanf("%s", S[p].s);
      int x = 0;
      for (int i = 0, lim = strlen(S[p].s); i < lim; i++) {
        int now = S[p].s[i] - 'a';
        if (ch[x][now])
          x = ch[x][now];
        else
          x = ch[x][now] = ++cntc;
      }
      End[x] = p;
    }
    Build();
    read(T);
    int x = 0;
    for (int p = 0, lim = strlen(T); p < lim; p++) {
      x = ch[x][T[p] - 'a'];
      f[x]++;
    }
    Count(0);
    sort(ans + 1, ans + n + 1, cmp);
    printf("%d\n%s\n", ans[n].sum, S[ans[n].d].s);
    for (int i = n - 1; i; i--)
      if (ans[i].sum == ans[i + 1].sum)
        printf("%s\n", S[ans[i].d].s);
      else
        break;
    for (int i = 0; i <= cntc; i++)
      End[i] = sur[i] = head[i] = f[i] = 0;
  }
}
