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
            int n,m; cin>>n>>m; string a,b; cin>>a>>b;
            if(n<m) {cout<<"no\n"; continue;}
            bool same=true;
            ru(i,1,b.size()){
                if(a[i+n-m]!=b[i]){same=false; break;}
            }
            if(!same){
                cout<<"no\n"; continue;
            }
            ru(i,0,n-m+1){
                if(a[i]==b[0]) same=false;
            }
            if(same) cout<<"no\n";
            else cout<<"yes\n";
        }
    }
};
struct b{
    static const int N=3e4+5; int num[N];
    int main(){
        int t;cin>>t;
        while(t--){
            int n,x; cin>>n>>x; ru_(i,1,n)cin>>num[i];
            int n_min=num[1]; int n_max=num[1]; int res=0;
            ru_(i,2,n){
                if(num[i]>n_max) n_max=num[i];
                if(num[i]<n_min) n_min=num[i];
                if(n_max-n_min>2*x){res++; n_min=n_max=num[i];}
            }
            cout<<res<<endl;
        }
    }
};
struct c{
    static const int N=5e4+5;
    int a[N], k;
    struct str{int x,y;}t[N];
    int main(){
        int T;cin>>T;
        while(T--){
            int k;k=0; int n,m; cin>>n>>m; ru_(i,1,m)cin>>a[i];
            sort(a+1,a+1+m); ru_(i,2,m)t[++k]={a[i]-a[i-1]-1,2};
            int num_tmp=a[1]+n-a[m]-1;
            if(num_tmp>0) t[++k]={num_tmp,2};
            sort(t+1,t+1+k,[](str a,str b){return a.x>b.x;});
            ll ans=0,cnt=0;
            ru_(i,1,k){
                if(t[i].x-cnt*2>0){
                    int num_tmp=max(1ll,t[i].x-cnt*2-1);
                    ans+=num_tmp;
                }
                cnt+=2;
            }
            cout<<n-ans<<endl;
        }
    }
};
struct d{
    static const int N=5e4+5;
    vector<ll> num[N];
    map<ll,ll> val_to_index;
    int main(){
        int t;cin>>t;
        while(t--){
            int n,m; val_to_index.clear(); cin>>n>>m;
            ll num_tmp;
            ru_(i,1,n){
                num[i].clear(); num[i].push_back(0);
                ru_(j,1,m){
                    cin>>num_tmp; num[i].push_back(num_tmp);
                }
            }
            ll res_tmp=-1;
            for(ll i=1;i<=n;i++){
                ll val=0;
                for(ll j=1;j<=m;j++) val+=(j*num[i][j]);
                if(val_to_index.find(val)!=val_to_index.end()){
                    res_tmp=val; val_to_index[val]=-1;
                } else val_to_index[val]=i;

            }
            assert(val_to_index.size()==2);
            for(auto &item: val_to_index){
                if(item.second!=1ll){
                    cout<<item.second<< ' ' <<abs(res_tmp-item.first)<<endl;
                }
            }
        }
    }
};

struct e{ // graph
    static const int N=5e4+5,M=998244353;
    int u,v,mx,r;
    int a[N],d[N],q[N],b[N],tmp[N];
    vector<int> g[N],z[N];
    ll s[N];
    int main(){
        int t;cin>>t;
        while(t--){
            int n,m; cin>>n>>m;
            ru_(i,1,n){
                cin>>a[i]; g[i].clear(); z[i].clear(); d[i]=0; tmp[i]=0; s[i]=0;
            }
            ru_(i,1,m){
                cin>>u>>v; ++d[u]; g[u].push_back(v); z[v].push_back(u);
            }
            auto NEX=[&](int M)->void{
                ru_(i,1,n){
                    if(b[i]){
                        tmp[i]+=b[i]-1;
                        for(auto it:g[i]) ++tmp[it];
                    }
                }
                ru_(i,1,n){
                    if(tmp[i]>=M) b[i]=tmp[i]%M+M;
                    else b[i]=tmp[i]%M;
                    tmp[i]=0;
                }
            };
            auto calc=[&](int M)->int{
                ru_(i,1,n) b[i]=a[i];
                ru_(i,1,n) {
                    bool fl=false;
                    ru_(j,1,n) if(b[j]) fl=true;
                    if(!fl) return i-1;
                    NEX(M);
                } return n;
            };
            mx=calc(M);
            if(mx<n){cout<<mx<<endl; continue;}
            r=0; ru_(i,1,n)if(!d[i])q[++r]=i;
            s[q[1]]=1;
            ru_(i,1,r){
                s[q[i]]%=M;
                for(auto it: z[q[i]]){
                    --d[it]; s[it]+=s[q[i]];
                    if(!d[it]) q[++r]=it;
                }
            }
            ll ans=n;
            ru_(i,1,n) ans=(ans+s[i]*b[i])%M;
            cout<<ans<<endl;
        }
    }
};
struct f{ // sg
    static const int N=5e4+5;
    int f[N],vis[N];
    int main(){
        ru_(i,1,1000){
            ru_(j,0,i-2) vis[f[j]^f[i-2-j]]=1;
            int j;
            for(j=0;vis[j];j++);
            f[i]=j;
            ru_(j,0,i) vis[j]=0;
        }
        ru(i,1001,N) f[i]=f[i-34];
        int t;cin>>t;
        while(t--){
            int n; char c[N]; cin>>n>>c+1; int s=0;
            ru_(i,1,n){
                if(c[i]=='R')++s;
                else --s;
            }
            if(s>0) puts("Alice");
            if(s<0) puts("Bob");
            if(s==0){
                int ans=0;
                ru_(i,1,n){
                    int j=i+1;
                    for(;j<=n&&c[j]!=c[j-1];++j) ans^=f[j-i];
                    i=j;
                }
                puts(ans?"Alice":"Bob");
            }
        }
    }
};
struct g{ // fft

};