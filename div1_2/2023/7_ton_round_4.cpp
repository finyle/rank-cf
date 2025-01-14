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
            int n;cin>>n; bool ok=false;
            ru(i,0,n){
                int x; cin>>x;
                if(i+1>=x) ok=true;
            }
            cout<<(ok?"yes":"no")<<endl;
        }
    }
};
struct b{
    int main(){
        int t;cin>>t;
        while(t--){
            ll n;cin>>n; const int m=40; vector<int>ans(m,1);
            if(n%2==0){
                cout<<-1<<endl; continue;
            }
            ru(i,1,m){
                if((n-1)&(1LL<<i)) ans[m-i]=2;
            }
            cout<<m<<endl;
            ru(i,0,m) cout<<ans[i]<<" \n"[i==m-1];
        }
    }
};
struct c{
    int main(){
        int t;cin>>t;
        while(t--){
            int n;ll c,d;cin>>n>>c>>d; vector<int>a(n); ru(i,0,n)cin>>a[i];
            sort(a.begin(),a.end());
            ll ans=c*n+d; int rm=0;
            ru(i,0,n){
                if(i>0&&a[i]==a[i-1]) rm+=1;
                ll cur=c*(n-1-i+rm)+d*(a[i]-(i+1-rm));
                ans=min(ans,cur);
            }
            cout<<ans<<endl;
        }
    }
};
struct d{
    int main(){
        int t;cin>>t;
        while(t--){
            int q;cin>>q;
            auto Calc=[&](ll a,ll b, ll h)-> ll{
                if(h<=a) return 1LL;
                return 1LL+((h-a+(a-b-1))/(a-b));
            };
            ll low=1, high=(ll)2e18;
            while(q--){
                int op; cin>>op;
                if(op==1){
                    ll a,b,n;cin>>a>>b>>n;
                    ll R=(a-b)*(n-1)+a;
                    ll L=(n==1?1LL:(a-b)*(n-2)+a+1);
                    if(R<low||high<L) {
                        cout<<0<<endl; continue;
                    } else{
                        cout<<1<<endl; low=max(low,L); high=min(high,R);
                    }
                } else{
                    ll a,b; cin>>a>>b;
                    ll x=Calc(a,b,low), y=Calc(a,b,high);
                    if(x==y) cout<<x<<endl;
                    else cout<<-1<<endl;
                }
            }
        }
        return 0;
    }
};

struct e{ // strut内预定义数组长度上限 1e4; 题目范围通常为1e6;
    int n,m;
    vector<int>E[2005];
    int a[2005], vis[2005];
    bool span(int u){
        set<pair<int,int>>st; st.insert(pair<int,int>{a[u],u});
        int amt=0, df=0;
        while(st.size()){
            auto pa=(*st.begin()); vis[pa.second]=u;
            if(pa.first>df)return(amt==n);
            st.erase(st.begin());
            amt++; df++;
            for(auto v: E[pa.second]){
                if(vis[v]<u){
                    st.insert(pair<int,int>{a[v],v});
                }
            }
        } return (amt==n);
    }
    void solve(){
        cin>>n>>m;
        for(int i=1;i<=n;i++)cin>>a[i],vis[i]=0,E[i].clear();
        for(int i=1;i<=m;i++){
            int u,v; cin>>u>>v; E[u].push_back(v); E[v].push_back(u);
        }
        for(int i=1;i<=n;i++){
            if(a[i]==0&&!vis[i]){
                if(span(i)) {puts("yes"); return;}
            }
        } puts("no");
    }
    int main(){ios::sync_with_stdio(0); cin.tie(0);int t;cin>>t;while(t--)solve();}
};

