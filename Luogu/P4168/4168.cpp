#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
int n, m, col[40001], key[40001], ans, l, r, cnt;
int L[40001], size, sum, p[201][201], s[201][40001];
int now[40001], wait[40001], pos;
struct node {
  int d, w;
} k[40001];
bool cmp(node a, node b) { return a.w < b.w; }
void Init() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    scanf("%d", &col[i]);
    k[i].d = i, k[i].w = col[i];
  }
  sort(k + 1, k + n + 1, cmp);
  for (int i = 1; i <= n; i++) {
    if (k[i].w != k[i - 1].w)
      cnt++;
    col[k[i].d] = cnt;
    key[cnt] = k[i].w;
  }
  size = sqrt(n);
  L[1] = 1;
  for (sum = 1; L[sum] < n; sum++)
    L[sum + 1] = L[sum] + size;
  if (L[sum] > n)
    sum--;
}
void Preprocess() {
  for (int i = 1; i <= sum; i++) {
    int book[40001] = {0}, num = 0;
    for (int j = 1; j <= cnt; j++)
      s[i][j] = s[i - 1][j];
    for (int j = L[i]; j <= L[i] + size - 1; j++)
      s[i][col[j]]++;
    for (int j = i; j <= sum; j++) {
      for (int k = L[j]; k <= min(L[j] + size - 1, n); k++) {
        book[col[k]]++;
        if (book[col[k]] > book[num] ||
            (book[col[k]] == book[num] && col[k] < num))
          num = col[k];
      }
      p[i][j] = num;
    }
  }
}
void work(int x) {
  if (!now[x]) {
    pos++;
    wait[pos] = x;
  }
  now[x]++;
}
int main() {
  freopen("4168.in", "r", stdin);
  freopen("4168.out", "w", stdout);
  Init();
  Preprocess();
  while (m--) {
    scanf("%d%d", &l, &r);
    l = (l + ans - 1) % n + 1, r = (r + ans - 1) % n + 1;
    pos = 0;
    if (l > r)
      swap(l, r);
    int posl = (l + size - 1) / size, posr = (r + size - 1) / size;
    if (posr - posl <= 4)
      for (int i = l; i <= r; i++)
        work(col[i]);
    else {
      for (int i = l; i < L[posl + 1]; i++)
        work(col[i]);
      for (int i = L[posr]; i <= r; i++)
        work(col[i]);
      for (int i = 1; i <= pos; i++)
        now[wait[i]] += (s[posr - 1][wait[i]] - s[posl][wait[i]]);
      int maxx = p[posl + 1][posr - 1];
      if (!now[maxx]) {
        pos++;
        wait[pos] = maxx;
        now[maxx] += s[posr - 1][maxx] - s[posl][maxx];
      }
    }
    ans = 0;
    for (int i = 1; i <= pos; i++)
      if (now[wait[i]] > now[ans] ||
          (now[wait[i]] == now[ans] && wait[i] < ans))
        ans = wait[i];
    for (int i = 1; i <= pos; i++)
      now[wait[i]] = 0;
    ans = key[ans];
    printf("%d\n", ans);
  }
}
