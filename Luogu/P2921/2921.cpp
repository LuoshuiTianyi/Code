#include <cstdio>
#include <iostream>
using namespace std;
int n, to[100001], book[100001], cnt, stack[100001], top, ans[100001];
bool yn[100001];
void dfs(int x) {
  stack[++top] = x;
  if (book[to[x]] == book[x]) {
    while (stack[top] != to[x])
      yn[stack[top--]] = true;
    yn[stack[top--]] = true;
  }
  if (!book[to[x]]) {
    book[to[x]] = book[x];
    dfs(to[x]);
  }
}
int count(int x, int start) {
  book[x] = 1;
  cnt++;
  if (to[x] == start)
    return ans[x] = cnt;
  return ans[x] = count(to[x], start);
}
int solve(int x) {
  if (ans[x])
    return ans[x];
  return ans[x] = solve(to[x]) + 1;
}
int main() {
  freopen("2921.in", "r", stdin);
  freopen("2921.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++)
    scanf("%d", &to[i]);
  for (int i = 1; i <= n; i++)
    if (!book[i]) {
      book[i] = ++cnt;
      top = 0;
      dfs(i);
    }
  for (int i = 1; i <= n; i++)
    book[i] = 0;
  for (int i = 1; i <= n; i++)
    if (yn[i] && !book[i]) {
      cnt = 0;
      ans[i] = count(i, i);
    }
  for (int i = 1; i <= n; i++)
    solve(i), printf("%d\n", ans[i]);
}
