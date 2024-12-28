#include <bits/stdc++.h>

using namespace std;

int n, k;
vector<vector<bool>> memo;
string res;
vector<int> cnt;
string s;

bool rec(int i, int cur) {
    if (i == k) {
        if (cur == 0) {
            return true;
        }
        return false;
    }
    if (memo[i][cur]) return false;
    memo[i][cur] = true;
    for (int c = 0; c < 2; ++c) {
        int q = cur;
        if (c == 0) q += cnt[i];
        else q += n - cnt[i];
        if ((q & 1) == s[i] - '0') {
            if (rec(i + 1, q / 2)) {
                res += char(c + '0');
                return true;
            }
        }
    }
    return false;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int tests;
    cin >> tests;
    while (tests--) {
        cin >> n >> k;
        cin >> s;
        reverse(s.begin(), s.end());
        cnt = vector<int>(k);
        for (int i = 0; i < n; ++i) {
            string t;
            cin >> t;
            reverse(t.begin(), t.end());
            for (int j = 0; j < k; ++j) cnt[j] += t[j] - '0';
        }
        memo = vector<vector<bool>>(k, vector<bool>(n, false));
        res = "";
        rec(0, 0);
        if (res.empty()) cout << "-1\n";
        else cout << res << '\n';
    }
}