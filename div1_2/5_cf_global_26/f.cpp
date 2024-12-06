
#include <iostream>
#include <vector>
#include <cstring>
#include <assert.h>
#include <set>
using namespace std;

#define ll long long

const int INF = 998244353;
// const int BOUND = 1e9;

void solve() {
    int n; cin >> n;
    int BOUND; cin >> BOUND;
    string s; cin >> s;
    s = "P" + s + "S";
    vector<ll> b(n + 2);
    for (int i = 0; i < n; ++i) cin >> b[i + 1];
    ll ans = 0;
    set<ll> done;
    for (int i = 0; i < n + 1; ++i) {
        ll sum = b[i] + b[i + 1];
        if (done.count(sum)) continue;
        int dp[n + 2][2];
        for (int j = 0; j < n + 2; ++j) for (int k = 0; k < 2; ++k) dp[j][k] = -1;
        // ["P", "S"]
        dp[0][0] = 1;
        for (int j = 1; j < n + 2; ++j) {
            bool tr[2]; tr[0] = tr[1] = true;
            if (s[j] == 'P') tr[1] = false;
            else if (s[j] == 'S') tr[0] = false;
            if (abs(b[j] - b[j - 1]) <= BOUND) {
                for (int k = 0; k < 2; ++k)
                    if (dp[j - 1][k] > -1 && tr[k]) dp[j][k] = dp[j - 1][k];
            }
            if (dp[j - 1][0] > -1 && tr[1] && sum == b[j] + b[j - 1]) {
                // "P" -> "S":
                if (dp[j][1] < 0) dp[j][1] = 0;
                dp[j][1] = (dp[j][1] + dp[j - 1][0]) % INF;
            }
            if (dp[j - 1][1] > -1 && tr[0]) {
                // "S" -> "P":
                ll add = b[j] + b[j - 1] - sum;
                ll large = max(abs(add / 2), abs(add - add / 2));
                if (large <= BOUND) {
                    if (dp[j][0] < 0) dp[j][0] = 0;
                    dp[j][0] = (dp[j][0] + dp[j - 1][1]) % INF;
                }
            }
        }
        if (dp[n + 1][1] < 0) continue;
        ans = (ans + dp[n + 1][1]) % INF;
        done.insert(sum);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int i = 0; i < t; ++i) solve();
    return 0;
}

//6
//4 10
//PSPP
//1 9 8 10
//4 1000000000
//????
//1 1 1 4000000000
//8 1000000000
//?P?SSP?P
//-857095623 -1424391899 -851974476 673437144 471253851 -543483033 364945701 -178537332
//4 7
//PPSS
//4 2 1 3
//9 20
//?????????
//1 2 3 4 5 6 7 8 9
//3 1000000000
//P??
//-145463248 -974068460 -1287458396
