#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")
#define ru(i,l,r) for(int i=(l);i<=(r);i++)
#define ru_(i,l,r) for(int i=(l);i<(r);i++)
#define rup(i,l,r) for(int i=(l);i<=(r);i+=2)
#define rd(i,r,l) for(int i=(r);i>=(l);i--)
#define ll long long
#define pii pair<ll,int>
#define s1 first
#define s2 second

using namespace std;


const ll MOD=998244353;
const ll MAX=1000100;
vector<vector<ll>> adj;
vector<ll> tin(MAX,0),tout(MAX,0);
vector<ll> parent(MAX,0);
vector<ll> overall_max(MAX,0);
ll now=1;
vector<ll> jump_to(MAX,0),sub(MAX,0);
vector<ll> dp(MAX,0);
struct FenwickTree{
    vector<ll> bit; ll n;
    FenwickTree(ll n){this->n=n; bit.assign(n,0);}
    FenwickTree(vector<ll> a): FenwickTree(a.size()){
        ll x=a.size();
        for(size_t i=0;i<x;i++) add(i,a[i]);
    }
    ll sum(ll r){
        ll ret=0;
        for(;r>=0;r=(r&(r+1))-1){ret+=bit[r]; ret%=MOD;};
        return ret;
    }
    ll sum(ll l, ll r){
        if(l>r) return 0;
        ll val=sum(r)-sum(l-1)+MOD; val%=MOD;
        return val;
    }
    void add(ll idx, ll delta){
        for(;idx<n;idx=idx|(idx+1)){
            bit[idx]+=delta; bit[idx]%=MOD;
        }
    }
};
void dfs(ll cur, ll par){
    parent[cur]=par; tin[cur]=now++; overall_max[cur]=cur;
    for(auto chld:adj[cur]){
        if(chld!=par){
            jump_to[chld]=max(jump_to[cur],cur);
            dfs(chld,cur);
            overall_max[cur]=max(overall_max[cur],overall_max[chld]);
        }
    }; tout[cur]=now++;
}
void solve(){
    ll n; cin>>n; adj.clear(); adj.resize(n+5);
    ru(i,1,n-1){ll u,v; cin>>u>>v; adj[u].push_back(v); adj[v].push_back(u);}
    now=1; dfs(1,0); ll ans=0; FenwickTree enter_time(now+5),exit_time(now+5);
    overall_max[0]=MOD; dp[0]=1;
    ru(i,1,n){
        ll p=jump_to[i]; dp[i]=(enter_time.sum(0,tin[i])-exit_time.sum(0,tin[i])-sub[p]+dp[p]+MOD+MOD)%MOD;
        if(p>i) dp[i]=0;
        ll node=i; while(overall_max[node]==i) node=parent[node];
        enter_time.add(tin[node],dp[i]); exit_time.add(tout[node],dp[i]);
        sub[i]=(enter_time.sum(0,tin[i])-exit_time.sum(0,tin[i])+MOD)%MOD;
    }; cout<<dp[n]<<endl;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    ll t; cin>>t; while(t--)solve(); return 0;}