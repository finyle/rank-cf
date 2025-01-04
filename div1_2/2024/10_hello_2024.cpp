#include <bits/stdc++.h>
#define ru_(i,l,r) for(int i=(l);i<=(r);i++)
#define ru(i,l,r) for(int i=(l);i<(r);i++)
#define rup(i,l,r) for(int i=(l);i<=(r);i+=2)
#define rd(i,r,l) for(int i=(r);i>=(l);i--)
#define ll long long
#define pii pair<ll,int>
#define pi priority_queue<pair<int,int>>
#define s1 first
#define s2 second

using namespace std;

struct a{  // math: game
    int main(){
        int t; cin>>t;
        while(t--){
            int a,b; cin>>a>>b;
            (a+b)%2==0 ? cout<<"Bob\n" : cout<<"Alice\n";
        }; return 0;
    }
};
struct b{
    int main(){
        int t; cin>>t;
        while(t--){
            int n; string s; cin>>n; cin>>s;
            int ans=0; ru(i,0,n) ans+=s[i]=='+'?1:-1;
            cout<<abs(ans)<<endl;
        }; return 0;
    }
};
struct c{ // subseq
    static const int maxn=1e4, inf=1e9+5;
    int n, a[maxn];
    int main(){
        int t; cin>>t;
        while(t--){
            cin>>n; ru(i,1,n) cin>>a[i];
            int t1=inf, t2=inf, ans=0;
            ru(i,1,n){
                if(t1>t2) swap(t1,t2);
                if(a[i]<=t1) t1=a[i];
                else if(a[i]<=t2) t2=a[i];
                else {t1=a[i]; ans++;}
            }; cout<<ans<<endl;
        }; return 0;
    }
};
// tedukuri-ds
struct d{  // binaryTree+pathsum
    static const int N=2e+5;
    int a[100], pre[100], nxt[100]; bool in[100];
    int n;
    bool good(int i) {
        if(i<1||i>n) return 0;
        return a[pre[i]]==a[i]-1||a[nxt[i]]==a[i]-1;
    }
    int main(){
        int t;cin>>t;
        while(t--){
            cin>>n; priority_queue<pair<int,int>> pq;
            ru(i,1,n) {pre[i]=i-1;nxt[i]=i+1;in[i]=0;cin>>a[i];}
            a[n+1]=a[0]=-2; ru(i,1,n) if(good(i)){in[i]=1; pq.push({a[i],i});}
            while(!pq.empty()){
                auto [_, i]=pq.top(); pq.pop(); nxt[pre[i]]=nxt[i];pre[nxt[i]]=pre[i];
                if(!in[pre[i]]&&good(pre[i])) {in[pre[i]]=1;pq.push({a[pre[i]],pre[i]});}
                if(!in[nxt[i]]&&good(nxt[i])) {in[nxt[i]]=1;pq.push({a[nxt[i]],nxt[i]});}
            }
            int mn=n, bad=0;
            ru(i,1,n) {bad+=!in[i]; mn=min(a[i],mn);}
            (bad==1&&mn==0) ? cout<<"YES"<<endl : cout<<"NO"<<endl;
        }; return 0;
    }
};

struct e{ // cnostructive: sorted permute()-> satisfy enumerate
    static const int INF=1e9+5, N=2e4+5, MOD=998244353;
    ll fact[N*2],ifact[N*2]; int t,n,f[N*2],d[N*2];
    inline ll ncr(int n,int r){
        if(r<0||n<r) return 0;
        return fact[n]*ifact[r]%MOD*ifact[n-r]%MOD;
    }
    inline ll starbar(int n,int x){
        if(n==0&&x==0) return 1;
        return ncr(x+n-1,x);
    }
    int main(){
        fact[0]=1;
        ru_(i,1,N*2) fact[i]=fact[i-1]*i%MOD;
        ifact[0]=fact[1]=1;
        ru_(i,2,N*2) ifact[i]=MOD-MOD/i*ifact[MOD%i]%MOD;
        ru_(i,2,N*2) ifact[i]=ifact[i-1]&ifact[i]%MOD;
        cin>>t;
        while(t--){
            cin>>n; ru_(i,0,n*2+5)f[i]=0;
            n++;ru_(i,1,n) {int s; cin>>s; f[s+n]++;}
            f[n]++;
            int mn=INF,mx=-INF;
            ru(i,0,2*n) if(f[i]){mn=min(mn,i); mx=max(mx,i);}
            bool bad=0; ru(i,mn,mx) if(!f[i]) {bad=1; break;}
            if(bad||mn==mx){cout<<0<<endl; continue;}
            ll ans=0;
            rd(x,mx,mn){
                d[mx-1]=f[mx]+(mx>n)-(mx==x);
                rd(i,mx-2,mn-1) d[i]=f[i+1]-d[i+1]+(i>=x)+(i>=n);
                if(d[mn-1]!=0) continue;
                ll res=1; rd(i,mx-1,mn) res=res*starbar(d[i],f[i]-d[i])%MOD;
                ans+=res; if(ans>=MOD) ans-=MOD;
            }; cout<<ans<<endl;
        }; return 0;
    }
};

