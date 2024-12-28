#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()

const char nl = '\n';
typedef long long ll;
typedef long double ld;

using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    cout << 1 + (n - 1) * k << nl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}

// ***********************************
#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()

const char nl = '\n';
typedef long long ll;
typedef long double ld;

using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    ll pref_max = 0, s = 0, mx = 0;
    for (int i = 0; i < n; i++) {
        pref_max = max(pref_max, (ll) a[i]);

        ll d = pref_max - a[i];
        s += d;
        mx = max(mx, d);
    }

    cout << s + mx << nl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}

// *********************************************
#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()

const char nl = '\n';
typedef long long ll;
typedef long double ld;

using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> h(n);
    for (auto &x: h) cin >> x;

    int ans = h[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        ans = max(ans + 1, h[i]);
    }

    cout << ans << nl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;
    while (T--) solve();
}

// ******************************************************
#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()

const char nl = '\n';
typedef long long ll;
typedef long double ld;

using namespace std;

const int inf = 1e9;

void solve() {
    vector<int> a;
    {
        int n;
        cin >> n;

        map<int, int> cnt;
        while (n--) {
            int x;
            cin >> x;
            cnt[x]++;
        }

        for (auto const &[k, v]: cnt) {
            a.push_back(v);
        }
    }

    int n = a.size();
    vector<int> dp(n + 1, inf);
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        vector<int> ndp = dp;

        for (int k = 1; k <= n; k++) {
            int nv = dp[k - 1] + a[i - 1];

            if (nv <= i - k) {
                ndp[k] = min(ndp[k], nv);
            }
        }

        dp = ndp;
    }

    int ans = n;
    while (dp[ans] >= inf) ans--;
    cout << n - ans << nl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;
    while (T--) solve();
}