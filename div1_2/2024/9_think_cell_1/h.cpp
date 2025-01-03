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
const ll MAX=200200;
vector<ll> adj[MAX];
ll now=0,till=20;
vector<ll> tin(MAX,0),tout(MAX,0),depth(MAX,0);
vector<vector<ll>> jump(MAX,vector<ll>(till+1,0));
void dfs(ll cur,ll par){
    jump[cur][0]=par;
    for(ll i=1;i<=till;i++)
        jump[cur][i]=jump[jump[cur][i-1]][i-1];
    tin[cur]=++now;
    for(ll chld:adj[cur]){
        if(chld!=par){
            depth[chld]=depth[cur]+1;
            dfs(chld,cur);
        }
    }
    tout[cur]=++now;
}
bool is_ancestor(ll a,ll b){
    if((tin[a]<=tin[b])&&(tout[a]>=tout[b]))
        return 1;
    return 0;
}
ll lca(ll a,ll b){
    if(is_ancestor(a,b))
        return a;
    for(ll i=till;i>=0;i--){
        if(!is_ancestor(jump[a][i],b))
            a=jump[a][i];
    }
    return jump[a][0];
}
void solve(){
    ll n; cin>>n;
    ll m; cin>>m;
    vector<ll> a(n+5);
    for(ll i=1;i<=n-1;i++){
        ll u,v; cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    now=1;
    dfs(1,1);
    vector<ll> p(n),q(n);
    for(ll i=0;i<n;i++){
        p[i]=q[i]=i+1;
    }
    sort(all(p),[&](ll l,ll r){return tin[l]<tin[r];});
    sort(all(q),[&](ll l,ll r){
        return tout[l]<tout[r];
    });
    for(auto it:p){
        cout<<it<<" ";
    }
    cout<<endl;
    for(auto it:q){
        cout<<it<<" ";
    }
    cout<<endl;
    auto query_p=[&](ll l,ll r){
        ll left_pos=n+1,right_pos=-1;
        for(ll i=0;i<n;i++){
            ll node=p[i];
            if((tin[node]>=l) and (tin[node]<=r)){
                left_pos=min(left_pos,i);
                right_pos=i;
            }
        }
        ll now=n+5;
        if(right_pos!=-1){
            left_pos++,right_pos++;
            cout<<"? 1 "<<left_pos<<" "<<right_pos<<endl;
            cin>>now;
        }
        return now;
    };
    auto query_q=[&](ll l,ll r){
        ll left_pos=n+1,right_pos=-1;
        for(ll i=0;i<n;i++){
            ll node=q[i];
            if((tout[node]>=l) and (tout[node]<=r)){
                left_pos=min(left_pos,i);
                right_pos=i;
            }
        }
        ll now=n+5;
        if(right_pos!=-1){
            left_pos++,right_pos++;
            cout<<"? 2 "<<left_pos<<" "<<right_pos<<endl;
            cin>>now;
        }
        return now;
    };
    while(m--){
        ll u,v; cin>>u>>v;
        if(tout[u]>tout[v]){
            swap(u,v);
        }
        ll lca_node=lca(u,v);
        ll ans=n;
        if(lca_node==v){
            ans=min(ans,query_q(1,tin[u]));
            ans=min(ans,query_p(tin[u]+1,tout[v]));
            ans=min(ans,query_q(tout[v]+1,now));
            cout<<"! "<<ans<<endl;
            ll x; cin>>x;
            continue;
        }
        ans=min(ans,query_q(1,tin[u]));
        ll consider=v;
        for(auto it:adj[lca_node]){
            if(is_ancestor(lca_node,it) and is_ancestor(it,v)){
                consider=it;
            }
        }
        ans=min(ans,query_p(tin[u]+1,tin[consider]-1));
        ans=min(ans,query_q(tin[consider],tin[v]));
        ans=min(ans,query_p(tin[v]+1,tout[lca_node]));
        ans=min(ans,query_q(tout[lca_node]+1,now));
        cout<<"! "<<ans<<endl;
        ll x; cin>>x;
    }
    for(ll i=1;i<=n;i++){
        adj[i].clear();
    }
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

//1
//3 1
//1 2
//2 3
//
//
//2 3
//
//1
//
//0
//
//1