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
#define all(x) x.begin(),x.end()

using namespace std;

struct a{
    int main(){
        int t; cin>>t;
        while(t--){
            ll n; cin>>n; vector<ll> a(2*n);
            ll ans=0; for(auto &it:a) cin>>it;
            sort(a.begin(), a.end());
            for(ll i=0;i<2*n;i+=2) ans+=a[i];
            cout<<ans<<endl;
        }; return 0;
    }
};
struct b{
    int main(){
        int t; cin>>t;
        while(t--){
            ll n; cin>>n; ll l=1, r=n;
            ru(i,1,n){
                if(i&1) {cout<<l<<" "; l++;}
                else{cout<<r<<" "; r--;}
            }
            cout<<endl;
        }
    }
};
struct c{
    int main(){
        int t; cin>>t;
        while(t--){
            ll n; cin>>n; set<ll> used,not_used; vector<ll> ans;
            ru(i,1,n){
                ll x; cin>>x; x+=i;
                if(!used.count(x)) not_used.insert(x);
                ll cur=*(--not_used.upper_bound(x));
                not_used.erase(cur);
                ans.push_back(cur); used.insert(cur);
                if(!used.count(cur-1)) not_used.insert(cur-1);
            }
            sort(ans.begin(), ans.end());
            reverse(ans.begin(), ans.end());
            for(auto i: ans) cout<<i<<" "; cout<<endl;
        }; return 0;
    }
};
struct d{
    int main(){
        int t; cin>>t;
        while(t--){
            ll n, ans=0; cin>>n; string s; cin>>s; s=" "+s; vector<ll> dp(n+5,0);
            rd(i,n,1){
                if(s[i]=='1') dp[i]=dp[i+3]+n-i+1;
                else dp[i]=dp[i+1];
                ans+=dp[i];
            }; cout<<ans<<endl;
        }
    }
};
// math
struct e{
    static const int MAX=5e6+500, MOD=998244353;
    vector<ll> fact, inv_fact;
    ll n, k;
    ll binpow(ll a,ll b, ll MOD){
        ll ans=1; a%=MOD;
        while(b){
            if(b&1) ans=(ans*a)%MOD;
            b/=2; a=(a*a)%MOD;
        }; return ans;
    }
    ll inverse(ll a,ll MOD){return binpow(a,MOD-2,MOD);}
    void precompute(ll MOD){
        ru_(i,2,MAX) fact[i]=(fact[i-1]*i)%MOD;
        inv_fact[MAX-1]=inverse(fact[MAX-1],MOD);
        rd(i,MAX-2,0) inv_fact[i]=(inv_fact[i+1]*(i+1))%MOD;
    }
    ll nCr(ll a,ll b,ll MOD){
        if(a==b) return 1;
        if((a<0)||(a<b)||(b<0)) return 0;
        ll denom=(inv_fact[b]*inv_fact[a-b])%MOD;
        return (denom*fact[a])%MOD;
    }
    ll ways(ll gaps, ll options){
        gaps--; ll now=nCr(gaps+options-1, options-1,MOD); return now;
    }
    void solve(){
        cin>>n;
        ru(i,1,(n-1)/2){
            ll ans=1;
            for(ll deleted=2*k;deleted<=n-1;deleted+=2*k){
                ll options=2*k, left_elements=n-deleted;
                ans=(ans+ways(left_elements+1,deleted+1)-ways(left_elements+1,options)+MOD)%MOD;
            }; cout<<ans<<" ";
        }; cout<<endl;
    }
    int main(){
        ll t; cin>>t; precompute(MOD); while(t--) solve();
    }
};
// bitset
struct f{
    void solve(){
        ll n,q; cin>>n>>q; ll till=1,len=1;
        while(till<n) {till*=2; len++;}
        ll ans=0; vector<vector<ll>> track(2,vector<ll>(till+5,0));
        auto add=[&](ll x,ll p){
            queue<ll> trav; if(track[p][x]) return;
            trav.push(x); track[p][x]=1;
            while(!trav.empty()){
                auto it=trav.front(); trav.pop();
                if(track[0][it]&track[1][it]) ans=max(ans,it);
                ru_(i,0,len) {
                    if(it&(1<<i)){
                        ll cur=(it^(1<<i));
                        if(!track[p][cur]) {track[p][cur]=1; trav.push(cur);}
                    }
                }
            }
        };
        ll supermask=till-1; vector<ll> a(q+5);
        ru(i,1,q){
            ll h; cin>>h; a[i]=(h+ans)%n;
            add(a[i],0); add(supermask^a[i],1);
            cout<<ans<<" \n"[i==q];
        }; return;
    }
    int main(){
        // 输入输出优化：
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
#ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        freopen("error.txt", "w", stderr);
#endif
        int t; cin>>t; while(t--) solve(); return 0;
//        cout<<fixed<<setprecision(10);
//        cerr<<"Time:"<<1000*((double)clock())/(double)CLOCKS_PER_SEC<<"ms\n";
    }
};
// tedukuri-ds: fenwickTree
struct g{
    static const ll MOD=998244353;
    const ll MAX=1000100;
    vector<vector<ll>> adj;
    vector<ll> tin,tout;
    vector<ll> parent;
    vector<ll> overall_max;
    ll now=1;
    vector<ll> jump_to,sub;
    vector<ll> dp;
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
        ll t; cin>>t; while(t--)solve(); return 0;}
};

