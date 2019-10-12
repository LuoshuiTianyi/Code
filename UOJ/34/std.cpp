#include <vector>
#include <cmath>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <iostream>
#include <algorithm>

typedef long long LL;
typedef unsigned long long uLL;

#define fir first
#define sec second
#define SZ(x) (int)x.size()
#define MP(x, y) std::make_pair(x, y)
#define PB(x) push_back(x)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define GO debug("GO\n")
#define rep(i, a, b) for (register int i = (a), i##end = (b); (i) <= i##end; ++ (i))
#define drep(i, a, b) for (register int i = (a), i##end = (b); (i) >= i##end; -- (i))
#define REP(i, a, b) for (register int i = (a), i##end = (b); (i) < i##end; ++ (i))

inline int read() {
    register int x = 0; register int f = 1; register char c;
    while (!isdigit(c = getchar())) if (c == '-') f = -1;
    while (x = (x << 1) + (x << 3) + (c xor 48), isdigit(c = getchar()));
    return x * f;
}
template<class T> inline void write(T x) {
    static char stk[30]; static int top = 0;
    if (x < 0) { x = -x, putchar('-'); }
    while (stk[++top] = x % 10 xor 48, x /= 10, x);
    while (putchar(stk[top--]), top);
}
template<typename T> inline bool chkmin(T &a, T b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, T b) { return a < b ? a = b, 1 : 0; }

using namespace std;

const int N = 3e6 + 10;
const int P = 998244353;
const int G = 3;
const int inv2 = (P + 1) >> 1;

int qpow(LL a, int b, int P) {
    LL ans(1);
    while (b) {
        if (b & 1) {
            ans = ans * a % P;
        }
        a = a * a % P;
        b >>= 1;
    }
    return ans;
}

int Inv(int x) { 
    return qpow(x, P - 2, P);
}

namespace Poly {
    int rev[N], omega[N], invomega[N];
    void init(int lim, int lg2) {
        REP (i, 0, lim) {
            rev[i] = rev[i >> 1] >> 1 | (i & 1) << (lg2 - 1);
        }
        omega[0] = 1, omega[1] = qpow(G, (P - 1) / lim, P);
        invomega[0] = 1, invomega[1] = Inv(omega[1]);
        REP (i, 2, lim) {
            omega[i] = 1ll * omega[i - 1] * omega[1] % P;
            invomega[i] = 1ll * invomega[i - 1] * invomega[1] % P;
        }
    }
    void NTT(int a[], int lim, int omega[]) {
        REP (i,0, lim) {
            if (rev[i] > i) {
                swap(a[i], a[rev[i]]);
            }
        }
        for (register int len = 2; len <= lim; len <<= 1) {
            register int m = len >> 1;
            for (register int *p = a; p != a + lim; p += len) {
                for (register int i = 0; i < m; ++i) {
                    register int t = 1ll * omega[lim / len * i] * p[i + m] % P;
                    p[i + m] = (1ll * p[i] - t + P) % P;
                    p[i] = (1ll * p[i] + t) % P;
                }
            }
        }
    }
    void DFT(int a[], int lim) {
        NTT(a, lim, omega);
    }
    void IDFT(int a[], int lim) {
        NTT(a, lim, invomega);
        int invlim = Inv(lim);
        REP (i, 0, lim) {
            a[i] = 1ll * a[i] * invlim % P;
        }
    }
    void Mul(const int a[], const int b[], int n, int m, int c[]) {
        static int A[N], B[N];
        int bit = log2(n + m - 2) + 1;
        int lim = 1 << bit;
        copy(a, a + n, A); 
        fill(A + n, A + lim, 0);
        copy(b, b + m, B);
        fill(B + m, B + lim, 0);
        init(lim, bit);
        DFT(A, lim), DFT(B, lim);
        REP (i, 0, lim)
          cout << A[i] << endl;
        REP (i, 0, lim) {
            A[i] = 1ll * A[i] * B[i] % P;
        }
        IDFT(A, lim);
        copy(A, A + n + m - 1, c);
    }
}

int main() 
{
#ifndef ONLINE_JUDGE
    freopen("34.in", "r", stdin);
    freopen("34.ans", "w", stdout);
#endif
    static int a[N], n, m, b[N], c[N];
    n = read(), m = read();
    n++, m++;
    REP (i, 0, n) {
        a[i] = read();
    }
    REP (i, 0, m) {
        b[i] = read();
    }
    Poly::Mul(a, b, n, m, c);
    REP (i, 0, n + m - 1) {
        write(c[i]), putchar(' ');
    }
    return 0;
}
