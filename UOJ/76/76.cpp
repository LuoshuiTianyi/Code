#include <bits/stdc++.h>
using namespace std;
long long read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = (x << 3) + (x << 1) + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 3005, mod = 998244353;
int n, Res, ans1, ans2;
int cntt, dfn[Max_n], low[Max_n], bel[Max_n], num[Max_n];
int cntp, in[Max_n], top[Max_n];
char P[Max_n][Max_n];
bool bk[Max_n], ins[Max_n];
vector<int> r[Max_n];
bitset<Max_n> s[Max_n];
stack<int> stk;
queue<int> q;
void dfs(int x) {
  dfn[x] = low[x] = ++cntt;
  stk.push(x), ins[x] = 1;
  for (auto to : r[x]) {
    if (!dfn[to])
      dfs(to), low[x] = min(low[x], low[to]);
    else if (ins[to])
      low[x] = min(low[x], dfn[to]);
  }
  if (dfn[x] == low[x]) {
    bel[x] = x;
    while (stk.top() != x) bel[stk.top()] = x, ins[stk.top()] = 0, stk.pop();
    ins[stk.top()] = 0, stk.pop();
  }
}
void del(int x) {
  for (int i = 1; i <= n; i++)
    if (x != i && bk[i] && P[i][x] == '0')
      bk[i] = 0, del(i);
}
int ksm(int a, int b) {
  int res = 1;
  for (; b; b >>= 1, a = 1ll * a * a % mod)
    if (b & 1) res = 1ll * res * a % mod;
  return res;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("76.in", "r", stdin);
  freopen("76.out", "w", stdout);
#endif
  Res = n = read();
  for (int i = 1; i <= n; i++) {
    scanf("%s", P[i] + 1), s[i].set(i), bk[i] = 1;
    for (int j = 1; j <= n; j++)
      if (P[i][j] == '0' && i != j)
        r[i].push_back(j);
  }
  for (int i = 1; i <= n; i++)
    if (!dfn[i]) dfs(i);
  for (int i = 1; i <= n; i++) num[bel[i]]++;
  for (int i = 1; i <= n; i++)
    if (num[bel[i]] > 1) bk[i] = 0;
  for (int i = 1; i <= n; i++)
    if (!bk[i]) del(i);
  for (int i = 1; i <= n; i++) Res -= !bk[i];
  for (int i = 1; i <= n; i++)
    if (bk[i])
      for (auto to : r[i]) in[to]++;
  for (int i = 1; i <= n; i++)
    if (!in[i] && bk[i]) q.push(i);
  while (!q.empty()) {
    top[++cntp] = q.front();
    for (auto to : r[q.front()])
      if (bk[to] && !(--in[to])) q.push(to);
    q.pop();
  }
  for (int i = 1; i <= cntp; i++) {
    int x = top[i];
    for (auto to : r[x])
      if (bk[to]) s[to] |= s[x];
  }
  for (int i = 1; i <= cntp; i++) {
    int x = top[i];
    int tot = s[x].count();
    ans1 = (ans1 + 1ll * (ksm(2, tot) - 1) * ksm(2, Res - tot) % mod) % mod;
    ans2 = (ans2 + ksm(2, Res - tot)) % mod;
  }
  cout << ans1 << " " << ans2 << endl;
}
