#include <bits/stdc++.h>

using namespace std;

const int N = 5000 + 8, P = 1e9 + 7;

int n, m, v, a[N], coef[N], dp[N][N];

long long Pow(long long a, int n) {
    long long r = 1;
    while (n) {
        if (n & 1) r = r * a % P;
        a = a * a % P, n >>= 1;
    }
    return r;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n >> m >> v;
    for (int i = 1; i <= n; i++) cin >> a[i];
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        auto coef = i * Pow(n, P - 2) % P * v % P;
        for (int j = 0; j < i; j++) {
            dp[i][j + 1] = dp[i - 1][j] * coef % P * (m - j) % P;
            dp[i][j] = (dp[i][j] + dp[i - 1][j] * (a[i] + 1LL * j * v % P)) % P;
        }
    }
    int ans = 0;
    for (int i = 0; i <= n; i++)
        (ans += dp[n][i]) %= P;
    cout << ans << '\n';
}