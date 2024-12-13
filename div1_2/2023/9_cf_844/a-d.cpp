#include <bits/stdc++.h>

using namespace std;

struct Sol1 {
    int main() {
        int tt;
        cin >> tt;
        while (tt--) {
            int w, d, h;
            cin >> w >> d >> h;
            int a, b;
            cin >> a >> b;
            int f, g;
            cin >> f >> g;
            int ans = b + abs(a - f) + g;
            ans = min(ans, a + abs(b - g) + f);
            ans = min(ans, (d - b) + abs(a - f) + (d - g));
            ans = min(ans, (w - a) + abs(b - g) + (w - f));
            cout << ans + h << '\n';
        }
        return 0;
    }
};
//5
//55 20 29
//23 10 18 3
//20 10 5
//1 5 2 5
//15 15 4
//7 13 10 10
//2 1000 2
//1 1 1 999
//10 4 10
//7 1 2 1

// *******************1***********************

struct Sol2 {
    int main() {
        int tt;
        cin >> tt;
        while (tt--) {
            int n;
            cin >> n;
            vector<int> cnt(n + 1);
            for (int i = 0; i < n; i++) {
                int a;
                cin >> a;
                cnt[a] += 1;
            }
            int ans = 0;
            int sum = 0;
            for (int k = 0; k <= n; k++) {
                if (cnt[k] == 0 && sum == k) {
                    ans += 1;
                }
                sum += cnt[k];
            }
            cout << ans << '\n';
        }
        return 0;
    }
};

//4
//2
//1 1
//7
//0 1 2 3 4 5 6
//8
//6 0 3 3 6 7 2 7
//5
//3 0 0 3 3


// *******************2***********************

struct Sol3 {
    int main() {
        int tt;
        cin >> tt;
        while (tt--) {
            int n;
            cin >> n;
            string s;
            cin >> s;
            vector<vector<int>> at(26);
            for (int i = 0; i < n; i++) {
                at[(int) (s[i] - 'a')].push_back(i);
            }
            vector<int> order(26);
            iota(order.begin(), order.end(), 0);
            sort(order.begin(), order.end(), [&](int i, int j) {
                return at[i].size() > at[j].size();
            });
            string res = "";
            int best = -1;
            for (int cnt = 1; cnt <= 26; cnt++) {
                if (n % cnt == 0) {
                    int cur = 0;
                    for (int i = 0; i < cnt; i++) {
                        cur += min(n / cnt, (int) at[order[i]].size());
                    }
                    if (cur > best) {
                        best = cur;
                        res = string(n, ' ');
                        vector<char> extra;
                        for (int it = 0; it < cnt; it++) {
                            int i = order[it];
                            for (int j = 0; j < n / cnt; j++) {
                                if (j < (int) at[i].size()) {
                                    res[at[i][j]] = (char) ('a' + i);
                                } else {
                                    extra.push_back((char) ('a' + i));
                                }
                            }
                        }
                        for (char& c : res) {
                            if (c == ' ') {
                                c = extra.back();
                                extra.pop_back();
                            }
                        }
                    }
                }
            }
            cout << n - best << '\n';
            cout << res << '\n';
        }
        return 0;
    }
};

//4
//5
//hello
//10
//codeforces
//5
//eevee
//6
//appall


// *******************3***********************

struct Sol4 {
    int main() {
        int tt;
        cin >> tt;
        while (tt--) {
            int n;
            cin >> n;
            vector<int> a(n);
            for (int i = 0; i < n; i++) {
                cin >> a[i];
            }
            int ans = 1;
            auto Test = [&](long long x) {
                int cnt = 0;
                for (int v : a) {
                    long long u = llround(sqrtl(v + x));
                    if (u * u == v + x) {
                        cnt += 1;
                    }
                }
                ans = max(ans, cnt);
            };
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j < n; j++) {
                    int diff = a[j] - a[i];
                    for (int k = 1; k * k <= diff; k++) {
                        if (diff % k == 0) {
                            long long q = k + diff / k;
                            if (q % 2 == 0) {
                                q /= 2;
                                if (q * q >= a[j]) {
                                    Test(q * q - a[j]);
                                }
                            }
                        }
                    }
                }
            }
            cout << ans << '\n';
        }
        return 0;
    }
};

//4
//5
//1 2 3 4 5
//5
//1 6 13 22 97
//1
//100
//5
//2 5 10 17 26

// *******************4***********************


int main() {
//    Sol1 s1;
//    s1.main();

//    Sol2 s2;
//    s2.main();

//    Sol3 s3;
//    s3.main();

    Sol4 s4;
    s4.main();

    return 0;
}
