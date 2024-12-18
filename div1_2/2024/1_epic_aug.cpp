#include <bits/stdc++.h>
#define ru(i,l,r) for(int i=(l);i<=(r);i++)
#define rd(i,r,l) for(int i=(r);i>=(l);i--)
#define ll long long
#define pii pair<ll,int>
#define s1 first
#define s2 second
using namespace std;

struct a {
    int main() {
        int t, n, m, k;
        scanf("%d", &t);
        while (t--) {
            scanf("%d%d%d", &n, &m, &t);
            printf("%d\n", min(n, k) * min(m, k));
        }
        return 0;
    }
};
struct b {
    int read() {
        int x=0,w=0; char ch=getchar();
        while(!isdigit(ch)) w|=ch=='-',ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return w?-x:x;
    }
    int main() {
        int T = read();
        while(T--){
            int n=read(); vector<int> a, b;
            ru(i,1,n) a.push_back(read());
            ru(i,1,n) b.push_back(read());
            if(a==b) {printf("Bob\n"); continue;}
            reverse(a.begin(), a.end());
            if(a==b) {printf("Bob\n"); continue;}
            printf("Alice\n");
        }
        return 0;
    }
};
struct c{
    int t, n, x[100],y[100],xs,ys,xt,yt;

    int dis(int x1, int y1, int x2, int y2) {
        return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);}
    int main() {
        scanf("%d",&t);
        while(t--){
            scanf("%d",&n);
            ru(i,1,n) scanf("%d%d",x+i,y+i);
            scanf("%d%d%d%d",&xs,&ys,&xt,&yt);
            bool ok=1;
            ru(i,1,n) {if(dis(xt,yt,x[i],y[i])<=dis(xt,yt,xs,ys)) {ok=0;break;}}
            printf(ok?"Yes\n":"No\n");
        }
    }
};

struct d{
    static const int maxn=100;
    int n,Q,fa[maxn],p[maxn],q[maxn],siz[maxn]; set<int> son[maxn];
    int read() {
        int x=0,w=0; char ch=getchar();
        while(!isdigit(ch)) w|=ch=='-',ch=getchar();
        while(isdigit(ch)) x=x*10+ch-'0',ch=getchar();
        return w?-x:x;
    }
    int chk(int x) {return son[x].empty()?1:(q[x]<*son[x].begin()&&*--son[x].end()+siz[p[*--son[x].end()]]<=q[x]+siz[x]);}
    void solve() {
        n=read();Q=read();
        ru(i,1,n) siz[i]=1,son[i].clear();
        ru(i,2,n) fa[i]=read();
        rd(i,n,2) siz[fa[i]]+=siz[i];
        ru(i,1,n) son[fa[p[i]=read()]].insert(i),q[p[i]]=i;
        int cnt=0;
        ru(i,1,n) cnt+=chk(i);
        while(Q--) {
            int i=read(),j=read(),x=p[i],y=p[j];
            set<int> s; s.insert(x),s.insert(y),s.insert(fa[x]),s.insert(fa[y]);
            for(auto x: s) {if(x) cnt-=chk(x);}
            son[fa[x]].erase(i), son[fa[y]].erase(j);
            swap(p[i],p[j]),swap(q[x],q[y]);
            son[fa[x]].insert(j), son[fa[y]].insert(i);
            for(auto x: s) {if(x) cnt+=chk(x);}
            puts(cnt==n?"yes":"no");
        }
    }
    int main() {
        int T = read(); while(T--) solve(); return 0;
    }
};
struct d_p{
    static const int maxn=100;
    int tin[maxn],tout[maxn],id[maxn],par[maxn]; vector<int> g[maxn]; int T=0;
    void dfs(int u, int p) {
        id[u]=tin[u]=tout[u]=T++;
        for(auto v:g[u]) if(v!=p){
            dfs(v,u); par[v]=u; tout[u]=tout[v];
        }
    }
    void solve() {
        int n,q; cin>>n>>q;
        vector<int> p(n+1);
        ru(i,0,n) g[i].clear();
        ru(i,2,n) {int pi; cin>>pi; g[pi].push_back(i);}
        ru(i,1,n) cin>>p[i];
        dfs(1,1); int cnt=0;
        auto ok=[&](int i) {
            if(p[i]==1){if(i==1) return 1; return 0;}
            int ant=p[i-1];
            if(par[p[i]]==ant) return 1;
            if(tin[ant]!=tout[ant]) return 0;
            int pa=par[p[i]];
            if(tin[ant]<tin[pa]||tin[ant]>tout[pa]) return 0;
            return 1;
        };
        ru(i,1,n) cnt+=ok(i);
        ru(qw,0,q) {
            int x, y; cin>>x>>y; set<int> in; in.insert(x); in.insert(y);
            if(x-1>=1) in.insert(x-1);
            if(x+1<=n) in.insert(x+1);
            if(y-1>=1) in.insert(y-1);
            if(y+1<=n) in.insert(y+1);
            for(auto v:in) cnt-=ok(v);
            swap(p[x],p[y]);
            for(auto v:in) cnt+=ok(v);
            cout<<(cnt==n?"yes":"no")<<endl;
        }
    }
    int main() {
        int T; cin >> T; while(T--){solve();} return 0;
    }
};

