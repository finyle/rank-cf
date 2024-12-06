#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;

mt19937_64 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

int n;
unsigned long long r[MAXN], hsh[MAXN], totr;
string s[MAXN];
vector<pair<int, int>> ans;

bool done[MAXN];
bool solve(vector<int> grp) {
    int pr = -1, pl = -1;
    vector<int> lft, rht;
    for (int i : grp) {
        if (s[i][i] == '0' || done[i] || hsh[i] == totr) {
            continue;
        }
        rht.clear();
        for (int j : grp) {
            if (s[j][i] == '0') {
                lft.push_back(j);
            } else {
                rht.push_back(j);
            }
        }
        if (!lft.empty()) {
            pr = i;
            break;
        }
    }
    if (pr == -1) {
        vector<int> dv, zero, one;
        for (int i : grp) {
            if (done[i]) {
                dv.push_back(i);
            } else if (s[i][i] == '0') {
                zero.push_back(i);
            } else {
                one.push_back(i);
            }
        }
        for (int i = 1; i < dv.size(); i++) {
            ans.push_back({dv[i - 1], dv[i]});
        }
        if (one.empty() && zero.empty()) {
            return 1;
        }
        if (one.size() >= zero.size()) {
            return 0;
        }
        if (one.empty()) {
            if (zero.size() >= 2 || !dv.empty()) {
                return 0;
            }
            return 1;
        }
        for (int i = 0; i < one.size(); i++) {
            ans.push_back({zero[i], one[i]});
            ans.push_back({one[i], zero[i + 1]});
        }
        for (int i = one.size() + 1; i < zero.size(); i++) {
            ans.push_back({one[0], zero[i]});
        }
        if (!dv.empty()) {
            ans.push_back({one[0], dv[0]});
        }
        return 1;
    }
    for (int i : lft) {
        if (s[i][i] == '0' || done[i] || ((hsh[i] ^ hsh[pr]) != totr)) {
            continue;
        }
        vector<int> trht;
        for (int j : grp) {
            if (s[j][i] == '0') {
                trht.push_back(j);
            }
        }
        if (trht == rht) {
            pl = i;
            break;
        }
    }
    if (pl == -1) {
        return 0;
    }
    for (int i : lft) {
        for (int j : rht) {
            if (j == pr) {
                continue;
            }
            if (s[i][j] != s[pr][j]) {
                return 0;
            }
        }
    }
    for (int i : rht) {
        for (int j : lft) {
            if (j == pl) {
                continue;
            }
            if (s[i][j] != s[pl][j]) {
                return 0;
            }
        }
    }
    ans.push_back({pl, pr});
    done[pl] = done[pr] = 1;
    return solve(lft) && solve(rht);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    for (int i = 0; i < n; i++) {
        r[i] = rnd();
        totr ^= r[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (s[i][j] == '1') {
                hsh[j] ^= r[i];
            }
        }
    }
    bool pos = 1;
    for (int i = 0; i < n; i++) {
        if (s[i][i] == '1') {
            continue;
        }
        for (int j = 0; j < n; j++) {
            if (s[j][i] == '1') {
                pos = 0;
                break;
            }
        }
    }
    if (!pos) {
        cout << "NO\n";
        return 0;
    }
    vector<int> v(n, 0);
    iota(v.begin(), v.end(), 0);
    if (!solve(v)) {
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    for (auto [u, v] : ans) {
        cout << u + 1 << ' ' << v + 1 << '\n';
    }
}

//4
//1100
//0101
//0011
//0101
