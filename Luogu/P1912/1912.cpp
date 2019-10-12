#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int T, n, L, P, sum[100001], g[100001];
int que[100001], l[100001], h, t;
char s[100001][31];
long double f[100001];
long double Pow(int x) {
  long double base = 1;
  for (int i = 1; i <= P; i++)
    base = base * (long double)x;
  return base;
}
long double work(int a, int b) {
  return f[a] + Pow((int)abs(sum[b] - sum[a] - 1 - L));
}
int find(int a, int b) {
  int l = a, r = n, ans = n + 1;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (work(a, mid) >= work(b, mid))
      r = mid - 1, ans = mid;
    else
      l = mid + 1;
  }
  return ans;
}
int main() {
  freopen("1912.in", "r", stdin);
  freopen("1912.out", "w", stdout);
  cin >> T;
  while (T--) {
    cin >> n >> L >> P;
    for (int i = 1; i <= n; i++) {
      scanf("%s", s[i]);
      sum[i] = strlen(s[i]) + sum[i - 1] + 1;
    }
    que[h = t = 0] = 0;
    for (int i = 1; i <= n; i++) {
      while (h < t && l[h] <= i)
        h++;
      g[i] = que[h];
      f[i] = work(g[i], i);
      while (h < t && find(que[t], i) <= l[t - 1])
        t--;
      l[t] = find(que[t], i);
      que[++t] = i;
    }
    if (f[n] > 1e18)
      cout << "Too hard to arrange\n";
    else {
      printf("%lld\n", (long long)f[n]);
      int stack[100001], top = 0, now = n;
      while (now) {
        stack[++top] = now;
        now = g[now];
      }
      stack[top + 1] = 0;
      for (int i = top; i; i--) {
        int l = stack[i + 1] + 1, r = stack[i];
        for (int j = l; j < r; j++)
          printf("%s ", s[j]);
        printf("%s\n", s[r]);
      }
    }
    puts("--------------------");
  }
}
