#include <cstdio>
#include <iostream>
using namespace std;
int n, m, book[10000001], pri[10000001], cnt;
int main() {
  freopen("3383.in", "r", stdin);
  freopen("3383.out", "w", stdout);
  cin >> n >> m;
  book[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!book[i])
      pri[++cnt] = i;
    for (int j = 1; j <= cnt; j++) {
      if ((long long)pri[j] * (long long)i > n)
        break;
      book[i * pri[j]] = 1;
      if (!(i % pri[j]))
        break;
    }
  }
  for (int i = 1; i <= m; i++) {
    int x;
    scanf("%d", &x);
    if (!book[x])
      cout << "Yes\n";
    else
      cout << "No\n";
  }
}
