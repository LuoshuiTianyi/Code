#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define LL long long
#define go(G, x, i, v) \
  for (int i = G.hd[x], v = G.to[i]; i; v = G.to[i = G.nx[i]])

char read_str[1 << 25], *CH = read_str;
#define getchar() (*CH++)
LL read() {
  char ch = getchar();
  int fl = 0;
  LL x = 0;
  while (!isdigit(ch)) {
    if (ch == '-') fl = 1;
    ch = getchar();
  }
  while (isdigit(ch)) x = (x << 1) + (x << 3) + ch - '0', ch = getchar();
  return fl ? -x : x;
}
void rstr(char *s) {
  char *x = s;
  char ch = getchar();
  while (ch == ' ' || ch == '\n' || ch == '\r') ch = getchar();
  while (ch != ' ' && ch != '\n' && ch != '\r') {
    *x++ = ch;
    ch = getchar();
  }
}

const int Max_n = 5e5 + 5;
int n, Q, Ans[Max_n];
int l[Max_n], r[Max_n];
int top, stk[Max_n], c[Max_n];
char S[Max_n];
vector<int> M[Max_n];
queue<int> q;

namespace Input {
void main() {
  fread(read_str, 1, 1 << 25, stdin);
  n = read(), rstr(S + 1);
  Q = read();
  for (int i = 1; i <= Q; i++) {
    l[i] = read(), M[r[i] = read()].push_back(i);
  }
}
}  // namespace Input

namespace SegTree {
int Min[Max_n << 1], tag[Max_n << 1];
#define ls (o << 1)
#define rs (o << 1 | 1)
#define mid (l + r >> 1)
void pushdown(int o) { Min[ls] += tag[o], Min[rs] += tag[o], tag[o] = 0; }
void pushup(int o) { Min[o] = min(Min[ls], Min[rs]); }
void add(int o, int l, int r, int L, int R, int x) {
  if (L > R || R < 1) return;
  if (l >= L && r <= R) {
    Min[o] += x, tag[o] += x;
    return;
  }
  pushdown(o);
  if (mid >= L) add(ls, l, mid, L, R, x);
  if (mid < R) add(rs, mid + 1, r, L, R, x);
  pushup(o);
}
int query(int o, int l, int r, int L, int R) {
  if (L > R || R < 1) return 0;
  int ans = 1e9;
  if (l >= L && r <= R) return Min[o];
  pushdown(o);
  if (mid >= L) ans = min(ans, query(ls, l, mid, L, R));
  if (mid < R) ans = min(ans, query(rs, mid + 1, r, L, R));
  pushup(o);
  return ans;
}
}  // namespace SegTree
using namespace SegTree;

namespace Solve {
void cadd(int k) {
  for (int i = k; i <= n; i += i & -i) c[i]++;
}
int cqry(int k) {
  int ans = 0;
  for (int i = k; i; i -= i & -i) ans += c[i];
  return ans;
}
void main() {
  for (int i = 1; i <= n; i++) {
    if (S[i] == 'C') {
      if (top) add(1, 1, n, q.front(), i - 1, 1), cadd(q.front()), q.pop();
    }
    if (S[i] == 'T') q.push(i), add(1, 1, n, i, i, -1);
    add(1, 1, n, i, i, query(1, 1, n, i - 1, i - 1));
    for (int j = M[i].size() - 1; ~j; j--) {
      int x = M[i][j];
      Ans[x] = max(0, query(1, 1, n, l[x] - 1, l[x] - 1) - query(1, 1, n, l[x], i)) + cqry(i) - cqry(l[x] - 1);
    }
  }
  for (int i = 1; i <= Q; i++) printf("%d\n", Ans[i]);
}
}  // namespace Solve

int main() {
#ifndef ONLINE_JUDGE
  freopen("B.in", "r", stdin);
  freopen("B.out", "w", stdout);
#endif
  Input::main();
  Solve::main();
}
