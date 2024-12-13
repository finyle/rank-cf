#include <bits/stdc++.h>
using namespace std;
int mod;
class Mint
{
public:
    int val;
    Mint(int _val = 0)
    {
        val = _val % mod;
    }
    Mint(long long _val)
    {
        val = _val % mod;
    }
    Mint operator+(Mint oth)
    {
        return val + oth.val;
    }
    Mint operator*(Mint oth)
    {
        return 1LL * val * oth.val;
    }
    Mint operator-(Mint oth)
    {
        return val - oth.val + mod;
    }
    void operator+=(Mint oth)
    {
        val = (Mint(val) + oth).val;
    }
    void operator-=(Mint oth)
    {
        val = (Mint(val) - oth).val;
    }
    void operator*=(Mint oth)
    {
        val = (Mint(val) * oth).val;
    }
};
int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n >> mod;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
    }
    a[0] = -1;
    vector<vector<Mint>> pas(n + 1, vector<Mint>(n + 1));
    pas[0][0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            if (j == 0 || j == i)
            {
                pas[i][j] = 1;
                continue;
            }
            pas[i][j] = pas[i - 1][j] + pas[i - 1][j - 1];
        }
    }
    function<Mint(int, int)> combi = [&](int i, int j)
    {
        if (i < j)
        {
            return Mint(0);
        }
        return pas[i][j];
    };
    function<Mint(int, int)> sb = [&](int n, int k)
    {
        return combi(n - 1, n - k);
    };
    vector<vector<vector<Mint>>> dp(n + 1, vector<vector<Mint>>(n + 1, vector<Mint>(2)));
    vector<vector<vector<Mint>>> coef(n + 1, vector<vector<Mint>>(n + 1, vector<Mint>(2)));
    dp[1][1][true] = 1;
    coef[1][1][true] = 1;
    for (int i = 2; i <= n; ++i)
    {
        dp[i][1][true] = dp[i - 1][1][false];
        coef[i][1][true] = dp[i - 1][1][false];
        dp[i][1][false] = (dp[i - 1][1][true] + dp[i - 1][1][false]) * (i - 1);
        coef[i][1][false] = dp[i - 1][1][true] + dp[i - 1][1][false];
        for (int j = 2; j <= i; ++j)
        {
            dp[i][j][true] = (dp[i - 1][j - 1][false] + dp[i - 1][j - 1][true]) * j;
            coef[i][j][true] = dp[i - 1][j - 1][false] + dp[i - 1][j - 1][true];
            dp[i][j][false] = (dp[i - 1][j][false] + dp[i - 1][j][true]) * (i - j);
            coef[i][j][false] = dp[i - 1][j][false] + dp[i - 1][j][true];
        }
    }
    vector<bool> exista(n + 2, true);
    exista[0] = false;
    exista[n + 1] = false;
    int cnt = 0;
    vector<Mint> ans(n + 1);
    for (int i = 1; i < n; ++i)
    {
        int last = -1;
        int m = 0;
        int sz = 0;
        for (int j = 1; j <= n; ++j)
        {
            if (exista[j])
            {
                m += j != (last + 1);
                last = j;
                sz++;
            }
        }
        function<void(int, int, int)> count = [&](int freq, int m, bool type)
        {
            if (freq == 0)
            {
                return;
            }
            if (type)
            {
                for (int k = 1; k <= n; ++k)
                {
                    int need = k - cnt;
                    if (need >= m)
                    {
                        ans[k] += combi(sz - m - 1, need - m) * (dp[need][m][false] + dp[need][m][true] - coef[need][m][true]) * freq;
                    }
                    if (need >= m - 1)
                    {
                        ans[k] += combi(sz - m - 1, need - m + 1) * coef[need + 1][m][true] * freq;
                    }
                }
            }
            else
            {
                for (int k = 1; k <= n; ++k)
                {
                    int need = k - cnt;
                    if (need >= m)
                    {
                        ans[k] += combi(sz - m - 1, need - m) * (dp[need][m][true] + dp[need][m][false]) * freq;
                    }
                }
            }
        };
        if (m)
        {
            if (exista[a[i - 1] + 1] && a[i - 1] + 1 < a[i])
            {
                if (exista[a[i - 1] + 2])
                {
                    count(1, m, true);
                }
                else
                {
                    count(1, m - 1, false);
                }
            }
            cnt++;
            int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0;
            for (int j = 1; j < a[i]; ++j)
            {
                if (j != (a[i - 1] + 1) && exista[j])
                {
                    if (exista[j - 1] && exista[j + 1])
                    {
                        cnt1++;
                        continue;
                    }
                    if (!exista[j - 1] && !exista[j + 1])
                    {
                        cnt2++;
                        continue;
                    }
                    if (!exista[j - 1])
                    {
                        cnt3++;
                        continue;
                    }
                    if (!exista[j + 1])
                    {
                        cnt4++;
                        continue;
                    }
                }
            }
            count(cnt1, m + 1, true);
            count(cnt2, m - 1, false);
            count(cnt3, m, true);
            count(cnt4, m, false);
            cnt--;
        }
        exista[a[i]] = false;
        cnt += a[i] != (a[i - 1] + 1);
    }
    for (int i = 1; i <= n; ++i)
    {
        cout << ans[i].val << ' ';
    }
}

//4 666012
//1 3 4 2
