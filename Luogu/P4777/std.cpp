#include <iostream>
#include <algorithm>

using namespace std;
using LL = long long;
using LLL = __int128;

const int maxN = 1e5 + 5;

int n;
LL a[maxN], p[maxN];

void Exgcd(LL& x, LL& y, LL a, LL b, LL c, LL mod)
{
    if (b == 0)
    {
        if (c % a)
            throw;
        x = c / a, y = 0;
        return;
    }
    Exgcd(x, y, b, a % b, c, mod);
    LL t = x;
    x = y, y = (t - LLL(a / b) * y) % mod;
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> p[i] >> a[i];

    LL x = 0, lcm = 1;
    for (int i = 1; i <= n; ++i)
    {
        LL t, q, gcd = __gcd(lcm, p[i]);
        Exgcd(t, q, lcm, p[i], (a[i] - x + p[i]) % p[i], lcm / gcd * p[i]);
        x = (x + (LLL)lcm * t) % (lcm / gcd * p[i]);
        lcm *= p[i] / gcd;
    }
    cout << (x + lcm) % lcm << endl;
    return 0;
}
