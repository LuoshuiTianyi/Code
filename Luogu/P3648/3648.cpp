#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n, K, head, tail, a[100001], que[100001], s[100001][201], Ans[100001], top;
long long q[100001], f[100001], g[100001];
long double work(int a, int b) {
  if (q[a] == q[b])
    return -1e18;
  return 1.0 * ((g[a] - q[a] * q[a]) - (g[b] - q[b] * q[b])) / (q[b] - q[a]);
}
int main() {
  freopen("3648.in", "r", stdin);
  freopen("3648.out", "w", stdout);
  cin >> n >> K;
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), q[i] = q[i - 1] + a[i];
  for (int j = 1; j <= K; j++) {
    head = 0, tail = 0;
    for (int i = 1; i <= n; i++) {
      while (head < tail && work(que[head], que[head + 1]) <= q[i])
        head++;
      int x = que[head];
      f[i] = g[x] + q[x] * (q[i] - q[x]);
      s[i][j] = x;
      while (head < tail && work(que[tail - 1], que[tail]) > work(que[tail], i))
        tail--;
      que[++tail] = i;
    }
    swap(f, g);
  }
  cout << g[n] << endl;
  for (int x = K, now = n; x; x--) {
    now = s[now][x];
    Ans[++top] = now;
  }
  while (top) {
    printf("%d ", Ans[top]);
    top--;
  }
}
