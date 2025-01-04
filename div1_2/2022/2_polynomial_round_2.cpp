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
            int n;cin>>n; char c[1005];cin>>c+1; int u=0;
            ru_(i,1,n){
                bool fl=(c[i]=='1') && u;
                u^=(c[i]-'0');
                if(i!=1) putchar(fl?'-':'+');
            }
            putchar('\n');
        }
    }
};
struct b{
    int main(){
        int t;cin>>t;
        while(t--){
            int n,m,k; cin>>n>>m>>k; int fl=0;
            ru_(i,1,m){
                int a; cin>>a;
                if(a==(n+k-1)/k) fl++;
                if(a>(n+k-1)/k) fl=1<<30;
            }
            puts(fl<=(n-1)%k+1?"yes":"no");
        }
    }
};
struct c{
    int main(){
        static const int N=3e4+5;
        int t;cin>>t;
        while(t--){
            int n; char a[N]; cin>>n>>a+1; int ps[2]; ps[0]=ps[1]=0;
            ru(i,1,n){
                ps[a[i]-48]=i;
                if(a[i]=='0') printf("%d ",ps[1]+1);
                else printf("%d",ps[0]+1);
            }
            putchar('\n');
        }
    }
};
struct d{
    int main(){
        int t;cin>>t;
        while(t--){
            int n,m; cin>>n>>m; vector<vector<int>> A(n, vector<int>(m,0)); vector<int> sum(n,0);
            ru(i,0,n) ru(j,0,m) {cin>>A[i][j]; sum[i]+=A[i][j];}
            int tot=0; ru(i,0,n) tot+=sum[i];
            if(tot%n){puts("-1"); continue;} tot/=n;
            vector<tuple<int,int,int>> ans; vector<int> Vg,Vl; Vg.reserve(n),Vl.reserve(n);
            ru(j,0,m) {
                    ru(i,0,n) {
                        if (sum[i] < tot && A[i][j])Vg.push_back(i);
                        if (sum[i] < tot && !A[i][j]) Vl.push_back(i);
                    }
                    ru(i,0,(int)min(Vl.size(),Vg.size())){
                        ++sum[Vl[i]],--sum[Vg[i]];
                        ans.emplace_back(Vl[i],Vg[i],j);
                    }
                    Vl.clear(), Vg.clear();
            }
            printf("%d\n",(int)ans.size());
            for(auto [i,j,k]: ans) printf("%d %d %d\n",i+1,j+1,k+1);
        } return 0;
    }
};
struct e{ // tedukuri-recursive, treeDP
    static const int N=1e4+5;
    bool f[2][N];
    int main(){
        int n,d; cin>>n>>d;
        int t[N*2], nxt[N*2], cnt,h[n], a[N], b[N];
        auto add=[&](int x,int y)->void{t[++cnt]=y;nxt[cnt]=h[x];h[x]=cnt;};
        ru(i,1,n){int x,y; cin>>x>>y; add(x,y), add(y,x);}
        function<void(int,int,int)> dfs1=[&](int x,int fa, int dis){
            a[dis]=x;
            if(dis>d) b[x]=a[dis-d];
            else b[x]=1;
            for(int i=h[x];i;i=nxt[i]){
                if(t[i]==fa) continue;
                dfs1(t[i],x,dis+1);
            }
        };
        dfs1(1,0,1);
        ru(i,0,1){
            int num; cin>>num;
            ru_(j,1,num){ int x; cin>>x; f[i][x]=1, f[i^1][b[x]]=1;}
        }
        function<void(int,int,int)> dfs2=[&](int x,int fa,int tp){
            bool u=0;
            for(int i=h[x];i;i=nxt[i]){
                if(t[i]==fa) continue;
                dfs2(t[i],x,tp); u|=f[tp][t[i]];
            }
            f[tp][x]|=u;
        };
        ru_(i,0,1) dfs2(i,0,i);
        int ans=0; ru_(i,0,1) ru_(j,2,n) if(f[i][j])ans+=2;
        cout<<ans;
        return 0;
    }
};
struct f{
    int main(){
        static const int N=8e4+5, mod=998244353;
        int n;cin>>n; ll maxs=1e9, sum=0;
        ll a[N],b[N],c[N],cnt,s[N],d[N],cntd;
        ru_(i,1,n){
            cin>>a[i];
            if(a[i]!=3)cin>>b[i];
            if(a[i]==2)sum+=b[i];
            sum=min(sum,maxs);
            if(a[i]==3) b[i]=sum, sum=sum*2;
            sum=min(sum,maxs);
        }
        sum=0; ll res=1, ans=0;
        rd_(i,n,1){
            if(a[i]==2) sum+=b[i];
            else if(a[i]==3){
                if(b[i]==maxs) continue;
                if(b[i]==0) {res=res*2%mod; continue;}
                c[++cnt]=b[i];

            } else {
                b[i]-=sum; if(b[i]<=0) continue;
                ll su=0,r=b[i];
                ru_(j,1,cnt){
                    if(r>c[j]) {
                        su=(su+(1ll<<(cnt-j)))%mod;
                        r-=c[j];
                    }
                }
                su=(su+1)%mod; ans=(ans+su*res)%mod;
            }
        } cout<<ans; return 0;
    }
};
struct g{ // segment

};