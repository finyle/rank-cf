#include<bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tests;
    cin >> tests;
    while (tests--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> a(n, vector<int>(m));
        for (auto &i: a) {
            for (auto &j: i) cin >> j;
        }
        if (n * m == 1) cout << "-1\n";
        else {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    cout << a[(i + 1) % n][(j + 1) % m] << ' ';
                }
                cout << '\n';
            }
        }
    }
}

// ********************
#include<bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    for (int i = 0; i < s.size() && s[i] == '0'; ++i) {
        if (t[i] != '0') {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

int main() {
    int t;
    cin >> t;
    while (t--) solve();
}

// *******************************
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tests;
    cin >> tests;
    while (tests--) {
        int n;
        ll x;
        cin >> n >> x;
        vector<ll> a(n + 1);
        for (int i = 1; i <= n; ++i) cin >> a[i];
        partial_sum(a.begin() + 1, a.end(), a.begin() + 1);
        vector<int> dp(n + 2);
        for (int i = n - 1; i >= 0; --i) {
            int q = upper_bound(a.begin(), a.end(), a[i] + x) - a.begin();
            dp[i] = dp[q] + q - i - 1;
        }
        cout << accumulate(dp.begin(), dp.end(), 0ll) << '\n';
    }
}

// *********************************
#include<bits/stdc++.h>
using namespace std;

int main() {
    int tests;
    cin >> tests;
    while (tests--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (auto& i : a) cin >> i;
        vector<int> pos(n);
        iota(pos.begin(), pos.end(), 0);
        vector<pair<int, int>> ans;
        for (int i = n - 1; i; --i) {
            vector<int> occ(i, -1);
            for (auto j : pos) {
                if (occ[a[j] % i] != -1) {
                    ans.emplace_back(j, occ[a[j] % i]);
                    pos.erase(find(pos.begin(), pos.end(), j));
                    break;
                }
                occ[a[j] % i] = j;
            }
        }
        reverse(ans.begin(), ans.end());
        cout << "YES\n";
        for (auto [x, y] : ans) cout << x + 1 << ' ' << y + 1 << '\n';
    }
}