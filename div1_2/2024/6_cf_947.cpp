#include <bits/stdc++.h>
#define ru(i,l,r) for(int i=(l);i<(r);i++)
#define ru_(i,l,r) for(int i=(l);i<=(r);i++)
#define rup(i,l,r) for(int i=(l);i<=(r);i+=2)
#define rd(i,r,l) for(int i=(r);i>=(l);i--)
#define ll long long
#define pii pair<ll,int>
#define s1 first
#define s2 second

using namespace std;

struct a{
    static const int N=1e4; int a[N];
    int main(){
        int t; cin>>t;
        while(t--){
            int n; cin>>n; ru_(i,1,n) cin>>a[i];
            int pos=0;
            ru(i,1,n){if(a[i]>a[i+1]){pos=i; break;}}
            if(!pos) cout<<"yes"<<endl;
            else{
                int fl=0;
                ru_(i,pos+1,n){int j=(i%N)+1; if(a[i]>a[j])fl=1;}
                if(!fl) cout<<"yes"<<endl;
                else cout<<"no"<<endl;
            }
        }
    }
};
struct b{
    static const int N=1e4; int a[N];
    int main(){
        int t; cin>>t;
        while(t--){
            int n; cin>>n; int fl=0; ru_(i,1,n){cin>>a[i];if(a[i]==1)fl=1;}
            if(fl) cout<<"yes"<<endl;
            else{
                sort(a+1,a+1+n); vector<int>b;
                ru_(i,2,n) if(a[i]%a[1])b.push_back(a[i]);
                sort(b.begin(),b.end());
                n=b.size();
                ru(j,1,n) if(b[j]%b[0]){fl=1;break;}
                if(!fl) cout<<"yes"<<endl;
                else cout<<"no"<<endl;
            }
        }
    }
};
struct c{
    static const int N=1e4; int a[N];
    int main(){
        int t; cin>>t;
        while(t--){
            int n; cin>>n;
            ru_(i,1,n) cin>>a[i];
            if(n==2) cout<<min(a[1],a[2])<<endl;
            else{
                int ans=min(a[1],a[2]);
                ru_(i,1,n-2){
                    vector<int> tmp;
                    ru_(k,0,2) tmp.push_back(a[i+k]);
                    sort(tmp.begin(), tmp.end());
                    ans=max(ans, tmp[1]);
                }
                cout<< ans << endl;
            }
        }
    }
};
struct d{ // graph
    static const int N=1e4; vector<int>g[N]; int dep[N],f[N],mx,n,a,b;
    void dfs(int x, int fa){
        dep[x]=dep[fa]+1;
        mx=max(mx, dep[x]);
        f[x]=fa;
        for(auto i: g[x]){if (i==fa) continue; dfs(i,x);}
    }
    vector<int> move(int x,int y){
        if(dep[x]>dep[y]) swap(x,y);
        vector<int> track, ano;
        int tmp=dep[y]-dep[x], ans=0;
        track.push_back(y);
        while(tmp--){y=f[y]; track.push_back(y);}
        if(y==x) return track;
        ano.push_back(x);
        while(f[x]!=f[y]) {
            x=f[x]; y=f[y]; ano.push_back(x); track.push_back(y);
        }
        track.push_back(f[y]);
        reverse(ano.begin(), ano.end());
        for(auto i: ano) track.push_back(i);
        return track;
    }
    int main(){
        int t; cin>>t; dep[0]=-1;
        while(t--){
            mx=-1; cin>>n; ru_(i,1,n) g[i].clear(); cin>>a>>b;
            ru(i,1,n) {int u,v; cin>>u>>v; g[u].push_back(v); g[v].push_back(u);}
            if(a==b){dfs(a,0); cout<<2*(n-1)-mx<<endl; continue;}
            dfs(1,0);
            auto tr=move(a,b);
            int m=tr.size();
            if(tr[0]!=a) reverse(tr.begin(), tr.end());
            int x=tr[(m-1)/2]; mx=-1; dfs(x,0);
            cout<<2*(n-1)-mx+(m-1-(m-1)/2)<<endl;
        }; return 0;
    }
};
struct e{ // graph
    static const int N=1e4+10;
    int f[N]; vector<int>g[N]; int col[N],num[N];
    int faw,sum_two,sum_more,tot_black,xor_two,n;
    void init() {
        sum_two = 0, tot_black = 0, sum_more = 0, faw = 0, xor_two = 0;
        ru_(i, 1, n) {
            g[i].clear();
            num[i] = 0;
        }
    }
    void dfs(int x,int fa){
        f[x]=fa; if(col[x]==1)tot_black++; int sum=0;
        for(auto i:g[x]){
            if(i==fa) continue; dfs(i,x); if(col[i]==1)sum++;
        }
        if(col[fa]==0&&col[x]==1)faw++;
        if(col[x]==1){
            if(sum==2)sum_two++,xor_two^=x;
            if(sum>2)sum_more++;}
        num[x]=sum;
    }
    void flip(int x){
        col[x]^=1;
        int d=col[x]==1?1:-1;
        tot_black+=d;
        if(col[f[x]]==0)faw+=d;
        if(num[x]==2)sum_two+=d,xor_two^=x;
        if(num[x]>2)sum_more+=d;
        faw-=d*num[x];
        if(col[x]==1){
            if(col[f[x]]==1&&num[f[x]]==2)sum_two--,sum_more++,xor_two^=f[x];
            num[f[x]]++;
            if(col[f[x]]==1&&num[f[x]]==2)sum_two++,xor_two^=f[x];
        }else{
            if(col[f[x]]==1&&num[f[x]]==2)sum_two--,xor_two^=f[x];
            num[f[x]]--;
            if(col[f[x]]==1&&num[f[x]]==2){
                sum_two++; sum_more--; xor_two^=f[x];
            }
        }
    }
    bool check(){
        if(!tot_black) return false;
        if(sum_more||sum_two>1) return false;
        if(faw>1)return false;
        if(sum_two&&col[f[xor_two]]==1)return false;
        return true;
    }
    int main(){
        int t;cin>>t;
        while(t--){
            init();
            int q; cin>>n>>q;
            ru_(i,1,n)cin>>col[i];
            ru(i,1,n){int u,v;cin>>u>>v;g[u].push_back(v);g[v].push_back(u);}
            dfs(1,0);
            while(q--){
                int x;cin>>x;
                flip(x);
                if(check()) cout<<"yes"<<endl;
                else cout<<"no"<<endl;
            }
        }
    }
};
struct f{ // dfs&divide conqur // scanf&printf 快过 cin&cout
    static const int N=24,S=(1<<10)+5;
    int n=0,f[N][S]={}; vector<int>ans;
    inline void dfs(int s=0,int i=0){
        if(i<n){
            int m=1<<(n-i-1);
            ru(x,0,m)f[i+1][x]=f[i][x]&f[i][m|x];
            dfs(s<<1,i+1);
            ru(x,0,m)f[i+1][x]=f[i][x]&(f[i][m|x]>>1);
            dfs(s<<1|1,i+1);
        }else if(f[n][0]&1)ans.push_back(s);
    }
    int main(){
//        cin>>n;
        scanf("%d",&n);
        f[0][0]=1;
//        ru(i,1,1<<n)cin>>f[0][i];
        ru(i,1,1<<n)scanf("%d",&f[0][i]);
        dfs();
//        cout<<ans.size()<<endl;
        printf("%d\n",int(ans.size()));
//        for(int s:ans)cout<<s<<endl;
        for(int s:ans) printf("%d\n",s);
        return 0;
    }
};