struct e{
    int main() {
        int N=100;
        int n, b[N], sn; int a[N]; pii s[N];
        int t; scanf("%d",&t);
        while(t--){
            ru(i,1,n) scanf("%d%d",a+i,b+i);
            sn=0; ll x=0;
            ru(i,1,n) {
                ll mx=0;
                while(sn) {
                    if(s[sn].s2==b[i]) a[i]+=s[sn-1].s1-mx;
                    else if(s[sn].s1<=a[i]) mx=max(mx,s[sn--].s1);
                    else break;
                }
                ++sn; s[sn]=pii(a[i],b[i]); x=max(x,s[sn].s1);
                printf("%d",x);
            }
            putchar(10);
        }
        return 0;
    }
};
struct e_p{

};
struct f{
    static const int maxn=100;
    bool ntp[maxn], bad[maxn][maxn];
    int pos[maxn], prime[maxn], mn[maxn], cnt;
    void sieve(int n) {
        int i, j;
        ru(i,2,n) {
            if(!ntp[i]) prime[++cnt]=i, mn[i]=i;
            for(j=1;i<=cnt&&i*prime[j]<=n;j++){
                mn[i*prime[j]]=prime[j];
                ntp[i*prime[j]]=1;
                if(!(i%prime[j])) break;
            }
        }
    }
    int gcd(int x, int y) {return x?gcd(y%x,x):y;}
    bool no(int l, int r, int k) {
        while(k>1){
            int x=mn[k]; while(k%x==0) k/=x;
            if(((l+x-1)/x)*x<=r) return 0;
        }; return 1;
    }
    int main() {
        sieve(maxn);
        int i, j=0,T,n,m,a,b,u,v,g=0,S=0,px,py,qwq=0;
        ll ans; prime[0]=1;
        ru(i,2,maxn) {while(j<cnt&&prime[j+1]<=i) j++; pos[i]=j;}
        scanf("%d",&T);
        while(T--) {
            scanf("%d%d%d%d",&n,&m,&a,&b);
            if(n<m){swap(n,m); swap(a,b);}
            u=prime[pos[n]]; v=m;
            while(v&&!no(u,n,v)) v--;
            ans=0; px=py=0;
            ru(i,u,n) {
                for(j=v;j<=m&&j<=i;j++){
                    bad[i-u+1][j-v+1]=((bad[i-u][j-v+1]&&bad[i-u+1][j-v])||gcd(i,j)>1);
                    if(!bad[i-u+1][j-v+1]){
                        ans=max(ans,(ll)a*i+(ll)b*j);
                        if((ll)a*i+(ll)b*j==ans) {px=i;py=j;}
                        if(i<=m) ans=max(ans,(ll)a*j+(ll)b*i);
                    }
                }
            }
            qwq=max(qwq,(n-px)+(m-py));
            printf("%d\n", ans);
        }
        return 0;
    }
};
struct f_p{

};

struct g{

};


int main() {
//    b b;
//    b.main();

//    c c;
//    c.main();

//    d d;
//    d.main();
    int a = 1e9+7;
    cout << a;


}