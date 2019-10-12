#include <bits/stdc++.h>
#include <tr1/unordered_map>
#define For(i, a, b) for (int i = a, i##E = b; i <= i##E; ++i)
#define rFor(i, a, b) for (int i = a, i##E = b; i >= i##E; --i)
#define pii pair<int, int>
#define mem(a, b) memset(a, b, sizeof(a))
#define SZ(x) (int)x.size()
#define ft first
#define sd second
#define pb push_back
#define ls l, mid
#define rs mid + 1, r
#define lc p << 1
#define rc p << 1 | 1
using namespace std;
typedef long long LL;
const int N = 1000010;
const int inf = 0x3f3f3f3f;
template <typename T> inline bool chkmax(T &A, const T &B) {
  return A < B ? A = B, 1 : 0;
}
template <typename T> inline bool chkmin(T &A, const T &B) {
  return A > B ? A = B, 1 : 0;
}
template <typename T> inline void read(T &x) {
  x = 0;
  int f = 0;
  char ch = getchar();
  while (!isdigit(ch))
    f |= (ch == '-'), ch = getchar();
  while (isdigit(ch))
    x = x * 10 + ch - '0', ch = getchar();
  x = f ? -x : x;
}
inline void file() {
  freopen("4436.in", "r", stdin);
  freopen("test.out", "w", stdout);
}
int n, m, Q;
int key[N], p[N];
int l[N], r[N], st[N], top;
int lS[N], rS[N];
int t[N << 3];
inline void Build(int l, int r, int p) {
  if (l == r) {
    t[p] = key[l];
    return;
  }
  int mid = (l + r) >> 1;
  Build(ls, lc), Build(rs, rc);
  t[p] = max(t[lc], t[rc]);
}
inline int Get(int l, int r, int p, int x) {
  if (t[p] <= x)
    return 0;
  if (l == r)
    return l;
  int mid = (l + r) >> 1;
  return t[rc] > x ? Get(rs, rc, x) : Get(ls, lc, x);
}
inline int Query(int l, int r, int p, int x, int y, int z) {
  if (x <= l && r <= y)
    return Get(l, r, p, z);
  int mid = (l + r) >> 1, pos = 0;
  if (y > mid)
    pos = Query(rs, rc, x, y, z);
  if (pos)
    return pos;
  if (x <= mid)
    pos = Query(ls, lc, x, y, z);
  return pos;
}
inline int find_pos(int l, int r, int x)
// the last pos_i in [l,r] that key[i]>r;
{
  if (l > r)
    return l;
  int pos = Query(1, n, 1, l, r, x);
  return pos ? pos + 1 : l;
}
inline void init() {
  Build(1, n, 1);
  key[n] = n + 1;
  key[0] = -1;
  For(i, 1, n) lS[i] = key[i - 1] && key[i - 1] <= i - 1 ? i : lS[i - 1];
  rFor(i, n, 1) rS[i] = key[i] && key[i] > i ? i : rS[i + 1];
  rFor(i, n, 1) {
    l[i] = r[i] = i;
    l[i] = find_pos(lS[i], l[i] - 1, r[i]);
    st[++top] = i;
    while (top &&
           ((l[i] <= key[st[top]] && key[st[top]] <= r[i]) || !key[st[top]])) {
      r[i] = st[--top];
      l[i] = find_pos(lS[i], l[i] - 1, r[i]);
    }
  }
}
int main() {
  int x, y;
  file();
  read(n), read(m), read(Q);
  For(i, 1, m) read(x), read(y), key[x] = y;
  init();
  /*while(Q--)
  {
      read(x),read(y);
      printf("%s\n",l[x]<=y&&y<=r[x]?"YES":"NO");
  }*/
  for (int i = 1; i <= n; i++)
    printf("%d %d\n", l[i], r[i]);
  return 0;
}
