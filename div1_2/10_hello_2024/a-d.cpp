
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int a, b; cin >> a >> b;
        if ((a + b) % 2 == 0) {
            cout << "Bob\n";
        } else {
            cout << "Alice\n";
        }
    }
}

int t;
int n;
string s;

int main() {
    cin >> t;
    while (t--) {
        cin >> n;
        cin >> s;
        int sm = 0;
        for (int i = 0; i < n; i++) {
            sm += s[i] == '+' ? 1 : -1;
        }
        cout << abs(sm) << '\n';
    }
}

const int INF = 1000000005;
const int MAXN = 200005;

int t;
int n;
int a[MAXN];

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> t;
    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        int t1 = INF, t2 = INF;
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            if (t1 > t2) {
                swap(t1, t2);
            }
            if (a[i] <= t1) {
                t1 = a[i];
            } else if (a[i] <= t2) {
                t2 = a[i];
            } else {
                t1 = a[i];
                ans++;
            }
        }
        cout << ans << '\n';
    }
}

const int MAXN = 200005;

int n;
int a[MAXN];
int prv[MAXN],nxt[MAXN];
bool in[MAXN];

bool good(int i) {
    if (i < 1 || i > n) {
        return 0;
    }
    return a[prv[i]] == a[i] - 1 || a[nxt[i]] == a[i] - 1;
}
int main(){
    ios::sync_with_stdio(0), cin.tie(0);
    int t; cin >> t;
    while (t--) {
        cin >> n;
        priority_queue<pair<int, int>> pq;
        for (int i = 1; i <= n; i++) {
            prv[i] = i - 1;
            nxt[i] = i + 1;
            in[i] = 0;
            cin >> a[i];
        }
        a[n + 1] = a[0] = -2;
        for (int i = 1; i <= n; i++) {
            if (good(i)) {
                in[i] = 1;
                pq.push({a[i], i});
            }
        }
        while (!pq.empty()) {
            auto [_, i] = pq.top(); pq.pop();
            nxt[prv[i]] = nxt[i];
            prv[nxt[i]] = prv[i];
            if (!in[prv[i]] && good(prv[i])) {
                in[prv[i]]=1;
                pq.push({a[prv[i]], prv[i]});
            }
            if (!in[nxt[i]] && good(nxt[i])) {
                in[nxt[i]]=1;
                pq.push({a[nxt[i]], nxt[i]});
            }
        }
        int mn = n, bad = 0;
        for (int i = 1; i <= n; i++) {
            bad += !in[i];
            mn = min(a[i], mn);
        }
        if (bad == 1 && mn == 0) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}