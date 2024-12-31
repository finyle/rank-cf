#include <bits/stdc++.h>
#define ru_(i,l,r) for(int i=(l);i<=(r);i++)
#define ru(i,l,r) for(int i=(l);i<(r);i++)
#define rd_(i,r,l) for(int i=(r);i>=(l);i--)
#define rd(i,r,l) for(int i=(r);i>(l);i--)
#define ll long long
#define pli pair<ll,int>
#define s1 first
#define s2 second
#define mod 998244353

using namespace std;
#ifdef LOCAL
#include 'algo/debug.h'
#else
#define debug(...)
#endif

//ios::sync_with_stdio(0); cin.tie(0);

struct a{
    int main(){
        int n,k; string str; cin>>n>>k>>str;
        vector<int> cnt_char(26,0); for(char c:str) cnt_char[c-'a']++;
        string ans="";
        ru(i,0,min(25,n/k)){
            while(k-ans.size()>cnt_char[i]) ans.push_back(i+'a');
        }
        char c='a'+min(n/k,25);
        while(k>ans.size()) ans+=c;
        reverse(ans.begin(),ans.end()); cout<<ans<<endl;
    }
};
struct b{
    int main(){
        ll l,r; cin>>l>>r;
        auto bs_sqrt=[&](ll x)->ll{
            ll left=0,right=2e9+123;
            while(left<right){
                ll mid=(left+right)>>1;
                if(mid*mid>x) right=mid;
                else left=mid+1;
            }
            return left-1;
        };
        ll sql=bs_sqrt(l),sqr=bs_sqrt(r); ll ans;
        if(sql==sqr){
            ans=0;
            ru(i,0,3){
                if(l<=sql*(sql+i)&&sql*(sql+i)<=r) ans++;
            }
        } else {
            ans=(sqr-sql-1)*3;
            ru(i,0,3){
                if(l<=sql*(sqr+i)&&sql*(sql+i)<=r) ans++;
                if(l<=sqr*(sqr+i)&&sqr*(sqr+i)<=r) ans++;
            }
        } cout<<ans<<endl;
    }
};
struct c{
    int main(){
        int x[3],y[3], u,v;
        int n;cin>>n; ru(i,0,3) cin>>x[i]>>y[i]; cin>>u>>v;
        auto centralSquare=[&]()->pair<int,int>{
            int a=(x[0]==x[1])?x[0]:x[2];
            int b=(y[0]==y[1])?y[0]:y[2];
            return {a,b};
        };
        int cx=centralSquare().first, cy=centralSquare().second;
        if((cx==1||cx==n)&&(cy==1||cy==n)){
            cout<<((u==cx||v==cy)?"yes\n":"no\n");
        } else {
            if((cx+cy)%2==(u+v)%2) cout<<(cx%2==u%2?"yes\n":"no\n");
            else cout<<"yes";
        }
    }
};
struct d{
    static const int N=507; ll f[N][N];
    int main(){
        int t;cin>>t;
        while(t--){
            int n,m; cin>>n>>m;
            ru(i,0,n){
                ru(j,0,n) f[i][j]=1e18;
                f[i][i]=0;
            }
            vector<tuple<int,int,int>> ed;
            ru(i,0,m){
                int u,v,w; cin>>u>>v>>w;
                ed.push_back(make_tuple(u-1,v-1,w));
                f[u-1][v-1]=1; f[v-1][u-1]=1;
            }
            ru(k,0,n) ru(i,0,n) ru(j,0,n) f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
            ll ans=1e18;
            for(auto x:ed){
                int u=get<0>(x), v=get<1>(x), w=get<2>(x);
                ans=min(ans,(ll)w*(f[0][u]+f[n-1][v]+1));
                ans=min(ans,(ll)w*(f[0][v]+f[n-1][u]+1));
                ru(i,0,n){
                    ans=min(ans,(ll)w*(f[v][i]+1+f[i][0]+f[i][n-1]+1));
                    ans=min(ans,(ll)w*(f[u][i]+1+f[i][0]+f[i][n-1]+1));
                }
            } cout<<ans<<endl;
        }

    }
};

struct e{
//    static const int mod=998244353;
    ll pow(ll u,ll v){
        if(v==0) return 1;
        ll mid=pow(u,v/2);
        mid=(mid*mid)%mod;
        return (v&1)?(mid*u%mod):mid;
    }
    void main(){

    }
};
int main(){

}