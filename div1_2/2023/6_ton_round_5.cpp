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
            int n,x; cin>>n>>x; int res=0;
            ru(it,0,3){
                vector<int>a(n);
                ru(i,0,n) cin>>a[i];
                for(int y:a){
                    if((y&x)!=y) break;
                    res|=y;
                }
            }
            cout<<(res==x?"yes":"no")<<endl;
        }
    }
};
struct b{
    int main(){
        int t;cin>>t;
        while(t--){
            int n,x,a[1000];cin>>n>>x; int s;
            ru(i,0,3){
                ru(j,0,n) cin>>a[j];
                ru(j,0,n){
                    if((x|a[j])!=x) break;
                    s |=a[j];
                }
            }
            if(s==x) cout<<"yes"<<endl;
            else cout<<"no"<<endl;
        }
    }
};
struct c{
    static const int N=2e4+5;
    int main(){
        int t;cin>>t;
        while(t--){
            int n,a[N],dp[N],buc[N]; cin>>n; dp[0]=0;
            ru_(i,1,n) buc[i]=0x3f3f3f3f;
            ru_(i,1,n) {
                cin>>a[i];
                dp[i]=min(dp[i-1]+1,buc[a[i]]);
                buc[a[i]]=min(buc[a[i]],dp[i-1]);
            }
            cout<<n-dp[n]<<endl;
        }
    }
};
struct d{
    int n,m; ll dis[100][100];
    int main(){
        cin>>n>>m; memset(dis,0x3f,sizeof dis);
        while(m--){
            int u,v,w; cin>>u>>v>>w, u--, v--;
            dis[u][v]=dis[v][u]=w;
        }
        ru(i,0,n) dis[i][i]=0;
        ru(k,0,n)ru(i,0,n)ru(j,0,n)dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
        if(dis[0][n-1]>1e18) cout<<"inf", exit(0);
        int ord[100]; iota(ord,ord+n,0);
        sort(ord+1,ord+n,[&](int a,int b){return dis[0][a]<dis[0][b];});
        string s(n,'0'); vector<pair<string,int>> ans;
        ru(i,0,n-1){
            int u=ord[i], v=ord[i+1];
            s[u]='1';
            ans.emplace_back(s,dis[0][v]-dis[0][u]);
            if(v==n-1)break;
        }
        cout<<dis[0][n-1]<<' '<<ans.size()<<endl;
        for(auto [s,t]:ans) cout<<s<<' '<<t<<endl;
    }
};
struct e{ //treelist
    static const int N=2e4+8,M=1<<18;
    int n,k,A,c[M<<1][2], dp[N]; vector<pair<int,int>>p[N];
    void insert(int i,int v){
        for(i+=M;i;i>>=1) c[i][0]=v, v=max(v,c[i^1][0]);
    }
    void add(int i,int v){
        for(i+=M+1;i>1;i>>=1){
            int v1=i&1?v:0;
            c[i^1][0]+=v1,c[i^1][1]+=v1;
            c[i>>1][0]=max(c[i][0],c[i^1][0])+c[i>>1][1];
        }
    }
    int main(){
        cin>>n>>k>>A;
        int sum=0;
        while(n--){
            int x,y,w; cin>>x>>y>>w;
            p[k-y].emplace_back(x,w);
            sum+=w;
        }
        ru_(i,1,k){
            add(i-1,-A);
            for(auto [x,w]:p[i])add(x,w);
            dp[i]=max(dp[i-1],c[1][0]);
            insert(i,dp[i]);
        }
        cout<<sum-dp[k]<<endl;
    }
};
struct f{ // bfs
    static const int N=5e3+8;
    int n,ans[N]; vector<int>G[N];
    void bfs(int u){
        static int q[N],dis[N];
        memset(dis,-1,sizeof dis);
        q[1]=u,dis[u]=0;
        for(int l=1,r=2;l<r;l++){
            u=q[l];
            for(int v:G[u]) if(dis[v]<0)
                dis[v]=dis[u]+1,q[r++]=v;
        }
        int sum=0;
        ru_(i,1,n){
            sum+=dis[q[i]];
            ans[i]=max(ans[i],(n-1)*i-sum*2);
        }
    }
    int main(){
        cin>>n;
        ru(i,0,n-1){
            int u,v;cin>>u>>v,u--,v--;
            G[u].push_back(v),G[v].push_back(u);
        }
        ru(i,0,n)bfs(i);
        ru_(i,0,n) cout<<ans[i]<<' ';
    }
};
struct g{
    static const int N=5e3+8,P=1e4+7;
    int n,m,v,a[N],coef[N],dp[N][N];
    ll Pow(ll a,ll b){
        ll r=1;
        while(n){
            if(n&1)r=r*a%P;
            a=a*a%P,n>>=1;
        }
        return r;
    };
    int main(){
        cin>>n>>m>>v; ru_(i,1,n)cin>>a[i];
        dp[0][0]=1;
        ru_(i,1,n){
            auto coef=i*Pow(n,P-2)%P*v%P;
            ru(j,0,i){
                dp[i][j+1]=dp[i-1][j]*coef%P*(m-j)%P;
                dp[i][j]=(dp[i][j]+dp[i-1][j]*(a[i]+1LL*j*v%P))%P;
            }
        }
        int ans=0;
        ru_(i,0,n) (ans+=dp[n][i])%=P;
        cout<<ans<<endl;
    }
};
struct h{
    static const int P=998244353;
    int n,m,G[20][2], f[1<<20];
    ll Pow(ll a,ll b){
        ll r=1;
        while(n){
            if(n&1)r=r*a%P;
            a=a*a%P,n>>=1;
        }
        return r;
    };
    inline void inc(int& a,int b){
        if((a+=b)>=P) a-=P;
    }
    int main(){
        cin>>n>>m;
        while(m--){
            int t,i,j; cin>>t>>i>>j;i--,j--;
            G[i][t]|=1<<j; G[j][t]|=1<<i;
        }
        f[0]=1;
        for(int S=0;S<1<<n;S++){
            for(int i=0;i<n;i++)
                if(~S>>i&1){
                    if((G[i][0]|S)==S)inc(f[S|1<<i],f[S]);
                    if((G[i][1]|S)==S)inc(f[S|1<<i],f[S]);
                }
        }
        ll t=1;
        ru_(i,1,n)t=t*i*2%P;
        cout<<f[(1<<n)-1]*Pow(t,P-2)%P<<endl;
    }
};
struct i{ //divide, conquer
    static const int N=5e4+8;
    int n,K,a[N],pre[N*2]; ll dp[N*2], ans;
    vector<int>trim(vector<int>a,int L,int R){
        return vector(a.begin()+L,a.end()-R);
    }
    vector<int> init(){
        static int q[N]; q[1]=0;
        for(int i=1,l=1,r=1;i<=n;i++){
            if(q[l]<i-K)l++;
            dp[i]=dp[q[l]]+a[i],pre[i]=q[l];
            while(l<=r&&dp[i]<dp[q[r]])r--;
            q[++r]=i;
        }
        ans=dp[n]; vector<int>res;
        for(int i=n;i;i=pre[i]) res.push_back(i);
        res.push_back(0), reverse(res.begin(),res.end());
        return res;
    }
    vector<int> solve(int first, vector<int> L, vector<int> R){
        dp[first]=a[first];
        int l=first, r=first;
        ll val; int p;
        auto checkMin=[&](int i){
            if(dp[i]<val) val=dp[i],p=i;
        };
        ru(i,0,L.size()){
            val=1e18,p=0;
            rd_(j,R[i],L[i]){
                for(;r>=max(l,j-K);r--) checkMin(r+i);
                dp[j+i+1]=val+a[j];
                pre[j+i+1]=p;
            }
            l=L[i],r=R[i];
        }
        val=1e18,p=0;
        for(int i=max(L.back(),n-K+first);i<=R.back();i++) checkMin(i+L.size());
        ans=min(ans,val); vector<int> res;
        for(int i=L.size();i;i--) res.push_back(p-i),p=pre[p];
        reverse(res.begin(),res.end());
        return res;
    }
    void divide(int l,int r,vector<int> L,vector<int> R){
        if(l>r)return;
        int mid=(l+r)>>1;
        auto M=solve(mid,L,R);
        divide(l,mid-1,L,M), divide(mid+1,r,M,R);
    }
    void divide(vector<int> p){
        p.push_back(n),divide(1,p[0],trim(p,0,1),trim(p,1,0));
    }
    int main(){
        int t;cin>>t;
        while(t--){
            cin>>n>>K;ru_(i,1,n)cin>>a[i];
            a[0]=a[n];
            auto p=init();
            divide(trim(p,1,1));
            divide(solve(0,trim(p,0,1),trim(p,1,0)));
            if((p.size()-2)*K>=n)
                divide(solve(0,trim(p,1,2),trim(p,2,1)));
            cout<<ans<<endl;
        }
    }
};