#include <bits/stdc++.h>
#define ru(i,l,r) for(int i=(l);i<=(r);i++)
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
            int n,k; cin>>n>>k;
            cout<<1+(n-1)*k<<endl;
        }; return 0;
    }
};
struct b{
    int main(){
        int t; cin>>t;
        while(t--){
            int n; cin>>n;
            vector<int> a(n);
            ru(i,0,n) cin>>a[i];
            ll pref_max=0,s=0,mx=0;
            ru(i,0,n){
                pref_max=max(pref_max,(ll)a[i]);
                ll d=pref_max-a[i]; s+=d; mx=max(mx,d);
            }
            cout<<s+mx<<endl;
        }
    }
};
struct c{
    int main(){
        int t; cin>>t;
        while(t--){
            int n; cin>>n; vector<int>h(n); for(auto &x:h) cin>>x;
            int ans=h[n-1];
            rd(i,n-2,0) ans=max(ans+1,h[i]);
            cout<<ans<<endl;
        }
    }
};
struct d{
    static const int inf=1e4;
    void solve(){
        vector<int> a;
        {int n; cin>>n; map<int,int> cnt; while(n--){int x; cin>>x; cnt[x]++;}
        for(auto const &[k,v]: cnt) a.push_back(v);}
        int n = a.size(); vector<int> dp(n+1,inf); dp[0]=0;
        ru(i,1,n){
            vector<int> ndp=dp;
            ru(k,1,n){
                int nv=dp[k-1]+a[i+1]; if(nv<=i-k) ndp[k]=min(ndp[k],nv);
            }
            dp=ndp;
        }
        int ans=n; while(dp[ans]>=inf)ans--; cout<<n-ans<<endl;
    }
    int main(){int t; cin>>t; while(t--) solve();}
};
struct e{
    static const ll inf=1e4;
    void solve(){
        int n; cin>>n; vector<int>a(n); for(auto &x:a) cin>>x;
        vector<int>d(n); vector<vector<int>> g(n);
        ru(i,1,n){int p;cin>>p;p--;g[p].push_back(i);d[i]=d[p]+1;}
        vector<ll>b(n);
        ru(v,0,n){
            if(g[v].empty()) b[v]=inf;
            else {b[v]=-a[v]; for(int u:g[v]) b[v]+=a[u];}
        }
        ll ans=0;
        for(int v=n-1;v>=0;v--){
            queue<int>q; q.push(v);
            while(!q.empty()){
                int i=q.front(); q.pop();
                for(int u:g[i]){
                    ll delta=min(-b[v],b[u]);
                    if(delta>0) {b[v]+=delta; b[u]-=delta; ans+=delta*(d[u]-d[v]);}
                    q.push(u);
                }
            }
        };
        cout<<ans<<endl;
    }
    int main(){int t; cin>>t; while(t--) solve();}
};
struct f{
    static const int inf=1e4;
    void solve(){
        int n; cin>>n; vector<int> a(n); ru(i,0,n) cin>>a[i];
        vector<vector<int>> dp(n+1,vector<int>(n+1,inf));
        ru(i,0,n) dp[i][i]=0;
        for(int le=1;le<=n;le++){
            for(int l=0;l+le<=n;l++){
                if(a[l]%2!=(l+1)%2) continue;
                if(a[l]>l+1) continue;
                int v=(l+1-a[l])/2;
                int r=l+le;
                for(int m=l+1;m<r;m+=2){
                    if(dp[l+1][m]<=v){
                        int new_val=max(v,dp[m+1][r]-(m-l+1)/2);
                        dp[l][r]=min(dp[l][r],new_val);
                    }
                }
            }
        }
        vector<int> dp2(n+1);
        ru(i,0,n){
            dp2[i+1]=dp2[i];
            ru(j,0,i){
                if(dp[j][i+1]<=dp2[j]) dp2[i+1]=max(dp2[i+1],dp2[j]+(i-j+1)/2);
            }
        }; cout<<dp2[n]<<endl;
    }
};
struct g{// string

};