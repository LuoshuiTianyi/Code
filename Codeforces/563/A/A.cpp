#include <cstdio>
#include <iostream>
using namespace std;
int n, ans;
char a[502][502];
bool pd(int x, int y) {
  char t = a[x][y], t1 = a[x - 1][y - 1], t2 = a[x - 1][y + 1],
       t3 = a[x + 1][y - 1], t4 = a[x + 1][y + 1];
  if (t == t1 && t1 == t2 && t2 == t3 && t3 == t4 && t4 == 'X')
    return true;
  return false;
}
int main() {
  freopen("A.in", "r", stdin);
  freopen("A.out", "w", stdout);
  cin >> n;
  char s[501];
  for (int i = 1; i <= n; i++) {
    cin >> s;
    for (int j = 1; j <= n; j++)
      a[i][j] = s[j - 1];
  }
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      if (pd(i, j))
        ans++;
  cout << ans;
}
