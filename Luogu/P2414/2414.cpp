#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
void read(int &x) {
  x = 0;
  char ch = getchar();
  while (!isdigit(ch)) ch = getchar();
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
}
const int Max_n = 1e5 + 1, Max_m = 1e5 + 1, Max_len = 1e5 + 1, M = 26;
int n, m, Ans[Max_n];
int top, pos, cnt_T, End[Max_n];
char S[Max_len], now_S[Max_len];
vector<int> que_d[Max_len], que_x[Max_len];
queue<int> q;
void Trie_add(int x);
struct Trie {
  int sur, ch[M], fa, deep, End;
  int nx(int x, int now) {
    if (!ch[x]) {
      ch[x] = ++cnt_T;
      Trie_add(now);
    }
    return ch[x];
  }
} k[Max_len], tp[Max_len];
void Trie_add(int x) { k[cnt_T].fa = x, k[cnt_T].deep = k[x].deep + 1; }
void Trie_build() {
  for (int i = 0; i < M; i++)
    if (k[0].ch[i]) q.push(k[0].ch[i]);
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    for (int i = 0; i < M; i++)
      if (k[x].ch[i])
        k[k[x].ch[i]].sur = k[k[x].sur].ch[i], q.push(k[x].ch[i]);
      else
        k[x].ch[i] = k[k[x].sur].ch[i];
  }
}
int cntr, head[Max_len], nx[Max_len], to[Max_len];
int cntd, d[Max_len], size[Max_len];
int cnts, s[Max_len << 1];
int c[Max_len];
bool vis[Max_len];
void get_s(int x) {
  s[++cnts] = x;
  for (int i = 0; i < M; i++)
    if (k[x].ch[i]) get_s(k[x].ch[i]);
  s[++cnts] = x;
}
void addr(int u, int v) {
  cntr++;
  to[cntr] = v, nx[cntr] = head[u];
  head[u] = cntr;
}
void Tree_build(int x) {
  size[x] = 1, d[x] = ++cntd;
  for (int i = head[x]; i; i = nx[i]) Tree_build(to[i]), size[x] += size[to[i]];
}
void c_add(int k, int x) {
  if (!k) return;
  for (int i = k; i <= cnt_T + 1; i += i & -i) c[i] += x;
}
int c_query(int k) {
  int ans = 0;
  for (int i = k; i; i -= i & -i) ans += c[i];
  return ans;
}
void Ans_Count(int x) {
  for (int i = 1; i <= cnts; i++) {
    int x = s[i];
    if (!vis[x]) {
      vis[x] = 1, c_add(d[x], 1);
      for (int j = que_d[x].size() - 1; ~j; j--) {
        int now = que_x[x][j];
        Ans[que_d[x][j]] =
            c_query(d[now] + size[now] - 1) - c_query(d[now] - 1);
      }
    } else
      c_add(d[x], -1);
  }
}
int main() {
  freopen("2414.in", "r", stdin);
  freopen("2414.out", "w", stdout);
  scanf("%s", S);
  for (int i = 0, lim = strlen(S); i < lim; i++) {
    if (S[i] == 'B')
      top--, pos = k[pos].fa;
    else if (S[i] == 'P') {
      for (int p = k[pos].deep + 1; p <= top; p++)
        pos = k[pos].nx(now_S[p] - 'a', pos);
      k[pos].End = ++n;
      End[n] = pos;
    } else
      now_S[++top] = S[i];
  }
  get_s(0);
  Trie_build();
  read(m);
  int x, y;
  for (int i = 1; i <= m; i++) {
    read(x), read(y);
    que_d[End[y]].push_back(i);
    que_x[End[y]].push_back(End[x]);
  }
  for (int i = 1; i <= cnt_T; i++) addr(k[i].sur, i);
  Tree_build(0);
  Ans_Count(0);
  for (int i = 1; i <= m; i++) printf("%d\n", Ans[i]);
}
