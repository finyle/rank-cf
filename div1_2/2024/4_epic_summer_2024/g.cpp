#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()

const char nl = '\n';
typedef long long ll;
typedef long double ld;

using namespace std;

array<vector<int>, 2> get_l_and_r(vector<int> &p) {
    int n = p.size();

    vector<int> l(n), r(n);

    stack<int> s;
    for (int i = 0; i < n; i++) {
        while (!s.empty() && p[s.top()] < p[i]) s.pop();

        if (s.empty()) l[i] = -1;
        else l[i] = s.top();

        s.push(i);
    }

    s = {};
    for (int i = n - 1; i >= 0; i--) {
        while (!s.empty() && p[s.top()] < p[i]) s.pop();

        if (s.empty()) r[i] = n;
        else r[i] = s.top();

        s.push(i);
    }

    return {l, r};
}

int ans_l_edge(array<int, 2> d, array<int, 2> e) {
    return d[0] + 1 + max(d[1], e[0]);
}

int ans_r_edge(array<int, 2> d, array<int, 2> e) {
    return e[1] + 1 + max(d[1], e[0]);
}

array<int, 2> add_l_edge(array<int, 2> d, array<int, 2> e) {
    return {max({d[0], d[1] + 1, e[0] + 1}), e[1]};
}

array<int, 2> add_r_edge(array<int, 2> d, array<int, 2> e) {
    return {d[0], max({d[1] + 1, e[0] + 1, e[1]})};
}

vector<array<int, 2>> process_dp(vector<array<int, 2>> &dp) {
    array<int, 2> max_a = {-1, -1}, max_b = {-1, -1}, max_s = {-1, -1};

    for (auto [a, b]: dp) {
        if (a > max_a[0] || (a == max_a[0] && b > max_a[1])) {
            max_a = {a, b};
        }

        if (b > max_b[1] || (b == max_b[1] && a > max_b[0])) {
            max_b = {a, b};
        }

        if (a + b > max_s[0] + max_s[1]) {
            max_s = {a, b};
        }
    }

    return {max_a, max_b, max_s};
}

void add_to_map(map<array<int, 2>, int> &dp_ind, int &len_dp, array<int, 2> a) {
    if (!dp_ind.count(a)) {
        dp_ind[a] = len_dp++;
    }
}

void solve() {
    int n;
    cin >> n;

    vector<int> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];

    string s;
    cin >> s;

    auto [l, r] = get_l_and_r(p);

    for (int i = 0; i < n; i++) {
        if (p[i] == n) continue;

        if (l[i] == -1 && s[i] == 'L') {
            cout << -1 << nl;
            return;
        }

        if (r[i] == n && s[i] == 'R') {
            cout << -1 << nl;
            return;
        }
    }

    int ans = 0;

    vector<int> q(n + 1);
    for (int i = 0; i < n; i++) {
        q[p[i]] = i;
    }

    int len_dp = 0;
    map<array<int, 2>, int> dp_ind;

    for (int x = 1; x <= n; x++) {
        int i = q[x];
        int tl = l[i], tr = r[i];

        add_to_map(dp_ind, len_dp, {tl, i});
        add_to_map(dp_ind, len_dp, {i, tr});
        add_to_map(dp_ind, len_dp, {tl, tr});
    }

    vector<vector<array<int, 2>>> dp(len_dp, {{0, 0}});
    for (int x = 1; x <= n; x++) {
        int i = q[x];
        int tl = l[i], tr = r[i];

        int ind_l = dp_ind[{tl, i}];
        int ind_r = dp_ind[{i, tr}];
        int ind_c = dp_ind[{tl, tr}];

        for (auto const &d: dp[ind_l]) {
            for (auto const &e: dp[ind_r]) {
                ans = max(ans, d[1] + e[0]);

                if (tl >= 0 && s[i] != 'R') {
                    ans = max(ans, ans_l_edge(d, e));
                    dp[ind_c].push_back(add_l_edge(d, e));
                }

                if (tr <= n - 1 && s[i] != 'L') {
                    ans = max(ans, ans_r_edge(d, e));
                    dp[ind_c].push_back(add_r_edge(d, e));
                }
            }
        }

        dp[ind_c] = process_dp(dp[ind_c]);
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

//8
//5
//2 1 4 3 5
//R?RL?
//2
//1 2
//LR
//3
//3 1 2
//L?R
//7
//5 3 1 6 4 2 7
//?R?R?R?
//5
//5 2 1 3 4
//?????
//6
//6 2 3 4 5 1
//?LLRLL
//8
//1 7 5 6 2 8 4 3
//?R??????
//12
//6 10 7 1 8 5 12 2 11 3 4 9
//????????????
