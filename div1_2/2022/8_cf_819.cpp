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
            int n;cin>>n; int A[n];int ans=-1e8-9; ru(i,0,n)cin>>A[i];
            ru(i,0,n)ans=max(ans,A[(i-1+n)%n]-A[i]);
            ru(i,1,n)ans=max(ans,A[i]-A[0]);
            ru(i,1,n-1)ans=max(ans,A[n-1]-A[i]);
            cout<<ans<<endl;
        }
    }
};
struct b{
    int main(){
        int t;cin>>t;
        while(t--){
            int n,m; cin>>n>>m;
            if(((n%2==0)&&(m%2==1))||(m<n)) cout<<"no\n";
            else if((n%2)==1){
                cout<<"yes\n";
                ru(i,1,n) cout<<"1";
                cout<<m-n+1<<endl;
            } else{
                cout<<"yes\n";
                ru(i,2,n) cout<<"1";
                cout<<(m-n+2)/2<<' '<<(m-n+2)/2<<endl;
            }
        }
    }
};
struct c{
    int main(){
        int t;cin>>t;
        while(t--){
            int n;string s; cin>>n>>s; n<<=1;
            int ans=1;
            ru(i,1,n){
                if(s[i]=='('&&s[i-1]=='(') ++ans;
            } cout<<ans<<endl;
        }
    }
};
struct d{
    int main(){
        int t;cin>>t;
        while(t--){
            int n,m; cin>>n>>m;
            vector<vector<pair<int,int>>> g(n+1); vector<pair<int,int>>edges(m); string s(m,'0');
            ru(i,0,m){
                int u,v; cin>>u>>v; edges[i]={u,v}; g[u].push_back({v,i}); g[v].push_back({u,i});
            }
            vector<bool>vis(n+1,false); vector<int>dep(n+1,0), par(n+1,-1);
            function<void(int,const vector<vector<pair<int,int>>>&,vector<bool>&,vector<int>&, vector<int>&, string&)> dfs=[&](int u,const vector<vector<pair<int,int>>>& g,vector<bool>& vis, vector<int>& dep, vector<int>& par, string& s)->void{
                vis[u]=true;
                for(auto [v,idx]:g[u]){
                    if (vis[v]) continue;
                    dep[v]=dep[u]+1;
                    par[v]=u;
                    s[idx]='1';
                    dfs(v,g,vis,dep,par,s);
                }
            };
            dfs(1,g,vis,dep,par,s); map<int,int>cnt;
            ru(i,0,m){
                if(s[i]=='0') {
                    cnt[edges[i].first]++;
                    cnt[edges[i].second]++;
                }
            }
            if(cnt.size()==3){
                int mn=2*n+5,mx=0;
                for(auto [_,c]:cnt){
                    mx=min(mn,c); mx=max(mx,c);
                }
                if(mn==mx&&mn==2){
                    vector<pair<int,int>> can;
                    for(auto [v,_]:cnt) can.push_back({dep[v],v});
                    sort(can.rbegin(),can.rend());
                    int u=can[0].second; int i,j;
                    for(auto [v,idx]:g[u]){
                        if(s[idx]=='0')i=idx;
                        else if(v==par[u]) j=idx;
                    }
                    s[i]='1'; s[j]='0';
                }
            }
            cout<<s<<endl;
        }
    }
};
struct e{ // fft
    static const int N=3e4+5;
    const ll mod = 998244353;
    const ll root = 15311432; // which is basically 3 ^ 119
    const ll root_1 = 469870224;
    const ll root_pw = (1 << 23);
    ll fact[N+1], ifact[N+1], sum_pow[N+1];
    void init_fact(){
        fact[0]=ifact[0]=1;
        ru_(i,1,N){
            fact[i]=fact[i-1]*i%mod;
            ifact[i]=inverse(fact[i]);
        }
    }
    ll fxp(ll a,ll n){
        if(!n) return 1;
        else if(n&1) return a*fxp(a,n^1)%mod;
        else {
            ll v=fxp(a,n>>1);
            return v*v%mod;
        }
    }
    ll inverse(ll a) {return fxp(a%mod, mod-2);}
    void fft(vector<ll>&a, bool invert){
        int n=a.size();
        for(int i=1,j=0;i<n;i++){
            int bit=n>>1;
            for(;j&bit;bit>>=1) j^=bit;
            j^=bit;
            if(i<j) swap(a[i],a[j]);
        }
        for(int len=2;len<=n;len<<=1){
            ll wlen=invert?root_1:root;
            for(int i=len;i<root_pw;i<<=1){
                wlen=wlen*wlen%mod;
            }
            for(int i=0;i<n;i+=len){
                ll w=1;
                for(int j=0;j<len/2;j++){
                    ll u=a[i+j],v=a[i+j+len/2]*w%mod;
                    a[i+j]=u+v<mod?u+v:u+v-mod;
                    a[i+j+len/2]=u-v>=0?u-v:u-v+mod;
                    w=w*wlen%mod;
                }
            }
        }
        if(invert){
            ll n_1=inverse(n);
            for(ll& x:a) x=x*n_1%mod;
        }
    }
    int main(){
        vector<ll> P(100);
        auto mul=[&](vector<ll> const& a, vector<ll> const & b)->vector<ll>{ // multiplying two polynomials a and b using ntt in O(max(A, B)log(max(A, B))), where A, B are degrees of a, b respectively
            vector<ll> fa(a.begin(),a.end()), fb(b.begin(),b.end());
            int n=1; while(n<(int)a.size()+(int)b.size()) n<<=1;
            fa.resize(n); fb.resize(n);
            fft(fa,false); fft(fb,false);
            ru(i,0,n) fa[i]=fa[i]*fb[i]%mod;
            fft(fa,true);
            while(fa.size()>1&&fa[fa.size()-1]==0) fa.pop_back();
            return fa;
        };
        auto init=[&]()->void{ // P(x)=e^(x+x(x^2)/2)
            init_fact(); vector<ll>e_x(N), e_x2_by2(N);
            ll modular_inverse_of_2=(mod+1)/2;
            ru(i,0,N){
                e_x[i]=ifact[i];
                e_x2_by2[i]=((i&1))?0:ifact[i/2]*fxp(modular_inverse_of_2,i/2)%mod;
            }
            P=mul(e_x, e_x2_by2);
        };
        init();
        int t;cin>>t;
        while(t--){
            int n;cin>>n; ll ans=0;
            ru_(s,0,n/4) ans=(ans+fact[n-2*s]*ifact[s]%mod*P[n-4*s])%mod;
            cout<<ans<<endl;
        }
    }
};