#include "../../sum/codeforce-template/seg_mx_mn.cpp"
struct f{
    int main(){
        int t;cin>>t;
        while(t--){
            int n,m,q; cin>>n>>m>>q; vector<int>a(n);ru(i,0,n){cin>>a[i];--a[i];}
            segtree st(2*n+2);
            auto Add=[&](int i){
                int x=st.find_first(i,2*n+1,[&](const segtree::node& nd){
                    return nd.mn<m-1;
                });
                if(i<x) st.modify(i,x-1,-(m-1));
                st.modify(x,x,+1);
            };
            auto Remove=[&](int i){
                int x=st.find_first(i,2*n+1,[&](const segtree::node& nd){
                    return nd.mx>0;
                });
                if(i<x) st.modify(i,x-1,+(m-1));
                st.modify(x,x,-1);
            };
            ru(i,0,n) Add(a[i]);
            Remove(0);
            ru(it,0,q){
                int x,y;cin>>x>>y;--x,--y;
                Add(y); Remove(a[x]); a[x]=y;
                ll sum=st.get(0,2*n+1).sum;
                int p=st.find_first(0,2*n+1,[&](const segtree::node& nd){
                    if(nd.sum<sum){
                        sum-=nd.sum;
                        return false;
                    }
                    return true;
                });
                cout<<(n==1?1:p+2)<<" \n"[it==q-1];
            }
        } return 0;
    }
};
struct g{ // N 预定义数组长度 二维 1e2; 一维1e4
    static const int mod=1e9+7, N=505;
    int p[N],q[N],n,f[N][N],h[N];
    int fpow(int a,int b){
        int ans=1;
        while(b){
            if(b&1) ans=1LL*ans*a%mod;
            a=1LL*a*a%mod; b>>=1;
        } return ans;
    }
    void solve(){
        cin>>n;
        for(int i=1;i<=n;i++){
            int a,b;cin>>a>>b;
            p[i]=1LL*a*fpow(b,mod-2)%mod;
            q[i]=(1-p[i]+mod)%mod;
        }
        for(int i=0;i<=n;i++) cin>>h[i];
        for(int i=0;i<=n;i++) f[0][i]=h[i];
        for(int i=1;i<=n;i++){
            for(int j=0;j<=n;j++){
                f[i][j]=(1LL*p[i]*f[i-1][j+1]+1LL*q[i]*f[i-1][max(0,j-1)])%mod;
            }
            printf("%d ",f[i][0]);
        }
        printf("\n"); return;
    }
    int main(){int t;cin>>t;while(t--)solve();return 0;}
};
struct h{
    void solve(__int128 n, __int128 a, __int128 b, __int128 c, __int128 &f) {
        if (n < 0) { f = 0; return; }
        if (a >= c || b >= c) {
            solve(n, a % c, b % c, c, f);
            f += (a / c) * (n * (n + 1) / 2) + (b / c) * (n + 1);
        } else if (a) {
            __int128 m = (a * n + b) / c;
            solve(m - 1, c, c - b - 1, a, f);
            f = n * m - f;
        }
    }

    const long double k = (1 + sqrt((long double) 5)) / 2;

    int n;
    long long ans;
    __int128 a, b, c, d;

    int main() {
        int T;
        scanf("%d", &T);
        __int128 x = (__int128) 2000000000000000000ll * 1000000000;
        __int128 y = (__int128) 1000000000000000000ll * 1000000000;
        __int128 z = (__int128) 1618033988749894848ll * 1000000000 + 204586834;
        for (; T; T--) {
            scanf("%d", &n);
            int i = 0;
            for (int l = 0, r = n - 1, mid; l <= r; ) {
                mid = l + r >> 1;
                if (n - floor(mid / k) <= mid + mid) {
                    i = mid; r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            solve((n - 1) / 2, x, 0, z, a);
            solve((i - 1) / 2, x, 0, z, b);
            solve((n - 2) / 2, x, y, z, c);
            solve((i - 2) / 2, x, y, z, d);
            ans = i + (i % 2 ? -1 : 1) * ((a - b) - (c - d));
            if ((n - i) % 2) { ans = n - ans; }
            printf("%lld\n", ans);
        }
        return 0;
    }
};

int main(){
//    a a; a.main();
//    c c; c.main();

//    e e;e.main();
//    f f; f.main();
//    g g;g.main();
    h h;h.main();
}