#include <iostream>
using namespace std;
int main(){
    int T; cin >> T;

    while (T--) {

        int n; cin >> n;

        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        if (a[0] == a[n - 1]) {
            cout << "NO" << "\n";
        }
        else {
            cout << "YES" << "\n";
            string s(n, 'R');
            s[1] = 'B';
            cout << s << "\n";

        }


    }
}

// ************************************
#include <iostream>
using namespace std;

#define ll long long

void solve() {
    ll n; cin >> n;
    n = n - n % 10 + (n % 10 + 1) % 10;
    while (n > 9) {
        if (n % 10 == 0) {
            cout << "NO\n";
            return;
        }
        n /= 10;
    }
    cout << (n == 1 ? "YES\n" : "NO\n");
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; cin >> t;
    for (int i = 0; i < t; ++i) solve();
    return 0;
}

// **************************************************
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

#define ll long long

const ll MAX_N = 400001;
const ll MOD = 998244353;

vector<ll> p2(MAX_N);

void solve() {
    int n; cin >> n;
    vector<int> arr(n); for (int i = 0; i < n; ++i) cin >> arr[i];
    ll sum = 0, mn = 0, ans = 0, abses = 0;
    for (int i = 0; i < n; ++i) sum += arr[i], mn = min(mn, sum);
    if (mn == 0) {
        cout << p2[n] << '\n';
        return;
    }
    sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += arr[i];
        if (sum == mn) {
            ans = (ans + p2[n - i - 1 + abses]) % MOD;
        }
        if (sum >= 0) ++abses;
    }
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    p2[0] = 1;
    for (int i = 1; i < MAX_N; ++i) p2[i] = 2 * p2[i - 1] % MOD;
    int t; cin >> t;
    for (int i = 0; i < t; ++i) solve();
    return 0;
}

// ************************************

#include <iostream>
#include <vector>
#include <climits>
#include <set>
using namespace std;

#define ll long long

vector<int> z_function(string s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for(int i = 1; i < n; ++i) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    return z;
}

void solve() {
    int n; // cin >> n;
    string s; cin >> s;
    n = s.length();
    vector<int> nona(n, n);
    for (int i = n - 1; i >= 0; --i) {
        if (s[i] != 'a') nona[i] = i;
        else if (i + 1 < n) nona[i] = nona[i + 1];
    }
    if (nona[0] == n) {
        cout << n - 1 << '\n';
        return;
    }
    string s2 = "";
    int i1 = nona[0];
    for (int i = i1; i < n; ++i) s2 += s[i];
    vector<int> z = z_function(s2);
    ll ans = 0;
    for (int len = 1; i1 + len <= n; ++len) {
        int cur = i1 + len;
        int mn = i1;
        bool works = true;
        while (cur < n) {
            if (nona[cur] == n) break;
            int bt = nona[cur] - cur;
            mn = min(mn, bt);
            cur += bt;
            if (z[cur - i1] < len) {
                works = false;
                break;
            }
            cur += len;
        }
        if (works) ans += mn + 1;
    }
    cout << ans << '\n';
}

int main() {
    int t; cin >> t;
    for (int i = 0; i < t; ++i) solve();
    return 0;
}