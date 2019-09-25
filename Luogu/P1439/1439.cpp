#include <cstdio>
#include <iostream>
using namespace std;
int n, a[100001], b[100001], c[100001], d[100001];
void add(int k, int x) {
  for (int i = k; i <= n; i += i & -i)
    c[i] = max(c[i], x);
}
int query(int x) {
  int ans = 0;
  for (int i = x; i > 0; i -= i & -i)
    ans = max(ans, c[i]);
  return ans;
}
int main() {
  freopen("1439.in", "r", stdin);
  freopen("1439.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    d[a[i]] = i;
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &b[i]);
    b[i] = d[b[i]];
  }
  for (int i = 1; i <= n; i++)
    add(b[i], query(b[i]) + 1);
  cout << query(n);
}