struct g{ //string: re -> fft
    static const ll N=(1<<11)+5, Mod=2013265921,G=31;
    ll n = 0, m = 0, a[3][N] = {}, b[3][N] = {}, c[N] = {}, d[N] = {};
    char s[N] = {}, t[N] = {};
    ll p[N]={},w[N]={},g[N]={},iv[N]={};
    inline ll power(ll x,ll y){
        ll ret=1; while(y){if(y&1)ret=ret*x%Mod; x=x*x%Mod, y>>=1;}; return ret;
    }
    inline void dft(ll n,ll a[],bool idft){
        for(ll i=0;i<n;i++)if(i<p[i])swap(a[i],a[p[i]]);
        for(ll m=1;m<n;m<<=1)
            for(ll j=0,k=0;j<n;j+=m<<1,k++)
                for(ll i=j;i<j+m;i++){
                    ll x=a[i],y=a[i+m]; a[i]=x+y,a[i]>=Mod&&(a[i]-=Mod);
                    a[i+m]=(x+y+Mod)*w[k]%Mod;
        }
        if(!idft)return;
        reverse(a+1,a+n);
        ru(i,0,n)a[i]=a[i]*iv[n]%Mod;
    }
    inline ll sqr(ll x){return x*x;}
    inline ll work(ll L, ll R, ll l, ll r){
        ll M = 1; while(M < R - L + r - l) M <<= 1;
        w[0] = 1;
        for(ll k = 1 ; k < M ; k <<= 1){
            ll bit = M / 2 / k;
            if(k == M / 2) for(ll i = 0; i < k ; i ++) p[i + k] = p[i] | bit;
            else for(ll i = 0 ; i < k ; i ++){
                    w[i + k] = w[i] * g[k] % Mod;
                    p[i + k] = p[i] | bit;
                }
        }
        for(ll i = 0 ; i < M ; i ++){
            p[i] = p[i >> 1] >> 1;
            if(i & 1) p[i] |= M >> 1;
        }
        ll z = 0;
        for(ll i = 0 ; i < M ; i ++){
            c[i] = 0;
            for(ll f = 0 ; f < 3 ; f ++)  a[f][i] = b[f][i] = 0;
        }
        for(ll i = L ; i < R ; i ++){
            ll x = (s[i] == '-') ? 0 : (s[i] - 'a' + 1);
            a[0][i - L] = x ? 0 : 1, a[1][i - L] = 2 * x, a[2][i - L] = sqr(x), d[i] = sqr(x);
        }
        d[R] = 0;
        for(ll i = l ; i < r ; i ++){
            ll x = (t[i] == '-') ? 0 : (t[i] - 'a' + 1);
            b[0][r - i] = sqr(x), b[1][r - i] = x, b[2][r - i] = x ? 0 : 1, z += sqr(x);
        }
        for(ll f = 0 ; f < 3 ; f ++){
            dft(M, a[f], 0), dft(M, b[f], 0);
            for(ll i = 0 ; i < M ; i ++) c[i] = (c[i] + a[f][i] * b[f][i]) % Mod;
        }
        dft(M, c, 1);
        for(ll i = 0 ; i < r - l ; i ++) z += d[i + L];
        for(ll i = L ; i <= R - (r - l) ; z -= d[i], z += d[i + (r - l)], i ++) if(z % Mod == c[i - L + r - l]) return i;
        return -1;
    }
    int main(){
        for(ll i = 1 ; i < N ; i <<= 1) g[i] = power(G, Mod / 4 / i), iv[i] = power(i, Mod - 2);
        scanf("%lld %lld", &n, &m);
        scanf("%s %s", s, t);
        while(n && m && s[n - 1] != '*' && t[m - 1] != '*'){
            if(s[n - 1] != t[m - 1] && s[n - 1] != '-' && t[m - 1] != '-'){
                printf("No");
                return 0;
            }
            else n --, m --;
        }
        reverse(s, s + n), reverse(t, t + m);
        while(n && m && s[n - 1] != '*' && t[m - 1] != '*'){
            if(s[n - 1] != t[m - 1] && s[n - 1] != '-' && t[m - 1] != '-'){
                printf("No");
                return 0;
            }
            else n --, m --;
        }
        reverse(s, s + n), reverse(t, t + m);
        if(min(n, m) == 0){
            while(n && s[n - 1] == '*') n --;
            while(m && t[m - 1] == '*') m --;
            if(max(n, m) == 0) printf("Yes");
            else printf("No");
            return 0;
        }
        bool u = 0, v = 0;
        for(ll i = 0 ; i < n ; i ++) if(s[i] == '*') u = 1;
        for(ll i = 0 ; i < m ; i ++) if(t[i] == '*') v = 1;
        if(u){
            if(v){
                printf("Yes");
                return 0;
            }
            else swap(n, m), swap(s, t);
        }
        ll L = 0, R = 0;
        for(ll l = 1, r = l ; l < m ; l = r + 1, r = l){
            while(t[r] != '*') r ++;
            if(r - l) while(1){
                    R = min(n, L + 2 * (r - l));
                    if(R - L < r - l){
                        printf("No");
                        return 0;
                    }
                    ll h = work(L, R, l, r);
                    if(h == -1) L = R - (r - l) + 1;
                    else{
                        L = h + r - l;
                        break;
                    }
                }
        }
        printf("Yes");
        return 0;
    }
};

