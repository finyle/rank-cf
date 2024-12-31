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
            int n; cin>>n;
            for(int i=1,nouse;i<=n;i++) cin>>nouse;
            cout<<"1 "<<n<<endl;
        }
    }
};
struct b{
    static const int maxn=1e4+5; int a[maxn];
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n; int tmp=0;
            ru_(i,1,n){
                cin>>a[i]; tmp=gcd(tmp,a[i]);
            }
            printf("%d\n",a[n]/tmp+(a[1]==0));
        } return 0;
    }
};
struct c{
    static const int maxn=2e4+5; int a[maxn];
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n; ru_(i,1,n)cin>>a[i]; sort(a+1,a+n+1);
            if(a[1]==a[n]){cout<<n/2<<endl; continue;}
            ll ans=0;
            for(int l=1,r=1;l<=n;l=r=r+1){
                while(r+1<=n&&a[r+1]==a[l]) ++r;
                ans=max(ans,1ll*(n-r)*r);
            }
            cout<<ans<<endl;
        } return 0;
    }
};
struct d{
    static const int mx=5e4+233;
    ll C[mx][mx], n,p,fac[mx];
    int main(){
        ll n,p; cin>>n>>p;
        auto init=[&]()->void{
            ru(i,0,mx)C[i][0]=1;
            ru(i,1,mx) ru(j,1,mx) C[i][j]=(C[i-1][j]+C[i-1][j-1])%p;
            fac[0]=fac[1]=1%p;
            ru(i,2,mx)fac[i]=fac[i-1]*i%p;
        };
        init();
        int t=n/2; ll ans=0;
        ru(i,t,n-1){
            if((n&1)&&i==n-1) break;
            int upper=(i==n-1)?n-i-1:n-i-2;
            ru_(j,0,upper) ans=(ans+n*(2*t-i)*C[upper][j]%p&fac[j+i-1])%p;
        }
        cout<<ans<<endl; return 0;
    }
};
struct e{
    static const int N=2e5+5;
    struct Goat{int x,y,id;}A[N];
    int mx[N], ans[N];
    int main(){
        int n,s;
        for(int i=1,x,y;i<=n;i++){
            cin>>x>>y; A[i]=(Goat){x,y,i}; ans[i]=false;
        }
        auto cmp=[&](Goat a,Goat b){return a.x<b.x;};
        sort(A+1,A+n+1,cmp); ru_(i,1,n)mx[i]=max(A[i].x+A[i].y,mx[i-1]);
        ru(i,1,n) if(A[i].x+A[i].y>=s) ans[A[i].id]=true;
        function<int(int)> calc=[&](int id) ->int{
            if(id==1) return A[id].x;
            int far=max(calc(id-1),mx[id-2]);
            return max(min(far,A[id].x)+A[id].y,A[id].x);
        };
        if(calc(n)>=s)ans[A[n].id]=true;
        puts(ans[1]?"yes":"no");
    }
};
struct f{
    static const int N=3e3+5; bool vis[N]; ll w[N][N], dis[N]; vector<int> e[N];
    int main(){
        int n; cin>>n; memset(w,-0x3f,sizeof w);
        ru_(i,1,n) ru_(j,1,i) {scanf("%lld",&w[i][j]); w[j][i]=w[i][j];}
        memset(dis,-0x3f,sizeof dis); dis[1]=0;
        ru_(i,1,n){
            int x=0;
            ru_(j,1,n) if(!vis[j]&&(!x||dis[j]>dis[x])) x=j;
            if(i!=1) ru_(j,1,n){
                if(w[j][x]==dis[x]&&vis[j]){
                    e[x].push_back(j); e[j].push_back(x);
                }
            }
            vis[x]=true;
            ru_(j,1,n) dis[j]=max(dis[j],w[x][j]);
        }
        int size[N];
        function<void(int,int)> dfs=[&](int x,int f){
            size[x]=1;
            for(auto i: e[x]){
                if(i==f) continue;
                dfs(i,x); size[x]+=size[i];
            }
            for(auto i: e[x]){
                if(i==f) continue;
                printf("%d %d %lld\n",x,i,(w[1][x]-w[1][i])/size[i]);
            }
        };
        dfs(1,1); return 0;
    }
};
struct g{ // interactive
};
struct h{

};