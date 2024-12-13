#include<bits/stdc++.h>
using namespace std;
int t,n,a[109];
inline int read(){
    int s = 0,w = 1;
    char ch = getchar();
    while (ch > '9' || ch < '0'){ if (ch == '-') w = -1; ch = getchar();}
    while (ch <= '9' && ch >= '0') s = (s << 1) + (s << 3) + (ch ^ 48),ch = getchar();
    return s * w;
}
int main(){
    t = read();
    while (t --){
        n = read();
        for (int i = 1;i <= n;i += 1) a[i] = read();
        puts(a[1] == 1 ? "Yes" : "No");
    }
    return 0;
}


// *******************
#include <bits/stdc++.h>
#define int long long
using namespace std;
int32_t main()
{
    cin.tie(nullptr)->ios_base::sync_with_stdio(false);
    int q;
    cin >> q;
    while (q--)
    {
        int n;
        string s;
        cin >> n >> s;
        s = '$' + s;
        int cnt0 = 0, cnt1 = 0;
        for (int i = 1; i <= n; ++i)
        {
            cnt0 += s[i] == '0';
            cnt1 += s[i] == '1';
        }
        int ans = cnt0 * cnt1;
        int lg = 1;
        for (int i = 2; i <= n; ++i)
        {
            if (s[i] == s[i - 1])
            {
                lg++;
            }
            else
            {
                ans = max(ans, lg * lg);
                lg = 1;
            }
        }
        ans = max(ans, lg * lg);
        cout << ans << '\n';
    }
}

// *************************
#include <bits/stdc++.h>
using namespace std;
int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    int q;
    cin >> q;
    while (q--)
    {
        int n;
        string a, b;
        cin >> n >> a >> b;
        a = '$' + a;
        b = '$' + b;
        bool ok = true;
        for (int i = 1; i <= n; ++i)
        {
            if (a[i] != char('1' - b[i] + '0'))
            {
                ok = false;
                break;
            }
        }
        ok = ok || (a == b);
        if (!ok)
        {
            cout << "NO\n";
            continue;
        }
        vector<pair<int, int>> ops;
        if (a[1] != b[1])
        {
            ops.push_back({1, n});
            a = b;
        }
        vector<int> cnt(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            if (a[i] == '1')
            {
                if (i == 1)
                {
                    ops.push_back({1, n});
                    ops.push_back({2, n});
                }
                else
                {
                    cnt[i]++;
                    cnt[i - 1]++;
                }
            }
        }
        for (int i = 1; i <= n; ++i)
        {
            if (cnt[i] % 2 == 1)
            {
                ops.push_back({1, i});
            }
        }
        cout << "YES\n"
             << (int)ops.size() << '\n';
        for (auto i : ops)
        {
            cout << i.first << ' ' << i.second << '\n';
        }
    }
}

// **************************
#include <bits/stdc++.h>
using namespace std;
int mod = 998244353;
struct Mint
{
    int val;
    Mint(int _val = 0)
    {
        val = _val % mod;
    }
    Mint(long long _val = 0)
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
vector<int> get_primes(int n)
{
    int d = 2;
    vector<int> ans;
    while (d * d <= n)
    {
        bool este = false;
        while (n % d == 0)
        {
            n /= d;
            este = true;
        }
        if (este)
        {
            ans.push_back(d);
        }
        d++;
    }
    if (n != 1)
    {
        ans.push_back(n);
    }
    return ans;
}
int gcd(int a, int b)
{
    while (b)
    {
        int c = a % b;
        a = b;
        b = c;
    }
    return a;
}
int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    int q;
    cin >> q;
    while (q--)
    {
        int n, m;
        cin >> n >> m;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i];
        }
        bool ok = true;
        for (int i = 2; i <= n; ++i)
        {
            if (a[i - 1] % a[i] != 0)
            {
                ok = false;
                break;
            }
        }
        if (!ok)
        {
            cout << 0 << '\n';
            continue;
        }
        vector<int> factori = get_primes(a[1]);
        map<pair<int, int>, int> calculat;
        for (int i = 2; i <= n; ++i)
        {
            calculat[{a[i - 1], a[i]}] = 0;
        }
        for (auto i : calculat)
        {
            int left = i.first.first / i.first.second;
            int till = m / i.first.second;
            vector<int> left_primes;
            for (auto i : factori)
            {
                if (left % i == 0)
                {
                    left_primes.push_back(i);
                }
            }
            int sz = (int)left_primes.size();
            int ans = 0;
            for (int mask = 0; mask < (1 << sz); ++mask)
            {
                int prod = 1;
                int cnt = 0;
                for (int j = 0; j < sz; ++j)
                {
                    if (mask & (1 << j))
                    {
                        prod *= left_primes[j];
                        cnt++;
                    }
                }
                if (cnt % 2 == 0)
                {
                    ans += till / prod;
                }
                else
                {
                    ans -= till / prod;
                }
            }
            calculat[i.first] = ans;
        }
        Mint ans = 1;
        for (int i = 2; i <= n; ++i)
        {
            ans = ans * calculat[{a[i - 1], a[i]}];
        }
        cout << ans.val << '\n';
    }
}
