#include <cstdio>
#include <iostream>
using namespace std;
int n, head, tail, a[1000001], que[1000001];
long long A, B, C, f[1000001], sum[1000001];
double work(int i, int j) {
  return double((f[i] - f[j] + A * (sum[i] * sum[i] - sum[j] * sum[j]) +
                 B * (sum[j] - sum[i])) /
                double(2 * A * (sum[i] - sum[j])));
}
int main() {
  freopen("3628.in", "r", stdin);
  freopen("3628.out", "w", stdout);
  cin >> n >> A >> B >> C;
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), sum[i] = sum[i - 1] + a[i];
  for (int i = 1; i <= n; i++) {
    while (head < tail && work(que[head], que[head + 1]) <= sum[i] * 1.0)
      head++;
    long long X = sum[i] - sum[que[head]];
    f[i] = f[que[head]] + X * X * A + X * B + C;
    while (head <= tail && work(que[tail - 1], que[tail]) >= work(que[tail], i))
      tail--;
    que[++tail] = i;
  }
  cout << f[n];
}