static const ll MAX=200200;
// tree, interactive
struct h{
    const ll MOD=998244353;
    vector<ll> adj[MAX];
    ll now=0,till=20;
    vector<ll> tin(MAX),tout(MAX),depth(MAX);
    vector<vector<ll>> jump(MAX,vector<ll>(till));
    void dfs(ll cur,ll par){
        jump[cur][0]=par;
        ru(i,1,till){jump[cur][i]=jump[jump[cur][i-1]][i-1];}
        tin[cur]=now++;
        for(ll chld: adj[cur]){
            if(chld!=par) {depth[chld]=depth[cur]+1; dfs(chld,cur);}
        }; tout[cur]=now++;
    }
    bool is_ancestor(ll a,ll b){
        if((tin[a]<=tin[b])&&(tout[a]>=tout[b])) return 1; return 0;
    }
    ll lca(ll a,ll b){
        if(is_ancestor(a,b)) return a;
        rd(i,till,0) if(!is_ancestor(jump[a][i],b)) a=jump[a][i];
        return jump[a][0];
    }
    void solve(){
        ll n; cin>>n; ll m; cin>>m;
        vector<ll> a(n+5); ru(i,1,n-1){ll u,v;cin>>u>>v; adj[u].push_back(v); adj[v].push_back(u);}
        now=1; dfs(1,1); vector<ll>p(n),q(n); ru_(i,0,n)p[i]=q[i]=i+1;
        sort(all(p));
        sort(all(p),[&](ll l,ll r){return tin[l]<tin[r];});
        sort(all(q),[&](ll l,ll r){return tout[l]<tout[r];});
        for(auto x: p) cout<<x<<" "; cout<<endl;
        for(auto x: q) cout<<x<<" "; cout<<endl;
        auto query_p=[&](ll l,ll r){
            ll left_pos=n+1, right_pos=-1;
            ru_(i,0,n){
                ll node=p[i]; if((tin[node]>=l)and(tin[node]<=r)){left_pos=min(left_pos,i); right_pos=i;}
            };
            ll now=n+5;
            if(right_pos!=-1){
                left_pos++,right_pos++; cout<<"? 1"<<left_pos<<" "<<right_pos<<endl; cin>>now;
            }; return now;
        };
        auto query_q=[&](ll l,ll r){
            ll left_pos=n+1, right_pos=-1;
            ru_(i,0,n){
                ll node=p[i]; if((tin[node]>=l)and(tin[node]<=r)){left_pos=min(left_pos,i); right_pos=i;}
            };
            ll now=n+5;
            if(right_pos!=-1){
                left_pos++,right_pos++; cout<<"? 2"<<left_pos<<" "<<right_pos<<endl; cin>>now;
            }; return now;
        };
        while(m--){
            ll u,v; cin>>u>>v;
            if(tout[u]>tout[v]) swap(u,v); ll lca_node=lca(u,v); ll ans=n;
            if(lca_node==v){
                ans=min(ans,query_q(1,tin[u]));
                ans=min(ans,query_p(tin[u]+1,tout[v]));
                ans=min(ans,query_q(tout[v]+1,now)); cout<<"! "<<ans<<endl;
                ll x; cin>>x; continue;
            };
            ans=min(ans,query_q(1,tin[u]));
            ll consider=v;
            for(auto x:adj[lca_node]){
                if(is_ancestor(lca_node,x)and is_ancestor(x,v)) consider=x;
            }
            ans=min(ans,query_p(tin[u]+1,tin[consider]-1));
            ans=min(ans,query_q(tin[consider],tin[v]));
            ans=min(ans,query_p(tin[v]+1,tout[lca_node]));
            ans=min(ans,query_q(tout[lca_node]+1,now));
            cout<<"! "<<ans<<endl; ll x; cin>>x;
        }
        ru(i,1,n) adj[i].clear();
    }
    int main(){int t; cin>>t; while(t--) solve(); return 0;}
};

struct i{ // comb nCr
};


int main(){
//    c c;
//    c.main();

//    d d;
//    d.main();

//    e e;
//    e.main();

//    f f;
//    f.main();

    h h;
    h.main();
}