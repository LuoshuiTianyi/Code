#include <bits/stdc++.h>
#define ll long long
#define re register
#define gc get_char
#define cs const

namespace IO {
inline char get_char() {
  static cs int Rlen = 1 << 22 | 1;
  static char buf[Rlen], *p1, *p2;
  return (p1 == p2) && (p2 = (p1 = buf) + fread(buf, 1, Rlen, stdin), p1 == p2)
             ? EOF
             : *p1++;
}

template <typename T>
inline T get() {
  re char c;
  while (!isdigit(c = gc()))
    ;
  re T num = c ^ 48;
  while (isdigit(c = gc())) num = (num + (num << 2) << 1) + (c ^ 48);
  return num;
}
inline int getint() { return get<int>(); }
}  // namespace IO
using namespace IO;

using std::cerr;
using std::cout;

cs int N = 1e6 + 6;

int n, m;

struct edge {
  int u, v;
};
std::vector<edge> pos[N];

int *sta[N << 1], top, pre[N << 1];
#define pack(x) (sta[++top] = &x, pre[top] = x)

int fa[N], siz[N];
inline int getfa(int x) { return x == fa[x] ? x : getfa(fa[x]); }
inline void merge(int x, int y) {
  x = getfa(x), y = getfa(y);
  if (x == y) return;
  if (siz[x] < siz[y]) std::swap(x, y);
  pack(siz[x]);
  pack(fa[y]);
  siz[x] += siz[y], fa[y] = x;
}

void solve(int l, int r) {
  if (l == r) {
    if (siz[getfa(1)] == n) cout << l, exit(0);
    return;
  }
  int mid = (l + r) >> 1, low = top;
  for (int re i = mid + 1; i <= r; ++i)
    for (auto &e : pos[i]) merge(e.u, e.v);
  solve(l, mid);
  while (top > low) *sta[top] = pre[top--];
  for (int re i = l; i <= mid; ++i)
    for (auto &e : pos[i]) merge(e.u, e.v);
  solve(mid + 1, r);
  while (top > low) *sta[top] = pre[top--];
}

signed main() {
  //  freopen("graph.in","r",stdin);freopen("graph.out","w",stdout);
  freopen("A.in", "r", stdin);
  freopen("A.out", "w", stdout);
  n = getint(), m = getint();
  while (m--) {
    int u = getint(), v = getint(), w = getint();
    pos[w].push_back((edge){u, v});
  }
  for (int re i = 1; i <= n; ++i) fa[i] = i, siz[i] = 1;
  solve(0, 100001);
  return 0;
}