//segment
struct f{
    static const int INF=1e9+5,maxn=5e3+5;
    static int n; // struct 内静态区变量 作为内部函数入参 报错: undefined ref;
    int q;
    int a[maxn],b[maxn];
    ll c[maxn],v[maxn],sv[maxn],mx[maxn * 4],lz[maxn * 4];
    void init(int u=1,int lo=1,int hi=n){
        lz[u]=0;
        if(lo==hi) mx[u]=sv[lo];
        else{
            int mid=(lo+hi)>>1;
            init(u<<1,lo,mid); init(u<<1^1,mid+1,hi);
            mx[u]=max(mx[u<<1],mx[u<<1^1]);}
    }
    void propo(int u){
        if(lz[u]==0) return;
        lz[u<<1]+=lz[u];
        lz[u<<1^1]+=lz[u];
        mx[u<<1^1]+=lz[u];
        lz[u]=0;
    }
    void incre(int s,int e,ll x,int u=1,int lo=1,int hi=n){
        if(lo>=s&&hi<=e){mx[u]+=x;lz[u]+=x;return;}
        propo(u); int mid=lo+hi>>1;
        if(s<=mid) incre(s,e,x,u<<1,lo,mid);
        if(e>mid) incre(s,e,x,u<<1^1,mid+1,hi);
        mx[u]=max(mx[u<<1],mx[u<<1^1]);
    }
    int main(){
        cin>>n>>q; ru(i,1,n)cin>>a[i]; ru(i,1,n)cin>>b[i]; ru(i,1,n) cin>>c[i];
        ll sma=0; rd(i,n,1){v[i]=a[i]-b[i]; sv[i]=v[i]+sv[i+1]; sma+=a[i];}
        init();
        while(q--){
            int p,x,y; ll z; cin>>p>>x>>y>>z;
            sma-=a[p];
            incre(1,p,-v[p]);
            a[p]=x; b[p]=y; v[p]=a[p]-b[p];
            sma+=a[p];
            incre(1,p,v[p]);
            cout<<sma-max(0ll,mx[0])<<endl;
        }; return 0;
    };
};

// game; constructive, divide conquer
struct g{ //
    static const int maxn=5005;
    int n; ll r[maxn], hsh[maxn], totr; string s[maxn];
    vector<pair<int,int>> ans; bool done[maxn];
    bool solve(vector<int> grp){
        int pr=-1,pl=-1; vector<int>lft,rht;
        for(int i:grp){
            if(s[i][i]=='0'||done[i]||hsh[i]==totr) continue;
            rht.clear();
            for(int j: grp){
                if(s[j][i]=='0') lft.push_back(j);
                else rht.push_back(j);
            }
            if(!lft.empty()){pr=i; break;}
        }
        if(pr==-1){
            vector<int> dv,zero,one;
            for(int i: grp){
                if(done[i]) dv.push_back(i);
                else if(s[i][i]=='0') zero.push_back(i);
                else one.push_back(i);
            }
            ru(i,1,dv.size()) ans.push_back({dv[i-1],dv[i]});
            if(one.empty()&&zero.empty()) return 1;
            if(one.size()>=zero.size()) return 0;
            if(one.empty()){if(zero.size()>=2||!dv.empty()){return 0;} return 1;}
            ru(i,0,one.size()){ans.push_back({zero[i],one[i]}); ans.push_back({one[i],zero[i+1]});}
            ru(i,one.size()+1,zero.size()) ans.push_back({one[0],zero[i]});
            if(!dv.empty()) ans.push_back({one[0],dv[0]});
            return 1;
        }
        for(int i:lft){
            if(s[i][i]=='0'||done[i]||((hsh[i]^hsh[pr])!=totr)) continue;
            vector<int> trht;
            for(int j:grp) if(s[j][i]=='0') trht.push_back(j);
            if(trht==rht){pl=i; break;}
        }
        if(pl==-1) return 0;
        for(int i:lft){
            for(int j:rht){
                if(j==pr) continue;
                if(s[i][j]!=s[pr][j]) return 0;
            }
        }
        for(int i:rht){
            for(int j:lft){
                if(j==pl) continue;
                if(s[i][j]!=s[pl][j]) return 0;
            }
        }
        ans.push_back({pl, pr}); done[pl]=done[pr]=1;
        return solve(lft)&&solve(rht);
    }
    int main(){
        cin>>n; ru(i,1,n) cin>>s[i];
        ru(i,0,n){r[i]=rand(); totr^=r[i];}
        ru(i,0,n) ru(j,0,n) if(s[i][j]=='1') hsh[j]^=r[i];
        bool pos=1;
        ru(i,0,n){
            if(s[i][i]=='1') continue;
            ru(j,0,n) if(s[j][i]=='1'){pos=0;break;}
        }
        if(!pos){cout<<"no"<<endl; return 0;}
        vector<int> v(n,0); iota(v.begin(),v.end(),0);
        if(!solve(v)) {cout<<"no"<<endl; return 0;}
        cout<<"yes"<<endl;
        for(auto [u,v]: ans) cout<<u+1<<' '<<v+1<<endl;
    }
};

struct h{// interactive

};

int main(){
//    b b;
//    b.main();

//    c c;
//    c.main();

//    d d;
//    d.main();

//    e e;
//    e.main();

//    f f;
//    f.main();

    g g;
    g.main();


}