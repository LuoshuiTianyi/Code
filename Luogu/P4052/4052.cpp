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
const int M = 26, Max_n = 65, Max_len = 105, mod = 10007;
void Mod(int &x) { x %= mod; }
int n, m, ans = 1;
int cntT, f[Max_n * Max_len][Max_len];
struct Trie {
  int sur, ch[M];
  bool book;
} k[Max_n * Max_len];
char s[Max_len];
queue<int> q;
void Trie_build() {
  for (int i = 0; i < M; i++)
    if (k[0].ch[i]) q.push(k[0].ch[i]);
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    k[x].book |= k[k[x].sur].book;
    for (int i = 0; i < M; i++) {
      int &p = k[x].ch[i];
      if (p)
        k[p].sur = k[k[x].sur].ch[i], q.push(p);
      else
        p = k[k[x].sur].ch[i];
    }
  }
}
void DP() {
  for (int len = 1; len <= m; len++)
    for (int i = 0; i <= cntT; i++)
      for (int j = 0; j < M; j++) {
        int p = k[i].ch[j];
        if (!k[p].book) Mod(f[p][len] += f[i][len - 1]);
      }
}
int main() {
#ifndef ONLINE_JUDGE
  freopen("4052.in", "r", stdin);
  freopen("4052.out", "w", stdout);
#endif
  n = read(), m = read();
  while (n--) {
    scanf("%s", s);
    int len = strlen(s), x = 0;
    for (int i = 0; i < len; i++) {
      int now = s[i] - 'A';
      if (!k[x].ch[now]) k[x].ch[now] = ++cntT;
      x = k[x].ch[now];
    }
    k[x].book = 1;
  }
  Trie_build();
  f[0][0] = 1;
  DP();
  for (int i = 1; i <= m; i++) ans = ans * 26 % mod;
  for (int i = 0; i <= cntT; i++) Mod(ans -= (f[i][m] - mod));
  cout << ans;
}