struct f{ // graph

};
struct g{ // seg

};
#define lli long long int
#define lld long double
struct h{ // geometry
    const lld PI=acos(-1.0);
    const int ITERATIONS = 60;
    const int PRECISION = 11;
    struct Point{
        lli x,y;
        Point& operator-=(const Point& rhs){
            x-=rhs.x, y-=rhs.y; return *this;
        }
        friend Point operator-(Point lhs,const Point& rhs){
            lhs-=rhs; return lhs;
        }
    };
    lld norm(Point p){return p.x*p.x+p.y*p.y;}
//    lld getalpha(Point a,Point b,Point c){return atan2l(cross_product(c-b,a-b),dot_product(c-b,a-b));}
//    int main(){
//        int n;cin>>n; vector<Point> v(n); for(auto& p:v) cin>>p;
//        if(n==4){
//            int MY=max({v[0].y,v[1].y,v[2].y,v[3].y});
//            int my=min({v[0].y,v[1].y,v[2].y,v[3].y});
//            int MX=max({v[0].x,v[1].x,v[2].x,v[3].x});
//            int mx=min({v[0].x,v[1].x,v[2].x,v[3].x});
//            if(MY-my==1||MX-mx==1){
//                cout<<fixed<<setprecision(PRECISION)<<1.0*(MY-my)*(MX-mx)<<endl; exit(0);
//            }
//        }
//        double ans=0;
//        ru(i,0,n) ans+=getarea(v[(i-1+n)%n],v[i],v[(i+1)%n]);
//        ru(i,0,n){
//            Point a=v[(i-1+n)%n],b=v[i],c=v[(i+1)%n],d=v[(i+2)%n];
//            if(norm(c-b)<3){
//                ans-=find_overlap_area(getalpha(a,b,c),getalpha(b,c,d),sqrt(norm(c-b)));
//            }
//        }
//        cout<<fixed<<setprecision(PRECISION)<<ans;
//        return 0;
//    }
};