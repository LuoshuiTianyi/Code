#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
const int M = 26;
int n, cnt, len, ans, ch[1000001][26], sur[1000001], End[1000001];
char s[1000001];
queue<int> q;
void build() {
  for (int i = 0; i < M; i++)
    if (ch[0][i])
      q.push(ch[0][i]);
  while (!q.empty()) {
    int x = q.front();
    q.pop();
    for (int i = 0; i < M; i++)
      if (ch[x][i])
        sur[ch[x][i]] = ch[sur[x]][i], q.push(ch[x][i]);
      else
        ch[x][i] = ch[sur[x]][i];
  }
}
int main() {
  freopen("3808.in", "r", stdin);
  freopen("3808.out", "w", stdout);
  cin >> n;
  while (n--) {
    scanf("%s", s);
    len = strlen(s);
    for (int now = 0, x = 0; now < len; now++) {
      int To = s[now] - 'a';
      if (!ch[x][To])
        ch[x][To] = ++cnt;
      x = ch[x][To];
      if (now == len - 1)
        End[x]++;
    }
  }
  build();
  scanf("%s", s);
  len = strlen(s);
  for (int i = 0, x = 0; i < len; i++) {
    x = ch[x][s[i] - 'a'];
    for (int j = x; j && End[j] != -1; j = sur[j])
      ans += End[j], End[j] = -1;
  }
  cout << ans;
}
