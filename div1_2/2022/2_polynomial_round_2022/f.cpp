// Author: Little09
// Problem: F. Magician and Pigs

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define mem(x) memset(x, 0, sizeof(x))
#define endl "\n"
#define printYes cout << "Yes\n"
#define printYES cout << "YES\n"
#define printNo cout << "No\n"
#define printNO cout << "NO\n"
#define lowbit(x) ((x) & (-(x)))
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define fi first
#define se second

const ll inf = 1000000000000000000;
// const ll inf=1000000000;
const ll mod = 998244353;
// const ll mod=1000000007;

const int N = 800005;
int n, m;
ll a[N], b[N], c[N], cnt, s[N], d[N], cntd;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    ll maxs = 1e9, sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] != 3) cin >> b[i];
        if (a[i] == 2) sum += b[i];
        sum = min(sum, maxs);
        if (a[i] == 3) b[i] = sum, sum = sum * 2;
        sum = min(sum, maxs);
    }
    sum = 0;
    ll res = 1, ans = 0;
    for (int i = n; i >= 1; i--) {
        if (a[i] == 2)
            sum += b[i];
        else if (a[i] == 3) {
            if (b[i] == maxs) continue;
            if (b[i] == 0) {
                res = res * 2 % mod;
                continue;
            }
            c[++cnt] = b[i];
        } else {
            b[i] -= sum;
            if (b[i] <= 0) continue;
            ll su = 0, r = b[i];
            for (int j = 1; j <= cnt; j++) {
                if (r > c[j]) {
                    su = (su + (1ll << (cnt - j))) % mod;
                    r -= c[j];
                }
            }
            su = (su + 1) % mod;
            ans = (ans + su * res) % mod;
        }
    }
    cout << ans;
    return 0;
}