#include <algorithm>
#include <cstdio>
#include <iostream>
using namespace std;
int n, cnt, M = 27, a[300001], sa[300001], rk[300001], height[300001],
            tp[300001], tag[300001], fa[300001], size[300001], Max[300001],
            Min[300001], w[300001], id[300001];
char s[300002];
long long Ans[300002], amax[300001], sum[300002];
void Sort() {
  for (int i = 1; i <= M; i++)
    tag[i] = 0;
  for (int i = 1; i <= n; i++)
    tag[rk[i]]++;
  for (int i = 1; i <= M; i++)
    tag[i] += tag[i - 1];
  for (int i = n; i >= 1; i--)
    sa[tag[rk[tp[i]]]--] = tp[i];
}
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
bool cmp(int a, int b) { return height[a] > height[b]; }
void Merge(int a, int b, int len) {
  a = find(a), b = find(b);
  fa[b] = a;
  sum[len] += 1ll * size[a] * size[b];
  size[a] += size[b];
  amax[a] = max(
      amax[a], max(amax[b], max(1ll * Max[a] * Max[b], 1ll * Min[a] * Min[b])));
  Max[a] = max(Max[a], Max[b]);
  Min[a] = min(Min[a], Min[b]);
  Ans[len] = max(Ans[len], amax[a]);
}
int main() {
  freopen("2178.in", "r", stdin);
  freopen("2178.out", "w", stdout);
  cin >> n;
  scanf("%s", s + 1);
  for (int i = 1; i <= n; i++)
    scanf("%d", &w[i]);
  for (int i = 1; i <= n; i++)
    rk[i] = s[i] - 'a' + 1, tp[i] = i;
  Sort();
  for (int len = 1; cnt < n; len <<= 1, M = cnt) {
    cnt = 0;
    for (int i = n - len + 1; i <= n; i++)
      tp[++cnt] = i;
    for (int i = 1; i <= n; i++)
      if (sa[i] > len)
        tp[++cnt] = sa[i] - len;
    Sort();
    swap(tp, rk);
    rk[sa[1]] = cnt = 1;
    for (int i = 2; i <= n; i++)
      rk[sa[i]] =
          tp[sa[i - 1]] == tp[sa[i]] && tp[sa[i - 1] + len] == tp[sa[i] + len]
              ? cnt
              : ++cnt;
  }
  for (int i = 1, len = 0; i <= n; i++) {
    if (len)
      len--;
    int x = sa[rk[i] - 1];
    while (s[x + len] == s[i + len])
      len++;
    height[rk[i]] = len;
  }
  for (int i = 1; i <= n; i++)
    Max[i] = Min[i] = w[i], amax[i] = Ans[i] = -1e18, id[i] = fa[i] = i,
    size[i] = 1;
  Ans[n + 1] = Ans[0] = -1e18;
  sort(id + 2, id + n + 1, cmp);
  for (int i = 2; i <= n; i++)
    Merge(sa[id[i]], sa[id[i] - 1], height[id[i]]);
  for (int i = n; i >= 0; i--)
    sum[i] += sum[i + 1], Ans[i] = max(Ans[i], Ans[i + 1]);
  for (int i = 0; i < n; i++)
    printf("%lld %lld\n", sum[i], !sum[i] ? 0 : Ans[i]);
}
