#include <bits/stdc++.h>
#define ru_(i,l,r) for(int i=(l);i<=(r);i++)
#define ru(i,l,r) for(int i=(l);i<(r);i++)
#define rup(i,l,r) for(int i=(l);i<=(r);i+=2)
#define rd(i,r,l) for(int i=(r);i>=(l);i--)
#define ll long long
#define pii pair<ll,int>
#define s1 first
#define s2 second

using namespace std;

struct a{

    int main(){
        int t; cin>>t;
        while(t--){
            int n; cin>>n; vector<int>a(n); for(auto &x:a) cin>>x;
            if(a[0]==a[n-1]) cout<<"no"<<endl;
            else{cout<<"yes"<<endl; string s(n,'R'); s[1]='B'; cout<<s<<endl;}
        }
    }
};
struct b{
    int main(){
        int t; cin>>t;
        while(t--) {
            auto solve = [&] ()->void{
                ll n;cin >> n;n = n - n % 10 + (n % 10 + 1) % 10;
                while (n > 9) {if (n % 10 == 0) {cout << "no" << endl;return;}n /= 10;}
                cout << (n == 1 ? "yes\n" : "no\n");
            };
            solve();
        }
    }
};
struct c{
//    static const int maxn=100, mod=1e4+9;
//    vector<ll> p2(maxn);
//    void solve(){
//        int n; cin>>n; vector<int>arr(n); for(auto &x:arr) cin>>x;
//        ll sum=0,mn=0,ans=0,abses=0;
//        ru(i,0,n) sum+=arr[i],mn=min(mn,sum);
//        if(mn==0){cout<<p2[n]<<endl; return;}
//        sum=0;
//        ru(i,0,n){
//            sum+=arr[i];
//            if(sum==mn) ans=(ans+p2[n-i-1+abses])%mod;
//            if(sum>=0)++abses;
//        }; cout<<ans<<endl;
//    }
//    int main(){
//        p2[0]=1;
//        ru(i,1,maxn) p2[i]=2*p2[i-1]%mod;
//        int t; cin>>t; while(t--)solve();
//        return 0;
//    }
};
struct d{
    vector<int> z_function(string s){
        int n=s.size(); vector<int> z(n); int l=0,r=0;
        ru(i,1,n){
            if(i<r) z[i]=min(r-i,z[i-l]);
            while(i+z[i]<n&&s[z[i]]==s[i+z[i]]) ++z[i];
            if(i+z[i]>r) l=i, r=i+z[i];
        }; return z;
    }
    void solve(){
        int n; string s; cin>>s; n=s.length(); vector<int> nona(n,n);
        rd(i,n-1,0){
            if(s[i]!='a') nona[i]=i;
            else if(i+1<n) nona[i]=nona[i+1];
        }
        if(nona[0]==n){cout<<n-1<<endl; return;}
        string s2=""; int i1=nona[0]; ru(i,i1,n) s2+=s[i];
        vector<int>z=z_function(s2);
        ll ans=0;
        for(int len=1;i1+len<=n;len++){
            int cur=i1+len; int mn=i1; bool works=true;
            while(cur<n){
                if(nona[cur]==n) break;
                int bt=nona[cur]-cur; mn=min(mn, bt); cur+=bt;
                if(z[cur-i1]<len){works=false; break;}
                cur+=len;
            }
            if(works) ans+=mn+1;
        }; cout<<ans<<endl;
    }
    int main(){int t;cin>>t;while(t--)solve();}
};
struct e{ // graph + iterate
    int n; vector<vector<int>> adj; vector<pii> edges; map<pii,int> mp;
    vector<vector<int>> dp; vector<vector<int>> from; vector<int>miss;
    void dfs(int e){
        if(dp[0][e]>=0||dp[1][e]>=0) return;
        int p=edges[e].first, v=edges[e].second;
        dp[0][e]=0, dp[1][e]=1;
        if(miss[v]<0){
            for(int u:adj[v]){
                if(u==p) continue; int ne=mp[{v,u}];
                dfs(ne);
                from[0][v]+=max(dp[1][ne], dp[0][ne]);
                from[1][v]+=dp[0][ne];
            }; miss[v]=p;
        }
        if(miss[v]!=p && miss[v]!=n){
            int ne=mp[{v, miss[v]}];
            dfs(ne);
            from[0][v]+=max(dp[1][ne], dp[0][ne]);
            from[1][v]+=dp[0][ne];
            miss[v]=n;
        }
        if(miss[v]==n){
            int nne=mp[{v,p}];
            dp[0][e]+=from[0][v]-max(dp[1][nne], dp[0][nne]);
            dp[1][e]+=from[1][v]-dp[0][nne];
        } else if(miss[v]==p){
            dp[0][e]+=from[0][v];
            dp[1][e]+=from[1][v];
        }
    }
    void solve(){
        cin>>n; adj.clear(), edges.clear(); adj.resize(n), edges.resize(2*n-2);
        ru(i,0,n-1){
            int a,b; cin>>a>>b;a--,b--;
            adj[a].push_back(b); adj[b].push_back(a);
            edges[2*i]={a,b}; edges[2*i+1]={b,a};
            mp[{a,b}]=2*i; mp[{b,a}]=2*i+1;
        }
        from=vector<vector<int>>(2,vector<int>(n)); miss=vector<int>(n,-1);
        dp=vector<vector<int>>(2, vector<int>(2*n-2,-1));
        ru(i,0,n*2-2) dfs(i);
        int ans=0;
        ru(i,0,n){
            if(adj[i].size()!=1) continue; int e=mp[{i,adj[i][0]}];
            ans=max(ans,1+max(dp[0][e], dp[1][e]));
        };cout<<ans<<endl;
    };
    int main(){int t;cin>>t;while(t--)solve();}
};
struct f{ // math, brute+dp
    static const int INF=998244353;
    void solve(){
        int n; cin>>n; int B; cin>>B; string s; cin>>s; s="P"+s+"S";
        vector<ll> b(n+2); ru(i,0,n) cin>>b[i+1]; ll ans=0; set<ll> done;
        ru(i,0,n+1){
            ll sum=b[i]+b[i+1]; if(done.count(sum)) continue;
            int dp[n+2][2];
            ru(j,0,n+2) ru(k,0,2) dp[j][k]=-1;
            dp[0][0]=1;
            ru(j,1,n+2){
                bool tr[2]; tr[0]=tr[1]=true;
                if(s[j]=='P') tr[1]=false;
                else if(s[j]=='S') tr[0]=false;
                if(abs(b[j]-b[j-1])<=B)
                    ru(k,0,2) if(dp[j-1][k]>-1&&tr[k]) dp[j][k]=dp[j-1][k];

                if(dp[j-1][0]>-1&&tr[1]&&sum==b[j]+b[j-1]) {
                    if (dp[j][1] < 0) dp[j][1] = 0;
                    dp[j][1]=(dp[j][1]+dp[j-1][0])%INF;
                }
                if(dp[j-1][1]>-1&&tr[0]){
                    ll add=b[j]+b[j-1]-sum; ll large=max(abs(add/2),abs(add-add/2));
                    if(large<=B){if(dp[j][0]<0) dp[j][0]=0; dp[j][0]=(dp[j][0]+dp[j-1][1])%INF;}
                }
            }
            if(dp[n+1][1]<0)continue;
            ans=(ans+dp[n+1][1])%INF;
            done.insert(sum);
        };cout<<ans<<endl;
    };
    int main(){int t;cin>>t;while(t--)solve();}
};

struct g{ // permute sort

};
struct h{ // geometry combination

};

int main(){
//    a a;
//    a.main();
//    b b;
//    b.main();
//    c c;
//    c.main();
//    d d;
//    d.main();

//    e e;
//    e.main();

    f f;
    f.main();

}