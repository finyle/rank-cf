#include <iostream>

using namespace std;

struct Sol1 {
    int main()
    {
        int t;
        cin >> t;
        while(t--)
        {
            int n, k;
            cin >> n >> k;
            int sum = 0;
            for(int i = 0 ; i < n ; i++){
                int a;
                cin >> a;
                sum += a;
            }
            if(sum > 0) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
        return 0;
    }
};

//7
//3 2
//0 1 0
//5 3
//1 0 1 1 0
//2 2
//1 1
//4 4
//0 0 0 0
//6 3
//0 0 1 0 0 1
//7 5
//1 1 1 1 1 1 1
//5 3
//0 0 1 0 0


// ************************************

struct Sol2 {
    int main()
    {
        int t;
        cin >> t;
        while(t--)
        {
            int n;
            cin >> n;
            int A[n], cnt[2][n+1];
            cnt[0][0] = cnt[1][0] = 0;
            for(int i = 0; i < n; i++)
            {
                cin >> A[i];
                cnt[0][i+1] = cnt[0][i]+(A[i]==0?1:0);
                cnt[1][i+1] = cnt[1][i]+(A[i]==1?1:0);
            }
            int ans = n-1;
            for(int last_zero = 0; last_zero <= n; last_zero++)
                ans= min(ans, max(cnt[1][last_zero], cnt[0][n]-cnt[0][last_zero]));
            cout << ans << endl;
        }
    }
};

//4
//8
//0 0 1 1 1 1 1 1
//5
//1 0 0 1 1
//2
//1 0
//11
//1 1 0 0 1 0 0 1 1 1 0



// **********************************

struct Sol3 {
    inline void solve()
    {
        int n;
        cin >> n;
        int permutation[n], location[n];
        for(int i = 0; i < n; i++)
        {
            cin >> permutation[i];
            permutation[i]--;
            location[permutation[i]] = i;
        }
        for(int i = 0; i < n; i++)
        {
            if(location[i] == n-1)
                cout << rand()%n+1 << (i == n-1?'\n':' ');
            else
                cout << location[i]+2 << (i == n-1?'\n':' ');
        }
    }

    int main()
    {
        int t;
        cin >> t;
        while(t--)
            solve();
        return 0;
    }
};

//4
//4
//1 2 3 4
//5
//1 3 2 4 5
//3
//2 3 1
//1
//1



//// ******************************
#include <bits/stdc++.h>
typedef long long ll;
const int N = 200000;

struct Sol4 {
    ll V[N], dp[N];
    int dad[N];
    vector<int> child[N];
    vector<pair<int, ll>> answers[N];

    inline ll DP(int v, ll k)
    {
        for(auto [kp, ans]: answers[v])
            if(k == kp)
                return ans;
        ll cnt_child = (ll)child[v].size();
        ll ans = k*V[v];
        if(cnt_child == 0)
            return ans;
        if(k%cnt_child == 0)
            for(auto u: child[v])
                ans += DP(u, k/cnt_child);
        else
        {
            ll dp1[cnt_child], dp2[cnt_child], diff[cnt_child];
            for(int i = 0; i < cnt_child; i++)
                dp1[i] = DP(child[v][i], k/cnt_child), dp2[i] = DP(child[v][i], k/cnt_child+1);
            for(int i = 0; i < cnt_child; i++)
                diff[i] = dp2[i] - dp1[i];
            sort(diff, diff+cnt_child, greater<int>());
            for(int i = 0; i < cnt_child; i++)
                ans += dp1[i];
            for(int i = 0; i < k%cnt_child; i++)
                ans += diff[i];
        }
        answers[v].push_back({k, ans});
        return ans;
    }

    inline ll solve()
    {
        ll n, k;
        cin >> n >> k;
        for(int i = 0; i < n; i++)
            child[i].clear(), answers[i].clear();
        dad[0] = 0;
        for(int i = 0; i < n-1; i++)
        {
            cin >> dad[i+1];
            dad[i+1]--;
            child[dad[i+1]].push_back(i+1);
        }
        for(int i = 0; i < n; i++)
            cin >> V[i];
        return DP(0, k);
    }

    int main()
    {
        int t;
        cin >> t;
        while(t--)
            cout << solve() << '\n';
        return 0;
    }
};

//2
//5 4
//1 2 1 3
//6 2 1 5 7
//5 3
//1 2 1 3
//6 6 1 4 10

// **********************************

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