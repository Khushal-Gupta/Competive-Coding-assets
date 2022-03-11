#include <bits/stdc++.h>
using namespace std;
#define lli long long int

const lli MOD = 1e9 + 7;

// Addition
lli add(lli a, lli b)
{
    a += b;
    while (a < 0)
        a += MOD;
    a %= MOD;
    return a;
}

// Multiplication
lli mul(lli a, lli b)
{
    return (a * b) % MOD;
}

// Fast method to get a^b,  O(log b)
lli binpower(lli a, lli b)
{
    lli z = 1;
    while (b)
    {
        if (b & 1)
            z = mul(z, a);
        a = mul(a, a);
        b /= 2;
    }
    return z;
}

// Modulo inverse of b
lli modinv(lli b)
{
    return binpower(b, MOD - 2);
}

const lli mx = 100000;
vector<lli> fact(mx, 1), inv(mx, 1), invfact(mx, 1);

void precalculate()
{
    // Calculates everthing in O(mx)
    for (int i = 2; i < fact.size(); i++)
    {
        fact[i] = mul(fact[i - 1], i);
        inv[i] = add(MOD, -mul(MOD / i, inv[MOD % i]));
        invfact[i] = mul(invfact[i - 1], inv[i]);
    }
}
