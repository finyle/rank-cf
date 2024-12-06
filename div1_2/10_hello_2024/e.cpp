#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF = 1000000005;
const int MAXN = 200005;
const int MOD = 998244353;

ll fact[MAXN * 2], ifact[MAXN * 2];
int t;
int n;
int f[MAXN * 2], d[MAXN * 2];

inline ll ncr(int n, int r) {
    if (r < 0 || n < r) {
        return 0;
    }
    return fact[n] * ifact[r] % MOD * ifact[n - r] % MOD;
}
// count number of a_1 + a_2 + ... + a_n = x
inline ll starbar(int n, int x) {
    if (n == 0 && x == 0) {
        return 1;
    }
    return ncr(x + n - 1, x);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    fact[0] = 1;
    for (int i = 1; i < MAXN * 2; i++) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    ifact[0] = ifact[1] = 1;
    for (int i = 2; i < MAXN * 2; i++) {
        ifact[i] = MOD - MOD / i * ifact[MOD % i] % MOD;
    }
    for (int i = 2; i < MAXN * 2; i++) {
        ifact[i] = ifact[i - 1] * ifact[i] % MOD;
    }
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 0; i < n * 2 + 5; i++) {
            f[i] = 0;
        }
        n++;
        for (int i = 1; i < n; i++) {
            int s; cin >> s;
            f[s + n]++;
        }
        f[n]++;
        int mn = INF, mx = -INF;
        for (int i = 0; i <= 2 * n; i++) {
            if (f[i]) {
                mn = min(mn, i);
                mx = max(mx, i);
            }
        }
        bool bad = 0;
        for (int i = mn; i <= mx; i++) {
            if (!f[i]) {
                bad = 1;
                break;
            }
        }
        if (bad || mn == mx) {
            cout << 0 << '\n';
            continue;
        }
        ll ans = 0;
        for (int x = mx; x >= mn; x--) {
            d[mx - 1] = f[mx] + (mx > n) - (mx == x);
            for (int i = mx - 2; i >= mn - 1; i--) {
                d[i] = f[i + 1] - d[i + 1] + (i >= x) + (i >= n);
            }
            if (d[mn - 1] != 0) {
                continue;
            }
            ll res = 1;
            for (int i = mx - 1; i >= mn; i--) {
                res = res * starbar(d[i], f[i] - d[i]) % MOD;
            }
            ans += res;
            if (ans >= MOD) {
                ans -= MOD;
            }
        }
        cout << ans << '\n';
    }
}

//5
//1
//0
//1
//1
//3
//-1 1 2
//5
//-1 0 0 1 1
//5
//-4 -3 -3 -2 -1
