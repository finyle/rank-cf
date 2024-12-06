#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    cout << "? aa" << endl;
    int p, v[10];
    cin >> p; p--;
    cout << "? zzzzzzzzzz" << endl;
    int hsh, hsho;
    ll nom = 0, cnt = 1;
    cin >> hsh;
    hsho = hsh;
    hsh++;
    for (int i = 0; i < 10; i++) {
        nom += 26 * cnt;
        cnt *= p;
        v[i] = 26 - (hsh % p);
        hsh /= p;
    }
    string s;
    cnt = 1;
    ll ch = 0;
    for (int i = 0; i < 10; i++) {
        if (v[i] < 1) {
            v[i] = 26;
            v[i + 1]--;
        }
        ch += cnt * v[i];
        cnt *= p;
        s += 'a' + (v[i] - 1);
    }
    cout << "? " << s << endl;
    int ans;
    cin >> ans;
    cout << "! " << p << ' ' << ans + nom - ch - hsho << endl;
}

int32_t main() {
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}