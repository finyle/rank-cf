#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 105;
int t, n, a[MAX_N];
int main() {
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; i++)
            cin >> a[i];
        int max_value = 0;
        for (int i = 1; i <= n; i += 2)
            max_value = max(max_value, a[i]);
        cout << max_value << '\n';
    }
}

// **************************
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1e5 + 5;
int n, b[MAX_N], a[MAX_N];
void solve() {
    cin >> n;
    for (int i = 1; i < n; i++)
        cin >> b[i];
    b[0] = b[n] = 0;
    for (int i = 1; i <= n; i++)
        a[i] = b[i - 1] | b[i];
    bool valid = true;
    for (int i = 1; i < n; i++)
        if ((a[i] & a[i + 1]) != b[i]) {
            valid = false;
            break;
        }
    if (valid) {
        for (int i = 1; i <= n; i++)
            cout << a[i] << ' ';
        cout << '\n';
    } else
        cout << -1 << endl;
}
int main() {
    int t;
    cin >> t;
    while (t--)
        solve();
}

// *************************
#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 2e5 + 5;
int n, a[MAX_N];
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    bool has_odd = false, has_even = false;
    for (int i = 1; i <= n; i++)
        if (a[i] % 2 == 1)
            has_odd = true;
        else
            has_even = true;
    if (has_even && has_odd)
        cout << -1 << '\n';
    else {
        vector<int> operations;
        for (int i = 29; i >= 0; i--)
            operations.push_back(1 << i);
        if (has_even)
            operations.push_back(1);
        cout << operations.size() << '\n';
        for (int x : operations)
            cout << x << ' ';
        cout << '\n';
    }
}
int main() {
    int t;
    cin >> t;
    while (t--)
        solve();
}

// ***************************
using namespace std;
void solve() {
    int n;
    cin >> n;
    if (n < 6) {
        if (n == 1)
            cout << 1 << '\n' << "1" << '\n';
        else if (n == 2)
            cout << 2 << '\n' << "1 2" << '\n';
        else if (n == 3)
            cout << 2 << '\n' << "1 2 2" << '\n';
        else if (n == 4)
            cout << 3 << '\n' << "1 2 2 3" << '\n';
        else if (n == 5)
            cout << 3 << '\n' << "1 2 2 3 3" << '\n';
    } else {
        cout << 4 << '\n';
        for (int i = 1; i <= n; i++)
            cout << i % 4 + 1 << ' ';
        cout << '\n';
    }
}
int main() {
    int t;
    cin >> t;
    while (t--)
        solve();
}