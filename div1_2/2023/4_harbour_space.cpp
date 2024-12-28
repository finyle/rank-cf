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
            int x,y,n;cin>>x>>y>>n; vector<int>a(n);a[0]=x;a[n-1]=y;int d=1;
            rd_(i,n-2,1){
                a[i]=a[i+1]-d; d++;
            }
            bool ok=true;
            ru(i,0,n-1){
                if(a[i+1]<=a[i]) ok=false;
            }
            ru(i,0,n-2){
                int p=a[i+1]-a[i], q=a[i+2]-a[i+1];
                if(p<=q) ok=false;
            }
            if(!ok){cout<<"-1"<<endl; continue;}
            ru(i,0,n){cout<<a[i]<<" ";}
            cout<<endl;
        }
    }
};
struct b{
#define all(a) a.begin(),a.end()
    int main(){
        int t;cin>>t;
        while(t--){
            int n,k;cin>>n>>k; string s;cin>>s;
            vector<char>odd,even;
            ru(i,0,n){if(i%2==0)even.push_back(s[i]); else odd.push_back(s[i]);}
            sort(all(even)); sort(all(odd));
            string ans1="";
            for(int i=0,j=0;i<even.size()||j<odd.size();i++,j++){
                if(i<even.size()) ans1+=even[i];
                if(j<odd.size()) ans1+=odd[i];
            }
            if(k%2==0){
                sort(all(s)); cout<<s<<endl; continue;
            }
            cout<<ans1<<endl;
        }
    }
};
struct c{ // bitmask
    bool bit(int max,int pos){ return (max>>pos)&1; }
    int main(){
        int t;cin>>t;
        while(t--){
            int x;cin>>x;int p;vector<int>ans;ans.push_back(x);
            for(int i=0;;i++){
                if(bit(x,i)){
                    if(x==(1<<i)){
                        p=i; break;
                    }
                    x-=(1<<i); ans.push_back(x);
                }
            }
            while(p>0){
                x-=(1<<(p-1));
                ans.push_back(x);
                p--;
            }
            cout<<ans.size()<<endl;
            for(int y:ans) cout<<y<<" ";
            cout<<endl;
        }
    }
};
struct d{
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n;vector<string>a(n);ru(i,0,n)cin>>a[i];
            int ans=0;
            vector<vector<int>> val(n,vector<int>(n,0));
            vector<vector<int>> sum(n,vector<int>(n,0));
            ru(i,0,n){
                ru(j,0,n){
                    if(i==0){}
                    else if(i==1){
                        for(int k=max(0,j-1);k<=min(j+1,n-1);k++) sum[i][j]^=sum[i-1][k];
                    } else{
                        if(j==0) sum[i][j]^=sum[i-2][j];
                        else sum[i][j]^=sum[i-1][j-1];
                        if(j==n-1) sum[i][j]^=sum[i-2][j];
                        else sum[i][j]^=sum[i-1][j+1];
                        sum[i][j]^=sum[i-2][j];
                        sum[i][j]^-val[i-1][j];
                    }
                    if(sum[i][j]^(a[i][j]-'0')){
                        ans++; sum[i][j]^=1; val[i][j]=1;
                    }
                }
            }
            cout<<ans<<endl;

        }
    }
};
struct e{ // game, pow, sort
    static const int mod =998244353;
    struct node{
        int to[2]; int cnt;
        node(){
            to[0]=to[1]=-1;
            cnt=0;
        }
    };
    bool bit(int mask, int pos){
        return (mask>>pos)&1;}
    vector<node> t;
    void add(int x){
        int v=0;
        rd_(i,29,0){
            int b=bit(x,i);
            if(t[v].to[b]==-1){
                t[v].to[b]=t.size();
                t.push_back(node());
            }
            ++t[v].cnt;
            v=t[v].to[b];
        }
        ++t[v].cnt;
    }
    void mul(int &a,int b){
        ll c=(a)*b; if(c>=mod) c%=mod;
        a=c;
    }
    int binpow(int a,int n){
        int ans=1;
        while(n){
            if(n&1) mul(ans,a);
            mul(a,a); n>>=1;
        } return ans;
    }
    void solve(int v,int k, ll& ans){
        if(t[v].to[0]!=-1&&t[v].to[1]!=-1){
            ll i=k+1;
            ans+=(2*(i/2)+1)*t[t[v].to[0]].cnt*t[t[v].to[1]].cnt;
            ans+=2*((i+1)/2)*t[t[v].to[0]].cnt*t[t[v].to[1]].cnt;
        }
        if(t[v].to[0]==-1&&t[v].to[1]==-1){
            ll i=k+1;
            ans+=i*t[v].cnt*t[v].cnt;
        }
        if(t[v].to[0]!=-1) solve(t[v].to[0],k,ans);
        if(t[v].to[1]!=-1) solve(t[v].to[1],k+1,ans);
    }
    int main(){
        int T;cin>>T;
        while(T--){
            t.clear(); t.push_back(node()); int n;cin>>n;ru(i,0,n){int a;cin>>a;add(a);}
            ll x=0;solve(0,0,x); int ans=x%mod;
            mul(ans,binpow(n,mod-2));
            mul(ans,binpow(n,mod-2));
            cout<<ans<<endl;
        }
    }
};
struct f{
    static const int N=1e3+10;
    vector<int>sum;vector<int>t; int n;
    vector<int>pos[N]; int cnt[N], distinct[N];
    void updSumTree(int pos){}
    int getSumTree(int l,int r){}
    void updTree(int pos, int val){}
    int getTree(int l,int r){}
    struct query{
        int l,r,id;
        bool operator<(const query& other)const{return l<other.l;}
    };
    int main(){
        int n,q;cin>>n>>q;vector<int>a(n); ru(i,0,n)cin>>a[i];
        t.assign(4*n,0);ru(i,0,n) pos[a[i]].push_back(i);
        vector<pair<int,int>>pts;
        ru_(x,1,n) {
            ru(i, 0, pos[x].size() - 1) {
                int lf = pos[x][i], rg = pos[x][i + 1];
                ++lf, --rg;
                if (lf > rg) continue;
                int y = getTree(lf, rg);
                if (y == 0) continue;
                pts.push_back({n - y, x});
            }
            for (int p: pos[x]) updTree(p, x);
        }
        cnt[0]=0; distinct[0]=0;
        ru_(x,1,n){
            cnt[x]=cnt[x-1]+pos[x].size();
            distinct[x]=distinct[x-1]+(!pos[x].empty());
        }
        sort(pts.begin(),pts.end());
        int ptr=0; vector<query>queries(q); vector<int>ans(q);
        ru(i,0,q){
            int l,r; cin>>l>>r; queries[i]={n-l,r,i}; ans[i]=distinct[r]-distinct[l-1];
        }
        sort(queries.begin(),queries.end()); n=n+1; sum.assign(N*2,0);
        ru(i,0,q){
            while(ptr<pts.size()&&pts[ptr].first<=queries[i].l){
                updSumTree(pts[ptr].second);
                ++ptr;
            }
            ans[queries[i].id] += getSumTree(0,queries[i].r);
        }
        ru(i,0,q) cout<<ans[i]<<endl;
    }
};
struct g{ // comb, constructive

};

