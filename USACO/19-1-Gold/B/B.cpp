#include <cstdio>
#include <iostream>
using namespace std;
int n, hd, head = 1e9, tot, pos = 1, a[100001], c[100001], opt[100001];
void add(int k) {
  for (int i = k; i <= n; i += i & -i)
    c[i]++;
}
int query(int k) {
  int ans = 0;
  for (int i = k; i > 0; i -= i & -i)
    ans += c[i];
  return ans;
}
int main() {
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
  cin >> n;
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  pos = n;
  while (a[pos] < head && pos > 0)
    add(a[pos]), head = a[pos], pos--;
  hd = pos;
  cout << hd << endl;
  for (pos = 1; pos <= hd; pos++) {
    printf("%d", hd - pos + query(a[pos]));
    if (pos < hd)
      cout << " ";
    add(a[pos]);
  }
}
