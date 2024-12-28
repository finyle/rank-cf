#include <bits/stdc++.h>
#define ru_(i,l,r) for(int i=(l);i<=(r);i++)
#define ru(i,l,r) for(int i=(l);i<(r);i++)
#define rup(i,l,r) for(int i=(l);i<=(r);i+=2)
#define rd(i,r,l) for(int i=(r);i>=(l);i--)
#define ll long long
#define pli pair<ll,int>
#define pii pair<int,int>
#define s1 first
#define s2 second

using namespace std;

struct a{
    int main(){
        int t; cin>>t;
        while(t--){
            int n,k; cin>>n>>k;
            printf("%d\n",1+(n-1)*k);
//            cout<<1+(n-1)*k<<endl;
        }; return 0;
    }
};
struct b{
    int main(){
        int t; cin>>t;
        while(t--){
            int n; cin>>n;
            vector<int> a(n);
            ru(i,0,n) cin>>a[i];
            ll pref_max=0,s=0,mx=0;
            ru(i,0,n){
                pref_max=max(pref_max,(ll)a[i]);
                ll d=pref_max-a[i]; s+=d; mx=max(mx,d);
            }
            cout<<s+mx<<endl;
        }
    }
};
struct c{
    int main(){
        int t; cin>>t;
        while(t--){
            int n; cin>>n; vector<int>h(n); for(auto &x:h) cin>>x;
            int ans=h[n-1];
            rd(i,n-2,0) ans=max(ans+1,h[i]);
            cout<<ans<<endl;
        }
    }
};
struct d{
    // static 修饰符仅用于 struct,class局部常量作为局部内置数据结构容量参数(<1e4)，单独使用时不修饰
    const int N=1e9;
    void solve(){
        vector<int> a;
        {int n; cin>>n; map<int,int> cnt;
            while(n--){int x; cin>>x; cnt[x]++;}
            for(auto const &[k,v]: cnt) a.push_back(v);}
        int n = a.size(); vector<int> dp(n+1,N); dp[0]=0;
        ru_(i,1,n){
            vector<int> ndp=dp;
            ru_(k,1,n){
                int nv=dp[k-1]+a[i-1];
                if(nv<=i-k) ndp[k]=min(ndp[k],nv);
            }
            dp=ndp;
        }
        int ans=n; while(dp[ans]>=N)ans--; cout<<n-ans<<endl;
    }
    int main(){int t; cin>>t; while(t--) solve();}
};
struct e{ // tree,bfs
    const ll N=1e15;
    void solve(){
        int n; cin>>n; vector<int>a(n); for(auto &x:a) cin>>x;
        vector<int>d(n); vector<vector<int>> g(n);
        ru(i,1,n){int p;cin>>p;p--;g[p].push_back(i);d[i]=d[p]+1;}
        vector<ll>b(n);
        ru(v,0,n){
            if(g[v].empty()) b[v]=N;
            else {b[v]=-a[v]; for(int u:g[v]) b[v]+=a[u];}
        }
        ll ans=0;
        for(int v=n-1;v>=0;v--){
            queue<int>q; q.push(v);
            while(!q.empty()){
                int i=q.front(); q.pop();
                for(int u:g[i]){
                    ll delta=min(-b[v],b[u]);
                    if(delta>0) {b[v]+=delta; b[u]-=delta; ans+=delta*(d[u]-d[v]);}
                    q.push(u);
                }
            }
        };
        cout<<ans<<endl;
    }
    int main(){ios::sync_with_stdio(0); cin.tie(0);int t; cin>>t; while(t--) solve();}
};
struct f{ //dp
    const int N=1e9;
    void solve(){
        int n; cin>>n; vector<int> a(n); ru(i,0,n) cin>>a[i];
        vector<vector<int>> dp(n+1,vector<int>(n+1,N));
        ru_(i,0,n) dp[i][i]=0;
        for(int le=1;le<=n;le++){
            for(int l=0;l+le<=n;l++){
                if(a[l]%2!=(l+1)%2) continue;
                if(a[l]>l+1) continue;
                int v=(l+1-a[l])/2;
                int r=l+le;
                for(int m=l+1;m<r;m+=2){
                    if(dp[l+1][m]<=v){
                        int new_val=max(v,dp[m+1][r]-(m-l+1)/2);
                        dp[l][r]=min(dp[l][r],new_val);
                    }
                }
            }
        }
        vector<int> dp2(n+1);
        ru(i,0,n){
            dp2[i+1]=dp2[i];
            ru(j,0,i){
                if(dp[j][i+1]<=dp2[j]) dp2[i+1]=max(dp2[i+1],dp2[j]+(i-j+1)/2);
            }
        }; cout<<dp2[n]<<endl;
    }
    int main(){ios::sync_with_stdio(0); cin.tie(0);int t;cin>>t;while(t--)solve();}
};
struct g{// constructive, tree diameter,dp
    array<vector<int>, 2> get_l_and_r(vector<int> &p) {
        int n = p.size();
        vector<int> l(n), r(n);
        stack<int> s;
        for (int i = 0; i < n; i++) {
            while (!s.empty() && p[s.top()] < p[i]) s.pop();
            if (s.empty()) l[i] = -1;
            else l[i] = s.top();
            s.push(i);
        }
        s = {};
        for (int i = n - 1; i >= 0; i--) {
            while (!s.empty() && p[s.top()] < p[i]) s.pop();
            if (s.empty()) r[i] = n;
            else r[i] = s.top();
            s.push(i);
        }
        return {l, r};
    }
    int ans_l_edge(array<int, 2> d, array<int, 2> e) {return d[0] + 1 + max(d[1], e[0]);}
    int ans_r_edge(array<int, 2> d, array<int, 2> e) {return e[1] + 1 + max(d[1], e[0]);}
    array<int, 2> add_l_edge(array<int, 2> d, array<int, 2> e) {return {max({d[0], d[1] + 1, e[0] + 1}), e[1]};}
    array<int, 2> add_r_edge(array<int, 2> d, array<int, 2> e) {return {d[0], max({d[1] + 1, e[0] + 1, e[1]})};}
    void add_to_map(map<array<int,2>,int>&dp_ind, int &len_dp,array<int,2>a){if(!dp_ind.count(a))dp_ind[a]=len_dp++;}
    vector<array<int,2>> process_dp(vector<array<int,2>>&dp){
        array<int,2>max_a={-1,-1},max_b={-1,-1},max_s={-1,-1};
        for(auto [a,b]:dp){
            if(a>max_a[0]||(a==max_a[0]&&b>max_a[1])) max_a={a,b};
            if(b>max_b[1]||(b==max_b[1]&&a>max_b[0])) max_b={a,b};
            if(a+b>max_s[0]+max_s[1])max_s={a,b};
        }
        return {max_a,max_b,max_s};
    }
    void solve(){
        int n;cin>>n; vector<int>p(n);ru(i,0,n)cin>>p[i];string s;cin>>s;
        auto[l,r]=get_l_and_r(p);
        ru(i,0,n){
            if(p[i]==n)continue;
            if(l[i]==-1&&s[i]=='L'){cout<<-1<<endl;return;}
            if(r[i]==n&&s[i]=='R'){cout<<-1<<endl;return;}
        }
        int ans=0;vector<int>q(n+1);
        ru(i,0,n)q[p[i]]=i;
        int len_dp=0;map<array<int,2>,int>dp_ind;
        ru_(i,1,n){
            int x=q[i],tl=l[x],tr=r[x];
            add_to_map(dp_ind,len_dp,{tl,x});
            add_to_map(dp_ind,len_dp,{x,tr});
            add_to_map(dp_ind,len_dp,{tl,tr});
        }
        vector<vector<array<int,2>>> dp(len_dp,{{0,0}});
        ru_(i,1,n){
            int x=q[i],tl=l[x],tr=r[x];
            int ind_l=dp_ind[{tl,x}], ind_r=dp_ind[{x,tr}], ind_c=dp_ind[{tl,tr}];
            for(auto const &d:dp[ind_l]){
                for(auto const &e:dp[ind_r]){
                    ans=max(ans,d[1]+e[0]);
                    if(tl>=0&&s[i]!='R'){ans=max(ans,ans_l_edge(d,e)); dp[ind_c].push_back(add_l_edge(d,e));}
                    if(tr<=n-1&&s[i]!='L'){ans=max(ans,ans_r_edge(d,e)); dp[ind_c].push_back(add_r_edge(d,e));}
                }
            }
            dp[ind_c]=process_dp(dp[ind_c]);
        };
        cout<<ans<<endl;
    }
    int main(){ios::sync_with_stdio(0); cin.tie(0);int t;cin>>t;while(t--)solve();}

};

struct h{//interactive

};


int main(){
//    a a;
//    a.main();
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