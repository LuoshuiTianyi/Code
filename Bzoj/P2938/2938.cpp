#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
int n, cnt = 0, ch[30002][2], sur[30002], vis1[30002];
char s[30002];
bool book[30002], vis[30002], ans;
queue<int> q;
void build() {
  for (int i = 0; i < 2; i++)
    if (ch[0][i])
      q.push(ch[0][i]);
  while (!q.empty()) {
    int x = q.front();
    book[x] |= book[sur[x]];
    q.pop();
    for (int i = 0; i < 2; i++) {
      if (ch[x][i])
        sur[ch[x][i]] = ch[sur[x]][i], q.push(ch[x][i]);
      else
        ch[x][i] = ch[sur[x]][i];
    }
  }
}
void dfs(int x) {
  if (ans)
    return;
  if (vis[x]) {
    ans = true;
    return;
  }
  vis[x] = true;
  vis1[x]++;
  for (int i = 0; i < 2; i++)
    if (!book[ch[x][i]] && vis1[x] <= 3)
      dfs(ch[x][i]);
  vis[x] = false;
}
int main() {
  freopen("2938.in", "r", stdin);
  freopen("2938.out", "w", stdout);
  cin >> n;
  while (n--) {
    scanf("%s", s + 1);
    int len = strlen(s + 1), now = 0;
    for (int i = 1; i <= len; i++) {
      int x = s[i] - '0';
      if (!ch[now][x])
        ch[now][x] = ++cnt;
      now = ch[now][x];
    }
    book[now] = 1;
  }
  build();
  dfs(0);
  if (ans)
    cout << "TAK";
  else
    cout << "NIE";
}
