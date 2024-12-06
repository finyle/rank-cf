#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()

const char nl = '\n';
typedef long long ll;
typedef long double ld;

using namespace std;

const ll inf = 1e15;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (auto &x: a) cin >> x;

    vector<int> d(n);
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        p--;

        g[p].push_back(i);
        d[i] = d[p] + 1;
    }

    vector<ll> b(n); // b[v] = sum(a[u]) - a[v]
    for (int v = 0; v < n; v++) {
        if (g[v].empty()) {
            b[v] = inf;
        } else {
            b[v] = -a[v];

            for (int u: g[v]) {
                b[v] += a[u];
            }
        }
    }

    ll ans = 0;
    for (int v = n - 1; v >= 0; v--) {
        queue<int> q;

        q.push(v);
        while (!q.empty()) {
            int i = q.front();
            q.pop();

            for (int u: g[i]) {
                ll delta = min(-b[v], b[u]);

                if (delta > 0) {
                    b[v] += delta;
                    b[u] -= delta;
                    ans += delta * (d[u] - d[v]);
                }

                q.push(u);
            }
        }
    }

    cout << ans << nl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}