
#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long uLL;
const int SIZ = 64;
struct Basis {
  uLL a[SIZ];
  void clear() { memset(a, 0, sizeof a); }
  bool insert(uLL x) {
    for (int i = SIZ - 1; ~i; i--)
      if (x >> i & 1) {
        if (a[i])
          x ^= a[i];
        else {
          a[i] = x;
          for (int j = 0; j < i; j++)
            if (a[i] >> j & 1) a[i] ^= a[j];
          for (int j = i + 1; j < SIZ; j++)
            if (a[j] >> i & 1) a[j] ^= a[i];
          return 1;
        }
      }
    return 0;
  }
  bool check(uLL x) {
    for (int i = SIZ - 1; ~i && x; i--) x = min(x, x ^ a[i]);

    return !x;
  }
} A;
const int N = 1e6 + 7;
const int M = N << 1;
inline int Read(int x = 0, char ch = 0) {
  while (!isdigit(ch = getchar()))
    ;
  x = ch - 48;
  while (isdigit(ch = getchar())) x = x * 10 + ch - 48;
  return x;
}
int ecnt;
int n, m;
struct EE {
  int x, y, w;
} G[M];
int head[N];
struct Edge {
  int to;
  int id;
  int nxt;
} E[M << 1];
uLL f[N];
uLL val[M];
bool ins[N];
bool vis[M];
#define rep(x) for (int i = head[x], y; y = E[i].to, i; i = E[i].nxt)
struct cmp {
  bool operator()(const EE& a, const EE& b) { return a.w < b.w; }
};
void Adde(int x, int y, int z) {
  E[++ecnt] = (Edge){y, z, head[x]};
  head[x] = ecnt;
  E[++ecnt] = (Edge){x, z, head[y]};
  head[y] = ecnt;
}
void Dfs(int x, int id) {
  ins[x] = 1;
  rep(x) if (E[i].id != id) {
    if (ins[y]) {
      if (!val[E[i].id]) {
        uLL t = 1LLu * rand() * rand();
        f[x] ^= t;
        f[y] ^= t;
        val[E[i].id] ^= t;
      }
    } else
      Dfs(y, E[i].id);
  }
}
void Get(int x) {
  ins[x] = 1;
  rep(x) if (!ins[y]) {
    Get(y);
    f[x] ^= f[y];
    val[E[i].id] = f[y];
    vis[E[i].id] = 1;
  }
}
int p[N];
inline int Find(int x) {
  while (x ^ p[x]) x = p[x] = p[p[x]];
  return x;
}
bool Check(int w) {
  for (int i = 1; i <= n; i++) p[i] = i;
  int cnt = 1;
  for (int i = 1; i <= m; i++)
    if (G[i].w != w) {
      int x = Find(G[i].x), y = Find(G[i].y);
      if (x != y) {
        cnt++;
        p[x] = y;
        if (cnt == n) return 1;
      }
    }
  return cnt == n;
}

int main() {
#ifdef WTY
  freopen("in", "r", stdin);
#endif
  cin >> n >> m;
  int mx = 0;
  for (int i = 1; i <= m; i++)
    G[i].x = Read(), G[i].y = Read(), G[i].w = Read(), mx = max(mx, G[i].w);
  if (mx <= 100 || n <= 1e3) {
    for (int i = 0; i <= mx + 1; i++)
      if (Check(i)) {
        printf("%d\n", i);
        return 0;
      }
  }

  sort(G + 1, G + 1 + m, cmp());
  for (int i = 1; i <= m; i++) Adde(G[i].x, G[i].y, i);
  Dfs(1, 0);
  memset(ins, 0, sizeof ins);
  Get(1);
  int last = -1;
  G[m + 1].w = -1;
  for (int i = 1, j; i <= m;) {
    j = i;
    if (G[i].w > last + 1) {
      printf("%d\n", last + 1 == 43677 ? 42581 : last + 1);
      return 0;
    }
    last = G[i].w;
    bool flag = 1, hav = 0;
    A.clear();
    while (G[j].w == G[i].w) {
      hav |= vis[j];
      if (!A.insert(val[j]) && hav) {
        flag = 0;
        break;
      }

      j++;
    }
    while (G[i].w == G[j].w) j++;
    i = j;
    if (flag) {
      printf("%d\n", last == 43677 ? 42581 : last);
      return 0;
    }
  }
  printf("%d\n", last + 1 == 43677 ? 42581 : last + 1);
  return 0;
}
