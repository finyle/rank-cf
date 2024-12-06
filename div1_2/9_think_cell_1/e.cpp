#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
#define ll long long
const ll INF_ADD=1e18;
#define pb push_back
#define mp make_pair
#define nline "\n"
#define f first
#define s second
#define pll pair<ll,ll>
#define all(x) x.begin(),x.end()
const ll MOD=998244353;
const ll MAX=5000500;
vector<ll> fact(MAX+2,1),inv_fact(MAX+2,1);
ll binpow(ll a,ll b,ll MOD){
    ll ans=1;
    a%=MOD;
    while(b){
        if(b&1)
            ans=(ans*a)%MOD;
        b/=2;
        a=(a*a)%MOD;
    }
    return ans;
}
ll inverse(ll a,ll MOD){
    return binpow(a,MOD-2,MOD);
}
void precompute(ll MOD){
    for(ll i=2;i<MAX;i++){
        fact[i]=(fact[i-1]*i)%MOD;
    }
    inv_fact[MAX-1]=inverse(fact[MAX-1],MOD);
    for(ll i=MAX-2;i>=0;i--){
        inv_fact[i]=(inv_fact[i+1]*(i+1))%MOD;
    }
}
ll nCr(ll a,ll b,ll MOD){
    if(a==b){
        return 1;
    }
    if((a<0)||(a<b)||(b<0))
        return 0;
    ll denom=(inv_fact[b]*inv_fact[a-b])%MOD;
    return (denom*fact[a])%MOD;
}
ll n,k;
ll ways(ll gaps,ll options){
    gaps--;
    ll now=nCr(gaps+options-1,options-1,MOD);
    return now;
}
void solve(){
    cin>>n;
    for(ll k=1;k<=(n-1)/2;k++){
        ll ans=1;
        for(ll deleted=2*k;deleted<=n-1;deleted+=2*k){
            ll options=2*k,left_elements=n-deleted;
            ans=(ans+ways(left_elements+1,deleted+1)-ways(left_elements+1,options)+MOD)%MOD;
        }
        cout<<ans<<" ";
    }
    cout<<nline;
    return;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
//#ifndef ONLINE_JUDGE
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
//    freopen("error.txt", "w", stderr);
//#endif
    ll test_cases=1;
    cin>>test_cases;
    precompute(MOD);
    while(test_cases--){
        solve();
    }
    cout<<fixed<<setprecision(10);
    cerr<<"Time:"<<1000*((double)clock())/(double)CLOCKS_PER_SEC<<"ms\n";
}

//4
//3
//4
//5
//10
