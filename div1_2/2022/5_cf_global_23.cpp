#include <bits/stdc++.h>
#define ru_(i,l,r) for(int i=(l);i<=(r);i++)
#define ru(i,l,r) for(int i=(l);i<(r);i++)
#define rd_(i,r,l) for(int i=(r);i>=(l);i--)
#define rd(i,r,l) for(int i=(r);i>(l);i--)
#define ll long long
#define pli pair<ll,int>
#define s1 first
#define s2 second

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
            int n,k;cin>>n>>k; int sum=0;
            ru(i,0,n) {int a; cin>>a; sum+=a;}
            if(sum>0) cout<<"yes"<<endl;
            else cout<<"no"<<endl;
        } return 0;
    }
};
struct b{
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n; int A[n],cnt[2][n+1]; cnt[0][0]=cnt[1][0]=0;
            ru(i,0,n){
                cin>>A[i]; cnt[0][i+1]=cnt[0][i]+(A[i]==0?1:0);
                cnt[1][i+1]=cnt[1][i]+(A[i]==1?1:0);
            }
            int ans=n-1;
            ru_(l,0,n) ans=min(ans,max(cnt[1][l],cnt[0][n]-cnt[0][l]));
            cout<<ans<<endl;
        }
    }
};
struct c{
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n; int per[n],loc[n];
            ru(i,0,n){
                cin>>per[i]; per[i]--; loc[per[i]]=i;
            }
            ru(i,0,n){
                if(loc[i]==n-1) cout<<rand()%n+1<<(i==n-1?'\n':' ');
                else cout<<loc[i]+1<<(i==n-1?'\n':' ');
            }
        }
    }
};
struct d{
    static const int N=2e4; ll V[N],dp[N]; int dad[N];
    vector<int> child[N]; vector<pair<int,ll>>ans[N];
    int main(){
        int t;cin>>t;
        while(t--){
            ll n,k; cin>>n>>k; ru(i,0,n) child[i].clear(),ans[i].clear();
            dad[0]=0;
            ru(i,0,n-1){
                cin>>dad[i+1]; dad[i+1]--; child[dad[i+1]].push_back(i+1);
            }
            ru(i,0,n) cin>>V[i];
            function<ll(int v,ll k)> dfs=[&](int v,ll k)->ll{
                for(auto[kp,a]:ans[v]) if(k==kp) return a;
                ll cnt_child=(ll)child[v].size(); ll a=k*V[v];
                if(cnt_child==0) return a;
                if(k%cnt_child==0) for(auto u:child[v]) a+=dfs(u,k/cnt_child);
                else {
                    ll dp1[cnt_child], dp2[cnt_child], diff[cnt_child];
                    ru(i,0,cnt_child) dp1[i]=dfs(child[v][i],k/cnt_child), dp2[i]=dfs(child[v][i],k/cnt_child+1);
                    ru(i,0,cnt_child) diff[i]=dp2[i]-dp1[i];
                    sort(diff, diff+cnt_child, greater<int>());
                    ru(i,0,cnt_child) a+=dp1[i];
                    ru(i,0,k%cnt_child) a+=diff[i];
                }
                ans[v].push_back({k,a}); return a;
            };
            return dfs(0,k);
        }
    }
};
struct e{ //

};
struct f{ // fenwick

};
struct g{ // interactive

};