#include <bits/stdc++.h>
using namespace std;
int p2[5001], dp[5001][5001], sum[5001][5001], sum2[5001][5001];
int32_t main()
{
    int n, mod;
    cin >> n >> mod;
    p2[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        p2[i] = p2[i - 1] + p2[i - 1];
        if (p2[i] >= mod)
        {
            p2[i] -= mod;
        }
    }
    dp[1][1] = 1;
    for (int j = 1; j <= n; ++j)
    {
        sum[1][j] = 1;
        sum2[1][j] = 1;
    }
    for (int i = 2; i <= n; ++i)
    {
        for (int j = 1; j <= i; ++j)
        {
            if (i == j)
            {
                dp[i][j] = p2[i - 2];
                for (int k = 1; k < i; ++k)
                {
                    dp[i][j] -= dp[i][k];
                    if (dp[i][j] < 0)
                    {
                        dp[i][j] += mod;
                    }
                }
                continue;
            }
            int lg = j + 1;
            if (i - j - lg >= 0)
            {
                dp[i][j] = (1ll * dp[j][j] * sum2[i - j - lg][lg - j - 1]) % mod;
            }
        }
        for (int j = 1; j <= i; ++j)
        {
            sum[i][j] = sum[i][j - 1] + dp[i][j];
            if (sum[i][j] >= mod)
            {
                sum[i][j] -= mod;
            }
        }
        for (int j = i + 1; j <= n; ++j)
        {
            sum[i][j] = sum[i][j - 1];
        }
        for (int j = 0; j <= n; ++j)
        {
            sum2[i][j] = sum[i][j];
            if (j + 1 <= n)
            {
                sum2[i][j] += sum2[i - 1][j + 1];
                if (sum2[i][j] >= mod)
                {
                    sum2[i][j] -= mod;
                }
            }
        }
    }
    cout << dp[n][n];
}

// 2 100