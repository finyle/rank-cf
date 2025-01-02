#include <bits/stdc++.h>
#define ru_(i,l,r) for(int i=(l);i<=(r);i++)
#define ru(i,l,r) for(int i=(l);i<(r);i++)
#define rd_(i,r,l) for(int i=(r);i>=(l);i--)
#define rd(i,r,l) for(int i=(r);i>(l);i--)
#define ll long long
#define pli pair<ll,int>
#define s1 first
#define s2 second
//#define mod 998244353

using namespace std;
#ifdef LOCAL
#include 'algo/debug.h'
#else
#define debug(...)
#endif

//ios::sync_with_stdio(0); cin.tie(0);

struct a{
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n;
            int minv=1e9+1, maxv=-1,mini,maxi;
            ru(i,0,n){
                int a;cin>>a;
                if(a>maxv){
                    maxi=i+1; maxv=a;
                }
                if(a<minv){
                    mini=i+1; minv=a;
                }
            }
            cout<<mini<<" "<<maxi<<endl;
        }
    }
};
struct b{
    int main(){
        int t;cin>>t;
        while(t--){
            int n,a; vector<int>v(n);
            for(int &x:v)cin>>x;
            bool ans=false;
            if(n==1)ans=(v[0]==a);
            else {
                sort(v.begin(),v.end());
                int i=0,j=1;
                while(j<n and i<n){
                    if(v[i]+abs(a)==v[i]){
                        if(v[i]+abs(a)==v[j]){
                            ans=true; break;
                        } else if(v[i]+abs(a)<v[j])++i;
                        else ++j;
                    }
                }
            }
            cout<<(ans?"yes":"no")<<endl;
        }
    }
};
struct c{
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n; vector<int>a(n); ru(i,0,n) cin>>a[i];
            sort(a.begin(),a.end());
            bool one=false, consec=false;
            ru(i,0,n){
                if(a[i]==1)one=true;
                if(i<n-1&&a[i]+1==a[i+1])consec=true;
            }
            cout<<((one&&consec)?"no":"yes")<<endl;
        }
    }
};
struct d{
    int main(){
        int t;cin>>t;
        while(t--){
            ll n; cin>>n; ll x=n;
            while(x%2==0)x/=2;
            if(x==1) cout<<-1<<endl;
            else if(x<=2e9&&(x*(x+1))/2<=n) cout<<x<<endl;
            else cout<<2*(n/x)<<endl;
        }
    }
};
struct e{  // graph
    vector<int>ans; vector<vector<int>>al;
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n;
            ru(i,0,n-1){
                int u,v; cin>>u>>v; u--,v--;
                al[u].push_back(v); al[v].push_back(u);
            }
            function<void(int,int,int)> dfs=[&](int u,int p,int c)->void{
                ans[u]=((int)al[u].size())*c;
                for(int v: al[u]){
                    if(v!=p) dfs(v,u,-c);
                }
            };
            dfs(0,-1,1);
            ru(i,0,n){
                cout<<ans[i];
                if(i<n-1)cout<<" ";
            } cout<<endl;
        }
    }
};

struct f{  // greedy
    int main(){
        int t;cin>>t;
        while(t--){
            ll n;cin>>n; vector<int>a(n); ll tsum=0; ru(i,0,n){cin>>a[i]; tsum+=a[i];}
            sort(a.begin(),a.end());
            if(a[n-1]*(n-2)+tsum<0||a[0]*(n-2)+tsum>0){
                cout<<"INF"<<endl; continue;
            }
            ll cslope=a[n-1]*(n-2)+tsum;
            ll cvalue=-(n-1)*a[n-1]*a[n-1];

            ll ans=cvalue;
            for(ll i=0;i<n;i++){
                ll d=a[n-i]-a[n-i-1];
                cvalue+=cslope*d;
                ans=max(ans,cvalue);
                cslope+=a[0]-a[n-1];
            }
            cout<<ans<<endl;
        }
    }
};

struct g{ // graph, cycle(dsu)

};

struct h{ // gcd. lcm
};
struct i{ // graph,
    struct graph{
        int n,m; vector<vector<int>> al; vector<int> morphism;
    };
    graph read_graph(){
        graph g; int n,m; cin>>n>>m; g.n=n;g.m=m;
        g.al=vector<vector<int>>(n,vector<int>());
        g.morphism=vector<int>(n,0);
        ru(i,0,n){
            g.morphism[i]=i;
        }
        for(int i=0;i<m;i++){
            int u,v; cin>>u>>v;
            g.al[u].push_back(v);
            g.al[v].push_back(u);
        }
        return g;
    }
    vector<vector<int>> solve(graph& input_graph){
        vector<vector<int>> ans(input_graph.n);
        vector<graph> comp;
    }
    void print_ans(const vector<vector<int>>& ans){
        int n=ans.size();
        if(n==0) cout<<"no"<<endl;
        else {
            cout<<"yes"<<endl;
            ru(i,0,n){
                for(int x:ans[i]) cout<<x<<" ";
                cout<<endl;
            }
        }
    }
    int main(){
        int t;cin>>t;
        while (t--){
            graph input_graph=read_graph();
            vector<vector<int>> ans=solve(input_graph);
            print_ans(ans);
        }
    }
};

int main(){
    e e;e.main();
}