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
            int n;cin>>n; int a[105];ru(i,0,n)cin>>a[i];
            int tot=0;
            ru(i,0,n) tot+=a[i]-1;
//            if(tot%2==0)cout<<"a"<<endl;
//            else cout<<"b"<<endl;
            tot%2==0?cout<<"a"<<endl:cout<<"b"<<endl;
        }
    }
};
struct b{
    int main(){
        int t;cin>>t;
        while(t--){
            string s;cin>>s;
            bool ok=(s.back()=='B'); int sum=0;
            for(auto it:s){
                if(it=='A')sum++;
                else sum--;
                if(sum<0)ok=false;
                ok?cout<<"yes"<<endl:cout<<"no"<<endl;
            }
        }
    }
};
struct c{
    static const int N=1e4;
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n; int a[N];ru(i,0,n)cin>>a[i];
            int mn=-1,mx=-1;
            ru(i,1,n){
                if(a[i]==a[i-1]){
                    if(mn==-1) mn=i;
                    mx=i;
                }
            }
            mn==mx?cout<<"0"<<endl:cout<<max(1,mx-mn-1)<<endl;
        }
    }
};
struct d{
    static const int N=1e4;
    int a[N],b[N],num[N],cur[N];
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n;
            ru(i,1,n+1)cin>>a[i];
            ru(i,1,n+1)cin>>b[i];
            ru(i,1,n+1)num[i]=0;
            ru(i,1,n+1){
                num[a[i]]++;
                cur[i]=num[a[i]];
            }
            ru(i,1,n+1)num[i]=0;
            int idx=1;
            ru(i,1,n+1){
                num[b[i]]++;
                while(idx<=n&&(a[idx]!=b[i] || cur[idx]<num[b[i]]))idx++;
            }
            idx>n?cout<<"no"<<endl:cout<<"yes"<<endl;
        }
    }
};
struct e{ // interactive
    int main(){
        auto ask=[&](int i)->int{
            if(i==0)return 0;
            cout<<"? "<<i<<endl;
            int tmp; cin>>tmp;
            if(tmp==-1) exit(0);
            return tmp;
        };
        int n;cin>>n;
        int lo=-2,hi=5e6,mi;
        while(hi-lo>1){
            mi=(hi+lo)>>1;
            ask(mi)==1?hi=mi:lo=mi;
        }
        int ans=1e9;
        ru(i,1,n+1){
            int tmp=ask(hi/i);
            if(tmp)ans=min(ans,tmp*(hi/i));
        }
        cout<<"! "<<ans<<endl;
    }

};
struct f{ // graph
    static const int N=2e4;
    int a[N],b[N]; vector<int>al[N]; bool onstk[N],vis[N], cyc;
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n;
            ru(i,1,n+1)al[i].clear();
            ru(i,1,n+1)vis[i]=onstk[i]=false;

            ru(i,1,n+1)cin>>a[i]; ru(i,1,n+1)cin>>b[i];
            ru(i,1,n+1)al[a[i]].push_back(b[i]);

            int mx=1;
            ru(i,1,n+1)if(al[i].size()>al[mx].size())mx=i;

