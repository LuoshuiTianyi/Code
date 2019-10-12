#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
//#include <unordered_map>
#define lowbit(x) (x & -x)
#define lc o << 1
#define rc o << 1 | 1
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
const int INF = 0x3f3f3f3f;
const int MAXN = 1e5 + 5;
const int MAXM = 2e5 + 5;
const int MOD = 1e9 + 7;
const double PI = acos(-1.0);
const double EXP = 1e-8;
struct Treap {
  int l[MAXN], r[MAXN], val[MAXN], rnd[MAXN], size[MAXN], w[MAXN];
  int sz, ans, rt;
  inline void pushup(int x) { size[x] = size[l[x]] + size[r[x]] + w[x]; }
  void lrotate(int &k) {
    int t = r[k];
    r[k] = l[t];
    l[t] = k;
    size[t] = size[k];
    pushup(k);
    k = t;
  }
  void rrotate(int &k) {
    int t = l[k];
    l[k] = r[t];
    r[t] = k;
    size[t] = size[k];
    pushup(k);
    k = t;
  }
  void insert(int &k, int x) {
    if (!k) {
      sz++;
      k = sz;
      size[k] = 1;
      w[k] = 1;
      val[k] = x;
      rnd[k] = rand();
      return;
    }
    size[k]++;
    if (val[k] == x)
      w[k]++;
    else if (val[k] < x) {
      insert(r[k], x);
      if (rnd[r[k]] < rnd[k]) lround(k);
    } else {
      insert(l[k], x);
      if (rnd[l[k]] < rnd[k]) rrotate(k);
    }
  }
  void del(int &k, int x) {
    if (!k) return;
    if (val[k] == x) {
      if (w[k] > 1) {
        w[k]--;
        size[k]--;
        return;
      }
      if (l[k] == 0 || r[k] == 0)
        k = l[k] + r[k];
      else if (rnd[l[k]] < rnd[r[k]]) {
        rrotate(k);
        del(k, x);
      } else {
        lrotate(k);
        del(k, x);
      }
    } else if (val[k] < x) {
      size[k]--;
      del(r[k], x);
    } else {
      size[k]--;
      del(l[k], x);
    }
  }
  int queryrank(int k, int x) {
    if (!k) return 0;
    if (val[k] == x)
      return size[l[k]] + 1;
    else if (x > val[k])
      return size[l[k]] + w[k] + queryrank(r[k], x);
    else
      return queryrank(l[k], x);
  }
  int querynum(int k, int x) {
    if (!k) return 0;
    if (x <= size[l[k]])
      return querynum(l[k], x);
    else if (x > size[l[k]] + w[k])
      return querynum(r[k], x - size[l[k]] - w[k]);
    else
      return val[k];
  }
  void querypre(int k, int x) {
    if (!k) return;
    if (val[k] < x)
      ans = k, querypre(r[k], x);
    else
      querypre(l[k], x);
  }
  void querysub(int k, int x) {
    if (!k) return;
    if (val[k] > x)
      ans = k, querysub(l[k], x);
    else
      querysub(r[k], x);
  }
} T;
int n;
int main(void) {
  freopen("3369.in", "r", stdin);
  freopen("3369.ans", "w", stdout);
  srand(123);
  scanf("%d", &n);
  int opt, x;
  for (int i = 1; i <= n; i++) {
    scanf("%d%d", &opt, &x);
    if (opt == 1)
      T.insert(T.rt, x);
    else if (opt == 2)
      T.del(T.rt, x);
    else if (opt == 3)
      printf("%d\n", T.queryrank(T.rt, x));
    else if (opt == 4)
      printf("%d\n", T.querynum(T.rt, x));
    else if (opt == 5) {
      T.ans = 0;
      T.querypre(T.rt, x);
      printf("%d\n", T.val[T.ans]);
    } else if (opt == 6) {
      T.ans = 0;
      T.querysub(T.rt, x);
      printf("%d\n", T.val[T.ans]);
    }
  }
  return 0;
}
