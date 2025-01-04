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
            int n,m;cin>>n>>m;vector<ll>a(n+m);ru(i,0,n)cin>>a[i];
            sort(a.begin(),a.end()-1);
            reverse(a.begin(),a.end());
            ll ans=0; ru(i,0,n)ans+=a[i];
            cout<<ans<<endl;
        } return 0;
    }
};
struct b{
    int main(){
        int t;cin>>t;
        while(t--){
            int n,k; cin>>n>>k;
            int l=1,r=n,_=1;
            while(l<=r)
                cout<<((_^=1)?l++:r--)<<' ';
            cout<<endl;
        }
    }
};
struct c{
    static const int N=105;
    int cnt[N];
    int main(){
        int t;cin>>t;
        while(t--){
            int n,a[N]; cin>>n;ru_(i,1,n)cin>>a[i];
            int isDistinct=1; sort(a+1,a+n+1);
            ru(i,1,n) if(a[i]==a[i+1]) isDistinct=0;
            if (isDistinct==0) {cout<<"no"<<endl; continue;}
            int CRT_able=1;
            ru_(mod,2,n/2){
                fill(cnt,cnt+mod,0);
                ru_(i,1,n) cnt[a[i]%mod]++;
                if(*min_element(cnt,cnt+mod)>=2)CRT_able=0;
            }
            cout<<(CRT_able?"yes":"no")<<endl;
        }
    }
};
struct d{ // tedukuri-recursive, uf
    static const int N=1e4+5, P=998244353;
    int vertex, edge, self_loop;
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n; int a[N],b[N]; vector<int>G[N]; bool vis[N];
            ru_(i,1,n)cin>>a[i]; ru_(i,1,n)cin>>b[i]; ru_(i,1,n)G[i].clear();
            ru_(i,1,n){
                G[a[i]].push_back(b[i]); G[b[i]].push_back(a[i]);
            }
            function<void(int)> dfs=[&](int x) ->void{
                if(vis[x]) return; vis[x]=true; vertex++;
                for(auto y: G[x]) {
                    edge++;
                    dfs(y);
                    if(y==x) self_loop++;
                }
            };
            int ans=1;
            ru_(i,1,n) vis[i]=false;
            ru_(i,1,n){
                if(vis[i]) continue;
                vertex=0; edge=0; self_loop=0;
                dfs(i);
                if(edge!=2*vertex) ans=0;
                else if(self_loop) ans=1ll*ans*n%P;
                else ans=ans*2%P;
            }
        }
    }
};
struct e{  // math, tedukuri-recursive
    static const int N=3e4+5, mod=998244353, inv2=499122177;
    int a[N],u[N],v[N]; ll p[N]; vector<int>e[N];
    ll sum[N]; int fa[N];
    int main(){
        int n,k; cin>>n>>k; ru_(i,1,k){cin>>a[i]; p[a[i]]=1;}
        ru_(i,1,n-1){
            cin>>u[i]>>v[i]; e[u[i]].push_back(v[i]); e[v[i]].push_back(u[i]);
        }
        function<void(int,int)> dfs=[&](int u,int f){
            sum[u]=p[u];
            for(int v: e[u]) if(v!=f){
                dfs(v,u);
                fa[v]=u;
                sum[u]+=sum[v];
            }
        };
        dfs(1,-1); ll ans=0;
        auto qpow =[&] (ll n,ll m)->ll {
            ll ret=1;
            while(m){
                if(m&1) ret=ret*n%mod;
                n=n*n%mod; m>>=1;
            }
        };
        auto getinv = [&](ll a)->ll{return qpow(a,mod-2);};
        ru_(i,1,n-1){
            if(fa[u[i]]==v[i]) swap(u[i],v[i]);
            ll puv=p[u[i]]*(1-p[v[i]]+mod)%mod;
            ll pvu=p[v[i]]*(1-p[u[i]]+mod)%mod;
            ll delta=0;
            delta-=puv*sum[v[i]]%mod*(k-sum[v[i]])%mod;
            delta-=pvu*sum[v[i]]%mod*(k-sum[v[i]])%mod;
            delta+=puv*(sum[v[i]]+1)%mod*(k-sum[v[i]]-1)%mod;
            delta+=pvu*(sum[v[i]]-1)%mod*(k-sum[v[i]]+1)%mod;
            ans=(ans%mod+mod)%mod;
            p[u[i]]=p[v[i]]=1ll*(p[u[i]]+p[v[i]])*inv2%mod;
        }
        cout<<ans*getinv(1ll*k*(k-1)/2%mod)%mod<<endl;
    }
};
struct f{    // math, bit
    int main(){
        int n,a,b; cin>>n>>a>>b;
        int ans=0;
        auto isSub=[&](int i,int j)->bool{
            if(i<0||j<0) return false;
            return (j&i)==i;
        };
        for(int sub=b;sub;sub=(sub-1)&b){
            ru(bit,0,20){
                if(sub&(1<<bit)){
                    if(isSub(a-(1<<bit),n*sub-(1<<bit))) ans^=(1<<bit);
                }
            }
        }
        cout<<ans*(n%2)<<endl;
    }
};
struct g{   // fft , divideAndConquer
    static const int mod=998244353; vector<int> v;
    vector<ll> conv(const vector<ll>&a,const vector<ll>&b){
        if(a.empty()||b.empty()) return {};
        int s=a.size()+b.size()-1, B=32-__builtin_clz(s),n=1<<B;
        int inv
    }
    vector<int> solve(int l,int r,vector<int>poly){
        if(poly.empty()) return poly;
        if(l==r){
            poly=conv(poly,{1,1}); poly.erase(poly.begin(),poly.begin()+v[i]);
            return poly;
        }
        int m=l+r>>1, num=0; ru(x,l,r+1)num+=v[x]; num=min(num,poly.size());
        vector<int> small(poly.begin(),poly.begin()+num);
        vector<int> mul; ru(x,0,r-l+2)mul.push_back(nCk(r-l+1,x));
        poly=conv(poly,mul);

        small=solve(m+1,r,solve(l,m,small));
        poly.resize(max(poly.size(),small.size()));
        ru(x,0,small.size())poly[x]=(poly[x]+small[x])%mod; return poly;
    }
    int solve(string s){
        if(s=="")return 1; v.clear();
        int mn=0,curr=0;
        for(auto it:s){
            if(it=='(') curr++;
            else{
                curr--;
                if(curr<mn){mn=curr; v.push_back(1);}
                else v.push_back(0);
            }
        }
    }
    int main(){
        int n; string s; int pref[50005];cin>>s;n=s.size();pref[0]=0;
        ru(x,0,n)pref[x+1]=pref[x]+(s[x]=='('?1:-1);
        int pos=min_element(pref,pref+n+1)-pref;
        string a=s.substr(0,pos),b=s.substr(pos,n-pos);
        reverse(b.begin(),b.end()); for(auto &it:b) it^=1;
        cout<<solve(a)*solve(b)%mod<<endl;
    }
};