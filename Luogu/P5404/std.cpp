#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <fstream>

typedef long long LL;
typedef unsigned long long uLL;

#define SZ(x) ((int)x.size())
#define ALL(x) (x).begin(), (x).end()
#define MP(x, y) std::make_pair(x, y)
#define DE(x) cerr << x << endl;
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define GO cerr << "GO" << endl;

using namespace std;

inline void proc_status() {
    ifstream t("/proc/self/status");
    cerr << string(istreambuf_iterator<char>(t), istreambuf_iterator<char>()) << endl;
}
inline int read() {
    register int x = 0;
    register int f = 1;
    register char c;
    while (!isdigit(c = getchar()))
        if (c == '-')
            f = -1;
    while (x = (x << 1) + (x << 3) + (c xor 48), isdigit(c = getchar()))
        ;
    return x * f;
}
template <class T>
inline void write(T x) {
    static char stk[30];
    static int top = 0;
    if (x < 0) {
        x = -x, putchar('-');
    }
    while (stk[++top] = x % 10 xor 48, x /= 10, x)
        ;
    while (putchar(stk[top--]), top)
        ;
}
template <typename T>
inline bool chkmin(T &a, T b) {
    return a > b ? a = b, 1 : 0;
}
template <typename T>
inline bool chkmax(T &a, T b) {
    return a < b ? a = b, 1 : 0;
}

const int maxN = 2e3;
const int mod = 998244353;

namespace math {
void pls(int &x, int y) {
    x += y;
    if (x >= mod)
        x -= mod;
    if (x < 0)
        x += mod;
}
LL qpow(LL a, LL b) {
    LL ans(1);
    while (b) {
        if (b & 1)
            ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}
}  // namespace math
using math::pls;
using math::qpow;

int n, m;  // n字符串长度，m走m步
char str[maxN + 2];
int fail[maxN + 2], ver[maxN + 2], edge[maxN + 2];

void insert() {
    fail[1] = 0;
    for (int i = 2, j = 0; i <= n; ++i) {
        while (j and str[j + 1] != str[i]) j = fail[j];
        j += str[j + 1] == str[i];
        fail[i] = j;
    }
}

void build() {
    for (int i = 0; i <= n; ++i) {
        for (int j = 25; j >= 0; --j) {
            int p = i;
            if (p == n)
                p = fail[p];
            while (p and str[p + 1] != j + 'a') p = fail[p];
            p += (str[p + 1] == (j + 'a'));
            if (p) {
                ver[i] = p;
                edge[i] = 25 - j;
                break;
            }
        }
    }
}

int size;
int f[maxN + 2][maxN + 2], g[maxN + 2][maxN + 2];  // f[i][u] : root -> u cost i ; g[i][u] : u -> root cost i

void DP() {
    f[0][0] = 1;
    for (int i = 0; i < m; ++i)
        for (int j = 0; j <= n; ++j) {
            pls(f[i + 1][ver[j]], f[i][j]);
            pls(f[i + 1][0], 1ll * f[i][j] * edge[j] % mod);
        }
    for (int i = 0; i <= n; ++i) g[1][i] = edge[i];
    for (int i = 2; i <= m; ++i)
        for (int j = 0; j <= n; ++j) g[i][j] = g[i - 1][ver[j]];
}

int key;
bool vis[maxN + 2];

bool dfs(int u) {
    if (!u)
        return 0;
    if (vis[u]) {
        key = u;
        return 1;
    }
    vis[u] = 1;
    if (dfs(ver[u])) {
        size++;
        return key != u;
    }
    return 0;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("5404.in", "r", stdin);
    freopen("5404.ans", "w", stdout);
#endif
    scanf("%d %s", &m, str + 1);
    n = strlen(str + 1);

    insert();
    build();
    DP();
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= m; j++)
      cout << g[j][i] << " ";
    cout << endl;
  }
    int ans = 0;
    dfs(1);
    if (m % size == 0)
        ans = size;
    for (int i = 0; i <= n; ++i) {
        int sum = 0;
        for (int j = 0; j <= m; ++j) pls(sum, 1ll * f[j][i] * g[m - j][i] % mod);
        pls(ans, sum);
    }
    cout << ((qpow(26, m) - ans) % mod + mod) % mod << endl;
    return 0;
}
