#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
int n, m, l[200002], r[200002], a, b, f[200001], q[200001], head = 1, tail = 1,
                                                            pos = 1;
void Min(int &a, int b) { a = a > b ? b : a; }
void Max(int &a, int b) { a = a < b ? b : a; }
int main() {
  freopen("3084.in", "r", stdin);
  freopen("3084.out", "w", stdout);
  cin >> n >> m;
  for (int i = 1; i <= n + 1; i++)
    r[i] = i - 1;
  for (int i = 1; i <= m; i++) {
    scanf("%d%d", &a, &b);
    Min(r[b], a - 1);
    Max(l[b + 1], a);
  }
  for (int i = n; i >= 1; i--)
    Min(r[i], r[i + 1]);
  for (int i = 2; i <= n + 1; i++)
    Max(l[i], l[i - 1]);
  for (int i = 1; i <= n + 1; i++) {
    while (pos <= r[i] && pos <= n) {
      if (f[pos] != -1) {
        while (f[pos] > f[q[tail]] && head <= tail)
          tail--;
        q[++tail] = pos;
      }
      pos++;
    }
    while (q[head] < l[i] && head <= tail)
      head++;
    f[i] = -1;
    if (head <= tail) {
      f[i] = f[q[head]] + 1;
    }
  }
  if (f[n + 1] == -1)
    cout << f[n + 1];
  else
    cout << f[n + 1] - 1;
}