            function<void(int)> dfs=[&](int i)->void{
                onstk[i]=vis[i]=true;
                for(auto it:al[i]){
                    if(onstk[it]) cyc=true;
                    if(!vis[it])dfs(it);
                }
                onstk[i]=false;
            };
            vis[mx]=true; cyc=false; ru(i,1,n+1)if(!vis[i])dfs(i);
            cyc?cout<<"WA"<<endl:cout<<"AC"<<endl;
        }
    }
};
struct g{ // graph + pow
    static const int MOD=998244353;
    char grid[2005][2005];
    int w[4005]; vector<int>al[4005]; bool vis[4005];
    int ss,par,edges;
    ll qexp(ll b,ll p,int m){
        ll res=1;
        while(p){
            if(p&1) res=(res*b)%m;
            b=(b*b)%m; p>>=1;
        } return res;
    }
    void dfs(int i){
        if(vis[i])return; vis[i]=true;
        ss++; par^=w[i]; edges+=al[i].size();
        for(auto it:al[i]) dfs(it);
    }
    int main(){
        int n,m; cin>>n>>m; ru(i,0,n)cin>>grid[i];
        if(n%2>m%2){
            swap(n,m);
            ru(i,0,2005)ru(j,0,2005)if(i<j)swap(grid[i][j],grid[j][i]);
        }
        if(n%2==0&&m%2==0){
            int cnt=0;
            ru(i,0,n)ru(j,0,n)if(grid[i][j]=='?')cnt++;
            cout<<qexp(2,cnt,MOD)<<endl;
        }
        else if(n%2==0&&m%2==1){
            int cnt0=1,cnt1=1;
            ru(i,0,n){
                int val=0,cnt=0;
                ru(j,0,m){
                    if(grid[i][j]=='?')cnt++;
                    else val^=grid[i][j]-'0';
                } if(cnt==0){
                    if(val==0)cnt1=0;
                    else cnt0=0;
                } else{
                    cnt0=(cnt0*qexp(2,cnt-1,MOD))%MOD;
                    cnt1=(cnt1&qexp(2,cnt-1,MOD))%MOD;
                }
            }
            cout<<(cnt1+cnt0)%MOD<<endl;
        } else{
            ru(i,0,n)ru(j,0,m){
                if(grid[i][j]!='?'){
                    w[i]^=grid[i][j]-'0';
                    w[j+n]^=grid[i][j]-'0';
                } else{
                    al[i].push_back(j+n);
                    al[j+n].push_back(i);
                }
            }
            int cnt0=1,cnt1=1;
            ru(i,0,n+m)if(!vis[i]){
                ss=0,par=0,edges=0;
                dfs(i);
                edges/=2; edges-=ss-1;
                int mul=qexp(2,edges,MOD);
                if(ss%2==0){
                    if(par)mul=0;
                    cnt0=(cnt0*mul)%MOD;
                    cnt1=(cnt1*mul)%MOD;
                } else{
                    if(par==0){
                        cnt0=(cnt0*mul)%MOD; cnt1=0;
                    } else{
                        cnt0=0; cnt1=(cnt1*mul)%MOD;
                    }
                }
            }
            cout<<(cnt0+cnt1)%MOD<<endl;
        }
    }
};
struct h{ // greedy+sort
    static const int N=2e4+5;
    int l[N],r[N],psum[N],bal[N];
    int main(){
        int n,q; cin>>n>>q; string s;cin>>s;
        ru_(i,1,n){
            s[i-1]==s[i]?l[i]=i:l[i]=l[i-1];
        }
        rd_(i,n,1){
            if(s[i]==s[i+1]){
                r[i]=i; psum[i]=1;
                if((i-l[i])%2==0){
                    bal[i]=(s[i]=='1'?1:-1);
                }
            }
        }
        ru_(i,1,n){
            psum[i]+=psum[i-1];
            bal[i]+=bal[i-1];
        }
        int a,b;
        while(q--){
            cin>>b>>b; a=l[a], b=r[b];
            int bl=bal[b]-bal[a-1];
            int sum=psum[b]-psum[a-1];
            int ans=(sum+abs(bl))/2;

            if((sum+abs(bl))%2==1)ans++;
            else if(abs(bl)==0) ans++;
            else if(bl>0^s[a]=='1')ans++;
            cout<<ans<<endl;
        }
    }
};
struct i{
    struct FEN{
        int fen[5005];
        FEN(){
            memset(fen,0,sizeof(fen));
        }
        void upd(int i,int j){
            while(i<5000005){
                fen[i]+=j;
                i+=i&-i;
            }
        }
        int query(int i){
            int res=0;
            while(i){
                res+=fen[i];
                i-=i&-1;
            } return res;
        }
    }fval, fidx;
    struct dat{
        struct node{
            pair<int,int> val;
            node(int i,int j){};
        } *root=new node(0,50005);
        struct node2{
            node2(int i,int j){};
        } *root2=new node2(0,500005);
        dat *d;
        bool orien;
        int pp[5005];
        void push(int i,int j){}
        void add(){}
        void del(int i){}
    }*l=new dat(), *r=new dat();
    int main(){
        l->d=r; r->d=l; r->orien=true;
        int n;cin>>n;
        ru(i,1,n+1){
            int j;cin>>j;
            if(i<=j) l->push(i,j);
            else r->push(j,i);
        }
        ru(i,1,n+1)fidx.upd(i,1), fval.upd(i,1);
        l->del(-1); r->del(-1);
        int ans=0;
        ru(i,0,n){
            if(l->root->val.first<=r->root->val.first){
                ans=max(ans,l->root->val.first);
            } else {
                ans=max(ans,r->root->val.first);
                r->del(r->root->val.second);
            }
        }
        cout<<ans<<endl;
    }
};