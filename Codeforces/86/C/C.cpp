#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
long long read() {
  long long x = 0, w = 1;
  char ch = getchar();
  while (!isdigit(ch)) w = ch == '-' ? -1 : 1, ch = getchar();
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * w;
}
const int Max_n = 1005, M = 4, mod = 1e9 + 9;
int n, m;
int a[Max_n];
char s[Max_n];
int f[Max_n][Max_n][11];
namespace Trie {
int cntT, ch[Max_n][M], sur[Max_n], len[Max_n];
void add(int Len) {
  int x = 0;
  for (int i = 0; i < Len; i++) {
    if (!ch[x][a[i]]) ch[x][a[i]] = ++cntT;
    x = ch[x][a[i]];
  }
  len[x] = max(len[x], Len);
}
void build() {
  queue<int> q;
  for (int i = 0; i < M; i++)
    if (ch[0][i]) q.push(ch[0][i]);
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    len[x] = max(len[x], len[sur[x]]);
    for (int i = 0; i < M; i++)
      if (ch[x][i])
        sur[ch[x][i]] = ch[sur[x]][i], q.push(ch[x][i]);
      else
        ch[x][i] = ch[sur[x]][i];
  }
}
}  // namespace Trie
using namespace Trie;
void Mod(int &x) { x %= mod; }
int DP(int L, int x, int left) {
  int &res = f[L][x][left];
  if (left > 10) return 0;
  if (res != -1) return res;
  if (!L)
    if (!left)
      return 1;
    else
      return 0;
  res = 0;
  for (int i = 0; i < M; i++) {
    int p = ch[x][i];
    if (len[p] >= left + 1)
      Mod(res += DP(L - 1, p, 0));
    else
      Mod(res += DP(L - 1, p, left + 1));
  }
  return res;
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("C.in", "r", stdin);
  freopen("C.out", "w", stdout);
#endif
  n = read(), m = read();
  while (m--) {
    scanf("%s", s);
    for (int i = 0, lim = strlen(s); i < lim; i++)
      if (s[i] == '2')
        a[i] = 0;
      else if (s[i] == '0')
        a[i] = 1;
      else if (s[i] == '1')
        a[i] = 2;
      else
        a[i] = 3;
    add(strlen(s));
  }
  build();
  memset(f, -1, sizeof(f));
  cout << DP(n, 0, 0);
}
