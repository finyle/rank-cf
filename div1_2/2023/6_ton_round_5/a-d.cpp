#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct Sol1 {
    int main() {
        ios::sync_with_stdio(false), cin.tie(nullptr);
        int T;
        cin >> T;
        while (T--) {
            int n, m, a[50], b[50];
            long long sumA = 0, sumB = 0;
            cin >> n >> m;
            for (int i = 0; i < n; i++)
                cin >> a[i], sumA += a[i];
            for (int i = 0; i < m; i++)
                cin >> b[i], sumB += b[i];
            if (sumA > sumB) cout << "Tsondu\n";
            if (sumA < sumB) cout << "Tenzing\n";
            if (sumA == sumB) cout << "Draw\n";
        }
    }
};

struct Sol2 {

    int main() {
        ios::sync_with_stdio(false), cin.tie(nullptr);
        int T;
        cin >> T;
        while (T--) {
            int n, x, a[100000];
            cin >> n >> x;
            int s = 0;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < n; j++) cin >> a[j];
                for (int j = 0; j < n; j++) {
                    if ((x | a[j]) != x) break;
                    s |= a[j];
                }
            }
            if (s == x) cout << "YES\n";
            else cout << "NO\n";
        }
    }
};

struct Sol3 {
    int main() {
        ios::sync_with_stdio(false), cin.tie(nullptr);
        int T;
        cin >> T;
        while (T--) {
            const int N = 200000 + 5;
            int n, a[N], dp[N], buc[N];
            cin >> n;
            dp[0] = 0;
            for (int i = 1; i <= n; i++) buc[i] = 0x3f3f3f3f;
            for (int i = 1; i <= n; i++) {
                cin >> a[i];
                dp[i] = min(dp[i - 1] + 1, buc[a[i]]);
                buc[a[i]] = min(buc[a[i]], dp[i - 1]);
            }
            cout << n - dp[n] << '\n';
        }
    }
};

struct Sol4 {
    int n, m;
    long long dis[100][100];

    int main() {
        ios::sync_with_stdio(false), cin.tie(nullptr);
        cin >> n >> m;
        memset(dis, 0x3f, sizeof dis);
        while (m--) {
            int u, v, w;
            cin >> u >> v >> w, u--, v--;
            dis[u][v] = dis[v][u] = w;
        }
        for (int i = 0; i < n; i++) dis[i][i] = 0;
        for (int k = 0; k < n; k++)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
        if (dis[0][n - 1] > 1e18)
            cout << "inf", exit(0);
        int ord[100];
        iota(ord, ord + n, 0);
        sort(ord + 1, ord + n, [](int a, int b) {
            return dis[0][a] < dis[0][b];
        });
        string s(n, '0');
        vector<pair<string, int>> ans;
        for (int i = 0; i < n - 1; i++) {
            int u = ord[i], v = ord[i + 1];
            s[u] = '1';
            ans.emplace_back(s, dis[0][v] - dis[0][u]);
            if (v == n - 1) break;
        }
        cout << dis[0][n - 1] << ' ' << ans.size() << '\n';
        for (auto [s, t] : ans)
            cout << s << ' ' << t << '\n';
    }
};

int main() {
    Sol1 s1;
    s1.main();


    return 0;
}
