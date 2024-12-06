#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int MAX = 2e6 + 5, MOD = 998244353;

ll fact[MAX], ifact[MAX];

ll bpow(ll a, int p){
    ll ans = 1;

    for (;p; p /= 2, a = (a * a) % MOD)
        if (p & 1)
            ans = (ans * a) % MOD;

    return ans;
}
ll ncr(int n, int r){
    if (n < 0)
        return 0;
    if (r > n)
        return 0;

    return fact[n] * ifact[r] % MOD * ifact[n - r] % MOD;
}
void solve(){
    int l, n;
    cin >> l >> n;

    ll all_even = 0;

    for (int s = 0; s <= l; s += 2){
        all_even += 2 * ncr(s / 2 + n - 1, n - 1) % MOD * ncr(l - s - n, n) % MOD;
        all_even %= MOD;
    }
    cout << (2 * ncr(l, 2 * n) % MOD - all_even + MOD) % MOD << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    for (int i = 0; i < MAX; i++)
        fact[i] = !i ? 1 : fact[i - 1] * i % MOD;

    for (int i = MAX - 1; i >= 0; i--)
        ifact[i] = (i == MAX - 1) ? bpow(fact[MAX - 1], MOD - 2) : ifact[i + 1] * (i + 1) % MOD;

    int tc;
    cin >> tc;

    while (tc--)
        solve();
}