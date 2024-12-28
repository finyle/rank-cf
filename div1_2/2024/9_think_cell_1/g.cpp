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
const ll MOD=998244353;
const ll MAX=1000100;
struct FenwickTree{
    vector<ll> bit;
    ll n;
    FenwickTree(ll n){
        this->n = n;
        bit.assign(n, 0);
    }
    FenwickTree(vector<ll> a):FenwickTree(a.size()){
        ll x=a.size();
        for(size_t i=0;i<x;i++)
            add(i,a[i]);
    }
    ll sum(ll r) {
        ll ret=0;
        for(;r>=0;r=(r&(r+1))-1){
            ret+=bit[r];
            ret%=MOD;
        }
        return ret;
    }
    ll sum(ll l,ll r) {
        if(l>r)
            return 0;
        ll val=sum(r)-sum(l-1)+MOD;
        val%=MOD;
        return val;
    }
    void add(ll idx,ll delta) {
        for(;idx<n;idx=idx|(idx+1)){
            bit[idx]+=delta;
            bit[idx]%=MOD;
        }
    }
};
vector<vector<ll>> adj;
vector<ll> tin(MAX,0),tout(MAX,0);
vector<ll> parent(MAX,0);
vector<ll> overall_max(MAX,0);
ll now=1;
vector<ll> jump_to(MAX,0),sub(MAX,0);
void dfs(ll cur,ll par){
    parent[cur]=par;
    tin[cur]=now++;
    overall_max[cur]=cur;
    for(auto chld:adj[cur]){
        if(chld!=par){
            jump_to[chld]=max(jump_to[cur],cur);
            dfs(chld,cur);
            overall_max[cur]=max(overall_max[cur],overall_max[chld]);
        }
    }
    tout[cur]=now++;
}
vector<ll> dp(MAX,0);
void solve(){
    ll n; cin>>n;
    adj.clear();
    adj.resize(n+5);
    for(ll i=1;i<=n-1;i++){
        ll u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    now=1;
    dfs(1,0);
    ll ans=0;
    FenwickTree enter_time(now+5),exit_time(now+5);
    overall_max[0]=MOD;
    dp[0]=1;
    for(ll i=1;i<=n;i++){
        ll p=jump_to[i];
        dp[i]=(enter_time.sum(0,tin[i])-exit_time.sum(0,tin[i])-sub[p]+dp[p]+MOD+MOD)%MOD;
        if(p>i){
            dp[i]=0;
        }
        ll node=i;
        while(overall_max[node]==i){
            node=parent[node];
        }
        enter_time.add(tin[node],dp[i]);
        exit_time.add(tout[node],dp[i]);
        sub[i]=(enter_time.sum(0,tin[i])-exit_time.sum(0,tin[i])+MOD)%MOD;
    }
    cout<<dp[n]<<nline;
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
    while(test_cases--){
        solve();
    }
    cout<<fixed<<setprecision(10);
    cerr<<"Time:"<<1000*((double)clock())/(double)CLOCKS_PER_SEC<<"ms\n";
}

//6
//1
//2
//1 2
//3
//1 2
//1 3
//3
//1 2
//2 3
//5
//1 2
//1 3
//1 4
//1 5
//10
//1 2
//2 3
//1 4
//2 5
//2 6
//4 7
//5 8
//4 9
//9 10
