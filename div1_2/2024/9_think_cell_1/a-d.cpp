
#include <bits/stdc++.h>
using namespace std;
#define ll long long
void solve(){
    ll n; cin>>n;
    vector<ll> a(2*n);
    ll ans=0;
    for(auto &it:a){
        cin>>it;
    }
    sort(a.begin(),a.end());
    for(ll i=0;i<2*n;i+=2){
        ans+=a[i];
    }
    cout<<ans<<"\n";
    return;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    ll test_cases=1;
    cin>>test_cases;
    while(test_cases--){
        solve();
    }
    cout<<fixed<<setprecision(10);
    cerr<<"Time:"<<1000*((double)clock())/(double)CLOCKS_PER_SEC<<"ms\n";
}

// ***********************************************************************************

#define ll long long
void solve(){
    ll n; cin>>n;
    ll l=1,r=n;
    for(ll i=1;i<=n;i++){
        if(i&1){
            cout<<l<<" ";
            l++;
        }
        else{
            cout<<r<<" ";
            r--;
        }
    }
    cout<<"\n";
    return;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    ll test_cases=1;
    cin>>test_cases;
    while(test_cases--){
        solve();
    }
    cout<<fixed<<setprecision(10);
    cerr<<"Time:"<<1000*((double)clock())/(double)CLOCKS_PER_SEC<<"ms\n";
}

// ***************************************************************************
void solve(){
    ll n; cin>>n;
    set<ll> used,not_used;
    vector<ll> ans;
    for(ll i=1;i<=n;i++){
        ll x; cin>>x; x+=i;
        if(!used.count(x)){
            not_used.insert(x);
        }
        ll cur=*(--not_used.upper_bound(x)); //find the largest element(<= x) which is not in.txt set "used"
        not_used.erase(cur);
        ans.push_back(cur);
        used.insert(cur);
        if(!used.count(cur-1)){
            not_used.insert(cur-1);
        }
    }
    sort(ans.begin(), ans.end());
    reverse(ans.begin(), ans.end());
    for(auto i:ans){
        cout<<i<<" ";
    }
    cout<<"\n";
    return;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    ll test_cases=1;
    cin>>test_cases;
    while(test_cases--){
        solve();
    }
    cout<<fixed<<setprecision(10);
    cerr<<"Time:"<<1000*((double)clock())/(double)CLOCKS_PER_SEC<<"ms\n";
}

// **********************************************************************
#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
#define ll long long
#define pb push_back
#define mp make_pair
#define nline "\n"
#define f first
#define s second
#define pll pair<ll,ll>
#define all(x) x.begin(),x.end()
const ll MOD=1e9+7;
const ll MAX=500500;
void solve(){
    ll n,ans=0; cin>>n;
    string s; cin>>s; s=" "+s;
    vector<ll> dp(n+5,0);
    for(ll i=n;i>=1;i--){
        if(s[i]=='1'){
            dp[i]=dp[i+3]+n-i+1;
        }
        else{
            dp[i]=dp[i+1];
        }
        ans+=dp[i];
    }
    cout<<ans<<nline;
    return;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    ll test_cases=1;
    cin>>test_cases;
    while(test_cases--){
        solve();
    }
    cout<<fixed<<setprecision(10);
    cerr<<"Time:"<<1000*((double)clock())/(double)CLOCKS_PER_SEC<<"ms\n";
}