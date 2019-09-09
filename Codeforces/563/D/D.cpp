#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
int n, m, head[100001], nx[200001], to[200001], a[100001], top;
bool book[100001];
void add(int u, int v, int d) {
  to[d] = v, nx[d] = head[u];
  head[u] = d;
}
priority_queue<int, vector<int>, greater<int>> q;
void Bfs() {
  q.push(1);
  book[1] = true;
  while (!q.empty()) {
    int x = q.top();
    q.pop();
    a[++top] = x;
    for (int i = head[x]; i; i = nx[i])
      if (!book[to[i]]) {
        book[to[i]] = true;
        q.push(to[i]);
      }
  }
}
int main() {
  freopen("D.in", "r", stdin);
  freopen("D.out", "w", stdout);
  cin >> n >> m;
  int u, v;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &u, &v);
    add(u, v, i), add(v, u, i + m);
  }
  Bfs();
  for (int i = 1; i <= top; i++)
    printf("%d ", a[i]);
}
