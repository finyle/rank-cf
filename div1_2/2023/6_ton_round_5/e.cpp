#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 8, M = 1 << 18;

int n, k, A, c[M << 1][2], dp[N];
vector<pair<int, int>> p[N];

void insert(int i, int v) {
    for (i += M; i; i >>= 1) c[i][0] = v, v = max(v, c[i ^ 1][0]);
}
void add(int i, int v) {
    for (i += M + 1; i > 1; i >>= 1) {
        int v1 = i & 1 ? v : 0;
        c[i ^ 1][0] += v1, c[i ^ 1][1] += v1;
        c[i >> 1][0] = max(c[i][0], c[i ^ 1][0]) + c[i >> 1][1];
    }
}
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> k >> A;
    int sum = 0;
    while (n--) {
        int x, y, w;
        cin >> x >> y >> w;
        p[k - y].emplace_back(x, w);
        sum += w;
    }
    for (int i = 1; i <= k; i++) {
        add(i - 1, -A);
        for (auto [x, w] : p[i]) add(x, w);
        dp[i] = max(dp[i - 1], c[1][0]);
        insert(i, dp[i]);
    }
    cout << sum - dp[k] << '\n';
}

//4 6 1
//1 2 1
//2 1 1
//1 1 1
//3 2 6
