#include <iostream>
#include <vector>
#include <map>
using namespace std;

#define pii pair<int, int>

int n;
vector<vector<int>> adj;
vector<pii> edges;
map<pii, int> mp;

vector<vector<int>> dp;
vector<vector<int>> from;
vector<int> miss;

void dfs(int e) {
    if (dp[0][e] >= 0 || dp[1][e] >= 0) return;
    int p = edges[e].first, v = edges[e].second;
    dp[0][e] = 0, dp[1][e] = 1;
    if (miss[v] < 0) {
        for (int u : adj[v]) {
            if (u == p) continue;
            int ne = mp[{v, u}];
            dfs(ne);
            from[0][v] += max(dp[1][ne], dp[0][ne]);
            from[1][v] += dp[0][ne];
        }
        miss[v] = p;
    }
    if (miss[v] != p && miss[v] != n) {
        int ne = mp[{v, miss[v]}];
        dfs(ne);
        from[0][v] += max(dp[1][ne], dp[0][ne]);
        from[1][v] += dp[0][ne];
        miss[v] = n;
    }
    if (miss[v] == n) {
        int nne = mp[{v, p}];
        dp[0][e] += from[0][v] - max(dp[1][nne], dp[0][nne]);
        dp[1][e] += from[1][v] - dp[0][nne];
    } else if (miss[v] == p) {
        dp[0][e] += from[0][v];
        dp[1][e] += from[1][v];
    }
}

void solve() {
    cin >> n;
    adj.clear(), edges.clear();
    adj.resize(n), edges.resize(2 * n - 2);
    for (int i = 0; i < n - 1; ++i) {
        int a, b; cin >> a >> b; --a, --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        edges[2 * i] = {a, b};
        edges[2 * i + 1] = {b, a};
        mp[{a, b}] = 2 * i;
        mp[{b, a}] = 2 * i + 1;
    }
    from = vector<vector<int>>(2, vector<int>(n));
    miss = vector<int>(n, -1);
    dp = vector<vector<int>>(2, vector<int>(2 * n - 2, -1));
    for (int i = 0; i < 2 * n - 2; ++i) dfs(i);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (adj[i].size() != 1) continue;
        int e = mp[{i, adj[i][0]}];
        ans = max(ans, 1 + max(dp[0][e], dp[1][e]));
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int i = 0; i < t; ++i) solve();
    return 0;
}

//4
//5
//1 2
//1 3
//2 4
//2 5
//5
//1 2
//2 3
//3 4
//4 5
//6
//1 2
//1 3
//1 4
//1 5
//1 6
//10
//9 3
//8 1
//10 6
//8 5
//7 8
//4 6
//1 3
//10 1
//2 7
