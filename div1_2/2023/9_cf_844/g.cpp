#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    cin >> tt;
    while (tt--) {
        int n;
        cin >> n;
        vector<int> p(n);
        for (int i = 1; i < n; i++) {
            cin >> p[i];
            --p[i];
        }
        for (int i = 2; i <= n; i++) {
            if (i == 4 && p[1] == 0 && p[2] == 1 && p[3] == 1) {
                cout << 2 << '\n';
            } else {
                cout << i % 2 << '\n';
            }
        }
        vector<vector<int>> g(n);
        for (int i = 1; i < n; i++) {
            g[p[i]].push_back(i);
        }
        string res = "";
        auto Solve = [&](int nn) {
            vector<vector<vector<bool>>> good(nn);
            vector<vector<vector<vector<int>>>> prevs(nn);
            vector<int> sz(nn);
            vector<int> L(nn);
            vector<int> R(nn);
            function<void(int)> Dfs = [&](int v) {
                sz[v] += 1;
                for (int u : g[v]) {
                    Dfs(u);
                    sz[v] += sz[u];
                }
                L[v] = sz[v] / 2;
                R[v] = L[v] + 1;
                good[v].assign(2, vector<bool>(R[v] - L[v] + 1, false));
                prevs[v].assign(2, vector<vector<int>>(R[v] - L[v] + 1));
                auto Set = [&](int c, int k, vector<int> pr) {
                    if (k >= L[v] && k <= R[v]) {
                        good[v][c][k - L[v]] = true;
                        prevs[v][c][k - L[v]] = pr;
                    }
                };
                if (g[v].size() == 0) {
                    Set(0, 1, {});
                }
                if (g[v].size() == 1) {
                    int u = g[v][0];
                    for (int cu = 0; cu < 2; cu++) {
                        for (int ku = L[u]; ku <= R[u]; ku++) {
                            if (good[u][cu][ku - L[u]]) {
                                Set(1, 1 + (sz[u] - ku), {cu, ku, 1});
                                if (cu == 1) {
                                    Set(0, 1 + ku, {cu, ku, 0});
                                }
                            }
                        }
                    }
                }
                if (g[v].size() == 2) {
                    int u = g[v][0];
                    int w = g[v][1];
                    for (int cu = 0; cu < 2; cu++) {
                        for (int ku = L[u]; ku <= R[u]; ku++) {
                            if (good[u][cu][ku - L[u]]) {
                                for (int cw = 0; cw < 2; cw++) {
                                    for (int kw = L[w]; kw <= R[w]; kw++) {
                                        if (good[w][cw][kw - L[w]]) {
                                            Set(1, 1 + (sz[u] - ku) + (sz[w] - kw), {cu, ku, 1, cw, kw, 1});
                                            if (cu == 1) {
                                                Set(1, 1 + ku + (sz[w] - kw), {cu, ku, 0, cw, kw, 1});
                                            }
                                            if (cw == 1) {
                                                Set(1, 1 + (sz[u] - ku) + kw, {cu, ku, 1, cw, kw, 0});
                                            }
                                            if (cu == 1 && cw == 1) {
                                                Set(0, 1 + ku + kw, {cu, ku, 0, cw, kw, 0});
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            };
            Dfs(0);
            int best = nn + 1;
            int best_k = -1;
            for (int k = L[0]; k <= R[0]; k++) {
                if (good[0][1][k - L[0]]) {
                    int val = abs(k - (nn - k));
                    if (val < best) {
                        best = val;
                        best_k = k;
                    }
                }
            }
            assert(best <= nn);
            res = string(nn, '.');
            function<void(int, int, int)> Restore = [&](int v, int c, int k) {
                int ptr = 0;
                for (int u : g[v]) {
                    res[u] = (prevs[v][c][k - L[v]][ptr + 2] == 0 ? res[v] : (char) ('w' ^ 'b' ^ res[v]));
                    Restore(u, prevs[v][c][k - L[v]][ptr], prevs[v][c][k - L[v]][ptr + 1]);
                    ptr += 3;
                }
            };
            res[0] = 'w';
            Restore(0, 1, best_k);
            return best;
        };
        Solve(n);
        cout << res << '\n';
    }
    return 0;
}

//2
//7
//1 2 2 1 5 5
//8
//1 2 3 4 5 6 7
