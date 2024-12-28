#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

template <typename T>
class fenwick {
public:
    vector<T> fenw;
    int n;

    fenwick(int _n) : n(_n) {
        fenw.resize(n);
    }

    void modify(int x, T v) {
        while (x < n) {
            fenw[x] += v;
            x |= (x + 1);
        }
    }

    T get(int x) {
        T v{};
        while (x >= 0) {
            v += fenw[x];
            x = (x & (x + 1)) - 1;
        }
        return v;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int tt;
    cin >> tt;
    while (tt--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        vector<int> b(n);
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        int m;
        cin >> m;
        vector<int> x(m);
        for (int i = 0; i < m; i++) {
            cin >> x[i];
        }
        bool ok = true;
        vector<pair<int, int>> need;
        for (int i = 0; i < n; i++) {
            if (a[i] < b[i]) {
                ok = false;
                break;
            }
            need.emplace_back(b[i], i);
        }
        if (!ok) {
            cout << "NO" << '\n';
            continue;
        }
        sort(need.begin(), need.end());
        sort(x.rbegin(), x.rend());
        int ptr = 0;
        int last_val = -1;
        int last_pos = -1;
        vector<int> to_put;
        fenwick<int> fenw(n);
        for (int id = n - 1; id >= 0; id--) {
            if (id < n - 1 && need[id].first != need[id + 1].first) {
                for (int xx : to_put) {
                    fenw.modify(xx, +1);
                }
                to_put.clear();
            }
            int i = need[id].second;
            bool use = false;
            if (a[i] > b[i]) {
                use = true;
                if (last_val == b[i]) {
                    assert(last_pos > i);
                    if (fenw.get(last_pos - 1) - fenw.get(i) == 0) {
                        use = false;
                    }
                }
            }
            if (use) {
                while (ptr < m && x[ptr] != b[i]) {
                    ptr += 1;
                }
                if (ptr < m && x[ptr] == b[i]) {
                    ptr += 1;
                } else {
                    ok = false;
                    break;
                }
                last_val = b[i];
                last_pos = i;
            }
            to_put.push_back(i);
        }
        cout << (ok ? "YES" : "NO") << '\n';
    }
    return 0;
}