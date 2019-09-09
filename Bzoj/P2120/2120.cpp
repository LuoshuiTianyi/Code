#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
int n, m, a[50001], book[1000001], L, R, T, cnt, Ans[50001], ans,
    Change[2][50002], pos[50002], time_a[50001], t[50002], size, qcnt;
char opt;
struct Que {
  int l, r, d, time;
} k[50001];
bool cmp(Que a, Que b) {
  return a.l / size != b.l / size
             ? a.l / size < b.l / size
             : a.r / size != b.r / size ? a.r < b.r : a.time < b.time;
}
void Del(int x) {
  book[a[x]]--;
  if (!book[a[x]])
    ans--;
}
void Add(int x) {
  book[a[x]]++;
  if (book[a[x]] == 1)
    ans++;
}
void Updateadd(int x, int l, int r) {
  if (Change[0][x] == Change[1][x])
    return;
  if (pos[x] >= l && pos[x] <= r) {
    book[Change[0][x]]--;
    book[Change[1][x]]++;
    if (!book[Change[0][x]])
      ans--;
    if (book[Change[1][x]] == 1)
      ans++;
  }
  a[pos[x]] = Change[1][x];
}
void Updatedel(int x, int l, int r) {
  if (Change[0][x] == Change[1][x])
    return;
  if (pos[x] >= l && pos[x] <= r) {
    book[Change[0][x]]++;
    book[Change[1][x]]--;
    if (!book[Change[1][x]])
      ans--;
    if (book[Change[0][x]] == 1)
      ans++;
  }
  a[pos[x]] = Change[0][x];
}
int main() {
  freopen("2120.in", "r", stdin);
  freopen("2120.out", "w", stdout);
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    time_a[i] = a[i];
  }
  for (int i = 1; i <= m; i++) {
    cin >> opt;
    if (opt == 'Q') {
      qcnt++;
      scanf("%d%d", &k[qcnt].l, &k[qcnt].r);
      k[qcnt].d = qcnt;
      k[qcnt].time = i;
    } else {
      cnt++;
      scanf("%d%d", &pos[cnt], &Change[1][cnt]);
      t[cnt] = i;
      Change[0][cnt] = time_a[pos[cnt]];
      time_a[pos[cnt]] = Change[1][cnt];
    }
  }
  t[cnt + 1] = 2e9;
  size = ceil(exp((log(n) + log(cnt)) / 3));
  sort(k + 1, k + qcnt + 1, cmp);
  L = k[1].l, R = k[1].l - 1;
  for (int i = 1; i <= qcnt; i++) {
    while (L < k[i].l)
      Del(L++);
    while (L > k[i].l)
      Add(--L);
    while (R < k[i].r)
      Add(++R);
    while (R > k[i].r)
      Del(R--);
    while (t[T + 1] < k[i].time && T <= cnt)
      Updateadd(++T, k[i].l, k[i].r);
    while (t[T] > k[i].time && T >= 1)
      Updatedel(T--, k[i].l, k[i].r);
    Ans[k[i].d] = ans;
  }
  for (int i = 1; i <= qcnt; i++)
    printf("%d\n", Ans[i]);
}
