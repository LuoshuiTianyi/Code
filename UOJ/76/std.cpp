#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <bitset>
#include <cstring>
#include <stack>
#include <vector>
#define MAXN 3001
#define MAXM 9000005
using namespace std;
const int mod = 998244353;
int add(int a, int b) {
  a += b;
  a -= a < mod ? 0 : mod;
  return a;
}
void inc(int &a, int b) { a = add(a, b); }
int mul(int a, int b) { return 1ll * a * b % mod; }

int N, pw[MAXN], ptot, Ans1, Ans2;
char s[MAXN][MAXN];
bool In[MAXN];
int low[MAXN], dfn[MAXN], V[MAXN], vt;
stack<int> S;
bool del[MAXN];
int en[MAXM], nex[MAXM], las[MAXN], tot;
vector<int> G[MAXN];
int deg[MAXN];
bitset<MAXN> v[MAXN];

void link(int x, int y) {
  en[++tot] = y;
  nex[tot] = las[x];
  las[x] = tot;
}

void Tarjan(int x) {
  int i, y;
  dfn[x] = low[x] = ++vt;
  In[x] = true;
  S.push(x);
  for (i = las[x]; i; i = nex[i]) {
    y = en[i];
    if (!dfn[y]) {
      Tarjan(y);
      low[x] = min(low[x], low[y]);
    } else if (In[y])
      low[x] = min(dfn[y], low[x]);
  }
  if (low[x] != dfn[x]) return;
  int sz = 0;
  do {
    y = S.top();
    S.pop();
    In[y] = false;
    V[++sz] = y;
  } while (y != x);
  if (sz > 1)
    for (i = 1; i <= sz; i++) del[V[i]] = true, ptot--;
}

void dfs(int x) {
  for (int i = 1; i <= N; i++)
    if (x != i && !del[i] && s[i][x] == '0') {
      del[i] = true;
      ptot--;
      dfs(i);
    }
}

int main() {
  freopen("76.in", "r", stdin);
  freopen("76.ans", "w", stdout);
  int i, j, cnt, x, y;
  scanf("%d", &N);
  for (i = 1; i <= N; i++) scanf("%s", &s[i][1]);

  for (i = 1, pw[0] = 1; i <= N; i++) pw[i] = add(pw[i - 1], pw[i - 1]);
  for (i = 1; i <= N; i++)
    for (j = 1; j <= N; j++)
      if (s[i][j] == '0' && i != j) link(i, j);

  ptot = N;
  for (i = 1; i <= N; i++)
    if (!dfn[i]) Tarjan(i);
  for (i = 1; i <= N; i++)
    if (del[i]) dfs(i);

  for (i = 1; i <= N; i++)
    if (!del[i]) {
      for (j = 1; j <= N; j++) {
        if (del[j] || i == j || s[i][j] == '1') continue;
        deg[j]++;
        G[i].push_back(j);
      }
    }

  for (i = 1; i <= N; i++)
    if (!del[i] && !deg[i]) S.push(i);
  while (S.size()) {
    x = S.top();
    S.pop();
    v[x].set(x);
    for (auto y : G[x]) {
      v[y] |= v[x];
      deg[y]--;
      if (!deg[y]) S.push(y);
    }
    cnt = v[x].count();
    inc(Ans1, mul(pw[ptot - cnt], pw[cnt] + mod - 1));
    inc(Ans2, pw[ptot - cnt]);
  }
  printf("%d %d\n", Ans1, Ans2);
}
