#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
int n, m, a, tot[1000001], c[10002], cnt;
void work(int x) {
  for (int i = 1; i <= sqrt(x); i++)
    if (!(x % i)) {
      tot[i]++;
      if (i * i != x)
        tot[x / i]++;
    }
}
void add(int k, int x) {
  for (int i = k; i <= n; i += i & -i)
    c[i] = max(c[i], x);
}
int query(int k) {
  int ans = 0;
  for (int i = k; i > 0; i -= i & -i)
    ans = max(ans, c[i]);
  return ans;
}
int main() {
  freopen("1414.in", "r", stdin);
  freopen("1414.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a;
    work(a);
  }
  for (int i = 1000000; i >= 1; i--)
    add(n - tot[i] + 1, i);
  for (int i = 1; i <= n; i++)
    printf("%d\n", query(n - i + 1));
}
