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
        vector<int> r1(n), c1(n), r2(n), c2(n);
        for (int i = 0; i < n; i++) {
            cin >> r1[i] >> c1[i] >> r2[i] >> c2[i];
            assert(1 <= r1[i] && r1[i] <= r2[i] && r2[i] <= 2 && c1[i] <= c2[i]);
            --c1[i];
        }
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int i, int j) {
            return c1[i] < c1[j];
        });
        set<pair<int, int>> s;
        int ans = 0;
        int p1 = -1;
        int p2 = -1;
        for (int i : order) {
            if (r1[i] == 1 && r2[i] == 2) {
                if (p1 >= c2[i]) {
                    r1[i] = 2;
                }
                if (p2 >= c2[i]) {
                    r2[i] = 1;
                }
                if (r1[i] > r2[i]) {
                    continue;
                }
            }
            if (r1[i] == 1 && r2[i] == 2) {
                while (!s.empty()) {
                    auto it = prev(s.end());
                    if (it->first >= c1[i]) {
                        c2[it->second] = c1[i];
                        s.erase(it);
                    } else {
                        break;
                    }
                }
                ans += (c2[i] - max(c1[i], p1)) + (c2[i] - max(c1[i], p2));
                p1 = p2 = c2[i];
                s.emplace(c2[i], i);
                continue;
            }
            assert(r1[i] == r2[i]);
            if (r1[i] == 1) {
                c1[i] = max(c1[i], p1);
                p1 = max(p1, c2[i]);
            } else {
                c1[i] = max(c1[i], p2);
                p2 = max(p2, c2[i]);
            }
            if (c1[i] < c2[i]) {
                ans += c2[i] - c1[i];
                s.emplace(c2[i], i);
            }
        }
        cout << ans << '\n';
        for (int i = 0; i < n; i++) {
            ++c1[i];
            if (r1[i] <= r2[i] && c1[i] <= c2[i]) {
                cout << r1[i] << " " << c1[i] << " " << r2[i] << " " << c2[i] << '\n';
            } else {
                cout << "0 0 0 0" << '\n';
            }
        }
    }
    return 0;
}

//8
//5
//1 2 2 4
//2 4 2 8
//1 4 2 7
//1 2 1 2
//1 9 1 10
//2
//1 1 1 10
//1 5 1 15
//2
//1 1 1 10
//1 1 1 10
//5
//1 3 1 7
//1 3 1 8
//1 1 1 4
//1 2 1 7
//1 10 1 11
//2
//1 1 2 10
//1 5 1 8
//2
//1 5 2 10
//1 2 1 7
//2
//1 5 2 10
//2 2 2 15
//5
//2 6 2 7
//1 4 2 5
//1 5 1 9
//1 7 2 10
//1 2 1 6
