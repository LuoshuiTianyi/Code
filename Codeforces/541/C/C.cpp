#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
int n, L, R, a[101], cnt, l[101], r[101], ll[101], rr[101], fa[101];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
int find1(int x) {
  int minn = 0;
  for (int i = 1; i <= n; i++)
    if (i != x && !r[i]) {
      if (cnt > 1 && find(x) == find(i))
        continue;
      if (abs(a[i] - a[x]) < abs(a[minn] - a[x]))
        minn = i;
    }
  return minn;
}
int find2(int x) {
  int minn = 0;
  for (int i = 1; i <= n; i++)
    if (i != x && !l[i]) {
      if (cnt > 1 && find(x) == find(i))
        continue;
      if (abs(a[i] - a[x]) < abs(a[minn] - a[x]))
        minn = i;
    }
  return minn;
}
int main() {
  // freopen("C.in","r",stdin);
  // freopen("C.out","w",stdout);
  cin >> n;
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  sort(a + 1, a + n + 1);
  a[0] = -1e9;
  for (int i = 1; i <= n; i++)
    fa[i] = i;
  cnt = n;
  for (int i = n; i >= 1; i--) {
    if (!l[i]) {
      int now = find1(i);
      fa[find(now)] = find(i);
      cnt--;
      l[i] = now, r[now] = i;
    }
    if (!r[i]) {
      int now = find2(i);
      fa[find(now)] = find(i);
      cnt--;
      r[i] = now, l[now] = i;
    }
  }
  for (int now = 1, cnt = 1; cnt <= n; now = l[now], cnt++)
    printf("%d ", a[now]);
}