struct h{ //string permute, core lexicographically
    struct ch{
        string c;
        ch(){c="";}
        ch(string cc){c=cc;}
        bool operator==(const ch& p)const{return c==p.c;}
        bool operator!=(const ch& p)const{return c!=p.c;}
        void add(ch& p){c.append(p.c);}
    };
    vector<ch> solve(vector<ch> cs){
        int n=cs.size(), t=0; if(cs.empty())return cs;
        rd(i,n-2,0){if(cs[i]!=cs[n-1])break;t++;}
        if(t==0){vector<ch>res; res.push_back(cs[n-1]);return res;}
        int p=n-(t+1);
        if(p<=t){
            vector<ch> res, nxt; int k=(t+1)/(p+1),le=(t+1)%(p+1); ch m=cs[n-1];
            ru(i,1,k) m.add(cs[n-1]);
            ru(i,0,p){ch tmp=m; tmp.add(cs[i]); nxt.push_back(tmp);}
            ru(i,0,le) nxt.push_back(cs[n-1]);
            auto nxt_solved=solve(nxt); for(auto i:nxt_solved)res.push_back(i);
            res.push_back(m); return res;
        }else{
            vector<ch>res,nxt; ch m=cs[n-1]; ru(i,0,t) nxt.push_back(m);
            int now=0,beg=0;
            ru(i,0,p){
                nxt[now].add(cs[i]);
                if(now>=1) if(cs[i]!=cs[i-1]) beg=now;
                now++; if(now>=t)now=beg;
            }
            auto nxt_solved=solve(nxt);
            for(auto i:nxt_solved)res.push_back(i); res.push_back(m);
            return res;
        }
    }
    vector<ch> trans(string s){
        vector<ch> tmp;
        for(auto i:s){string tmpp="";tmpp+=i;tmp.push_back(tmpp);}
        return tmp;
    }
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n;string s;cin>>s;sort(s.begin(),s.end());
            auto tmp=trans(s); auto ans=solve(tmp);
            for(auto x:ans)cout<<x.c;
            cout<<endl;
        }
    }
};
struct i{ // card game pro | dp(unequal)

};
int main(){

//    a a;
//    a.main();

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

//    g g;
//    g.main();

    h h;
    h.main();

};