#include <algorithm>
#include <cstdio>
#include <iostream>
#define ll long long
#define re register
#define cs const

namespace IO {

inline char gc() {
    static cs int Rlen = 1 << 22 | 1;
    static char buf[Rlen], *p1, *p2;
    return (p1 == p2) && (p2 = (p1 = buf) + fread(buf, 1, Rlen, stdin), p1 == p2) ? EOF : *p1++;
}
template <typename T>
T get_integer() {
    char c;
    bool f = false;
    while (!isdigit(c = gc())) f = c == '-';
    T x = c ^ 48;
    while (isdigit(c = gc())) x = ((x + (x << 2)) << 1) + (c ^ 48);
    return f ? -x : x;
}
inline int gi() { return get_integer<int>(); }

char obuf[(int)(3e7 + 7)], *oh = obuf, ch[23];
template <typename T>
void print(T a, char c) {
    if (a < 0)
        a = -a, *oh++ = '-';
    int tl = 0;
    do
        ch[++tl] = a % 10;
    while (a /= 10);
    while (tl) *oh++ = ch[tl--] ^ 48;
    *oh++ = c;
}
struct obuf_flusher {
    ~obuf_flusher() { fwrite(obuf, 1, oh - obuf, stdout); }
} Flusher;

}  // namespace IO
using IO::gi;
using IO::print;

using std::cerr;
using std::cout;

cs int N = 5e5 + 7;

int n, m, op, ans;
int a[N], b[N], uf[N];
int cir[N], vs[N];
inline int gf(int u) {
    while (u != uf[u]) u = uf[u] = uf[uf[u]];
    return u;
}

int el[N], nx[N + N], to[N + N], w[N + N], rev[N + N], ec;

void adde(int u, int v, int vl) { nx[++ec] = el[u], el[u] = ec, to[ec] = v, w[ec] = vl; }

int in[N], ou[N], dfc;
int bel[N + N], typ[N + N], rt[N], tct;

void dfs_tree(int u, int rt, int p) {
    in[u] = ++dfc, vs[u] = true;
    for (int re e = el[u]; e; e = nx[e])
        if (to[e] != p) {
            dfs_tree(to[e], rt, u);
            bel[e] = bel[rev[e]] = rt;
            typ[e] = typ[rev[e]] = 1;
        }
    ou[u] = dfc;
}
void prework_tree(int u) { dfs_tree(u, u, 0), rt[++tct] = u; }

int L[N], R[N], cct, st[N], top;
void dfs_cir(int u, int tp, int ban, int p) {
    vs[u] = true;
    if (u == tp)
        for (int re i = 1; i <= top; ++i) {
            typ[st[i]] = 2, L[cct] += w[st[i]];
            typ[rev[st[i]]] = 3, R[cct] += w[rev[st[i]]];
        }
    for (int re e = el[u]; e; e = nx[e])
        if (to[e] != p && e != ban && e != rev[ban]) {
            bel[e] = bel[rev[e]] = cct, typ[e] = 4;
            st[++top] = e, dfs_cir(to[e], tp, ban, u), --top;
        }
}
void prework_cir(int u) {
    ++cct;
    int e = cir[u];
    dfs_cir(to[e], to[rev[e]], e, 0);
    bel[e] = bel[rev[e]] = cct;
    typ[e] = 2, L[cct] += w[e];
    if (e != rev[e])
        typ[rev[e]] = 3, R[cct] += w[rev[e]];
    ans += std::max(L[cct], R[cct]);
}

namespace SGT {

#define lc u << 1
#define rc lc | 1
int mx[N << 2], ad[N << 2];

void modify(int u, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr) {
        mx[u] += v, ad[u] += v;
        return;
    }
    int m = (l + r) >> 1;
    if (ql <= m)
        modify(lc, l, m, ql, qr, v);
    if (m < qr)
        modify(rc, m + 1, r, ql, qr, v);
    mx[u] = std::max(mx[lc], mx[rc]) + ad[u];
}

int query(int u, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return mx[u];
    int m = (l + r) >> 1;
    if (qr <= m)
        return query(lc, l, m, ql, qr) + ad[u];
    if (m < ql)
        return query(rc, m + 1, r, ql, qr) + ad[u];
    return std::max(query(lc, l, m, ql, qr), query(rc, m + 1, r, ql, qr)) + ad[u];
}

}  // namespace SGT
using SGT::modify;
using SGT::query;

void modify_tree(int e, int w) {
    int u = to[e], v = to[rev[e]];
    if (in[u] < in[v])
        modify(1, 1, dfc, in[v], ou[v], w);
    else {
        modify(1, 1, dfc, in[bel[e]], ou[bel[e]], w);
        modify(1, 1, dfc, in[u], ou[u], -w);
    }
}

void Main() {
    m = gi(), n = gi(), op = gi();
    for (int re i = 0; i < m; ++i) a[i] = gi();
    for (int re i = 0; i < m; ++i) b[i] = gi();
    for (int re i = 1; i <= n; ++i) uf[i] = i;
    for (int re i = 0; i < m; ++i) {
        int u = (a[i] + b[i]) % n + 1;
        int v = (a[i] - b[i] + n) % n + 1;
        if (u > v)
            std::swap(u, v);
        adde(v, u, gi());
        int fu = gf(u), fv = gf(v);
        if (fu == fv)
            cir[fu] = ec;
        else
            uf[fu] = fv, cir[fv] |= cir[fu];
        if (u != v) {
            adde(u, v, gi());
            rev[ec] = ec - 1, rev[ec - 1] = ec;
        } else
            rev[ec] = ec;
    }
    for (int re i = 1; i <= n; ++i)
        if (!vs[i]) {
            int u = gf(i);
            //	cerr<<"rt : "<<u<<" "<<cir[u]<<"\n";
            if (!cir[u])
                prework_tree(u);
            else
                prework_cir(u);
        }
    for (int re i = 1; i <= ec; ++i)
        if (typ[i] == 4)
            ans += w[i];
        else if (typ[i] == 1)
            modify_tree(i, w[i]);
    for (int re i = 1; i <= tct; ++i) ans += query(1, 1, dfc, in[rt[i]], ou[rt[i]]);
    int Q = gi();
    print(ans, '\n');
    while (Q--) {
        int e = gi() - ans * op, vl = gi() - ans * op;
        switch (typ[e]) {
            case 0:
                break;
            case 1: {
                ans -= query(1, 1, dfc, in[bel[e]], ou[bel[e]]);
                modify_tree(e, vl - w[e]);
                w[e] = vl;
                ans += query(1, 1, dfc, in[bel[e]], ou[bel[e]]);
                break;
            }
            case 2: {
                ans -= std::max(L[bel[e]], R[bel[e]]);
                L[bel[e]] += vl - w[e];
                w[e] = vl;
                ans += std::max(L[bel[e]], R[bel[e]]);
                break;
            }
            case 3: {
                ans -= std::max(L[bel[e]], R[bel[e]]);
                R[bel[e]] += vl - w[e];
                w[e] = vl;
                ans += std::max(L[bel[e]], R[bel[e]]);
                break;
            }
            case 4: {
                ans += vl - w[e], w[e] = vl;
                break;
            }
        }
        print(ans, '\n');
    }
}

signed main() {
  freopen("523.in", "r", stdin);
  freopen("523.ans", "w", stdout);
    Main();
    return 0;
}
