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
            string n; cin>>n;
            if(n.size()==2) cout<<n[1]<<endl;
            else cout<<*min_element(n.begin(),n.end())<<endl;
        }
    }
};
struct b{
    int main(){
        int t;cin>>t;
        while(t--){
            int a,b,c; cin>>a>>b>>c;
            cout<<a+b+c<<" "<<b+c<<" "<<c<<endl;
        }
    }
};
struct c{
    int main(){
        int t;cin>>t;
        while(t--){
            int n,m; cin>>n>>m; vector<vector<int>>a(n,vector<int>(m));
            ru(i,0,n)ru(j,0,m) cin>>a[i][j];
            auto solve=[&](vector<vector<int>> &a)->void{
                int n=a.size(),m=a[0].size(); vector<int> bad;
                for(int i=0;i<n&&bad.empty();i++){
                    vector<int> b=a[i];
                    sort(b.begin(),b.end());
                    ru(j,0,m)if(a[i][j]!=b[j])bad.push_back(j);
                }
                if((int)bad.size()==0){cout<<1<<" "<<1<<endl; return;}
                if((int)bad.size()>2){cout<<-1<<endl; return;}
                ru(i,0,n) swap(a[i][bad[0]],a[i][bad[i]]);
                ru(i,0,n)ru(j,1,m)if(a[i][j]<a[i][j-1]) {cout<<-1<<endl; return;}
                cout<<bad[0]+1<<" "<<bad[1]+1<<endl;
                return;
            };
            solve(a);
        }
    }
};
struct d{
    int main(){
        int t;cin>>t;
        while(t--){
            int n,k; cin>>n>>k; ll ans=0; vector<int>a(n);
            ru(i,0,n){cin>>a[i];ans+=a[i];a[i]+=i+1;}
            sort(a.begin(),a.end()); reverse(a.begin(),a.end());
            ru(i,0,k) ans-=a[i];
            ru(i,0,k) {ans+=n; ans-=i;}
            cout<<ans<<endl;
        }
    }
};

struct e{  //
    static const int INF=1e9+1;
    int main(){
        int t;cin>>t;
        while(t--){
            int n,k; cin>>n>>k; vector<int>a(n); for(auto &c:a)cin>>c;
            map<int,int>cnt; for(auto &c:a)cnt[c]++;
            set<pair<int,int>> s1,s2; int sum1=0;
            for(auto &c:cnt)s2.insert(make_pair(c.second,c.first));
            int ans=INF,skip=0;
            ru_(x,0,n){
                if(s1.find(make_pair(cnt[x-1],x-1))!=s1.end()){
                    sum1-=cnt[x-1]; s1.erase(make_pair(cnt[x-1],x-1));
                }
                if(s2.find(make_pair(cnt[x-1],x-1))!=s2.end()){
                    s2.erase(make_pair(cnt[x-1],x-1));
                }
                while(s2.size()&&sum1+s2.begin()->first<=k){
                    s1.insert(*s2.begin());
                    sum1+=s2.begin()->first;
                    s2.erase(s2.begin());
                }
                if(k<skip) break; int now=x+s2.size();
                if(x==0) now=max(1,(int)s2.size());
                ans=min(ans,now-x);
                if(cnt[x]==0) skip++;
            }
            cout<<ans<<endl;
        }
    }
};

#define all(x) (x).begin(),(x).end()
struct f{  // seg
    vector<int> f;
    void incr(int x,int d){
        for(;x<(int)f.size();x|=(x+1)) f[x]=max(f[x],d);
    }
    int get(int x){
        int ans=-1;
        for(;x>=0;x=(x&(x+1))-1) ans=max(ans,f[x]);
        return ans;
    }
    void main(){
        int t;cin>>t;
        while(t--){
            int n,m; cin>>n>>m; vector<int>a(n); for(auto &c:a)cin>>c;
            map<int,vector<int>> gist; ru(i,0,n) gist[a[i]].push_back(i);
            vector<pair<int,int>> seg(m);
            f.assign(n,-1);
            for(auto &c: seg){
                cin>>c.first>>c.second;
                c.first--; c.second--;
                incr(c.first,c.second);
            }
            vector<int> mnl(n); set<int> s; int l=n;
            rd_(r,n-1,0){
                while(l-1>=0&!s.count(a[l-1])){
                    l--; s.insert(a[l]);
                }
                mnl[r]=1;
                s.erase(a[r]);
            }
            int mnr=-1;
            for(auto &c:seg){
                int l=c.first, r=c.second;
                if(mnl[r]<=l) continue;
                mnr=max(mnr,mnl[r]-1);
            }
            if(mnr==-1){cout<<0<<endl; return ;}
            int ans=mnr+1;
            ru_(i,0,n-1){
                if(gist[a[l]][0]!=l){
                    int id= lower_bound(all(gist[a[l]]),l)-gist[a[l]].begin()-1;
                    int pr=gist[a[l]][id];
                    if(get(pr)>=1) break;
                }
                int id= upper_bound(all(gist[a[l]]),mnr)-gist[a[l]].begin();
                if(id!=(int)gist[a[l]].size()){
                    int nxt=gist[a[l]][id];
                    if(get(l)>=nxt) mnr=nxt;
                }
                mnr=max(mnr,l+1); ans=min(ans,mnr-1);
            }
            cout<<ans<<endl;
        }
    }
};

struct g{ // graph
    vector<vector<int>> g;
    vector<int> with,usd;
    int main(){
        int n,A; vector<int>a(n);vector<int>l,r;
        for(auto &c:a){
            cin>>c;
            if(c*3>A)l.push_back(c);
            else r.push_back(c);
        }
        g.resize(l.size());
        with.resize(r.size(),-1);
        ru(i,0,(int)l.size()) ru(j,0,(int)r.size()){
            if(l[i]%r[j]==0&&2*l[i]+r[j]<=A) g[i].push_back(j);
        }
        function<int(int)> dfs=[&](int v)->int{
            if(usd[v]) return 0; usd[v]=1;
            for(auto &to: g[v]){
                if(with[to]==-1) {
                    with[to]=v; return 1;
                }
            }
            for(auto &to: g[v]){
                if(dfs(with[to])){
                    with[to]=v; return 1;
                }
            } return 0;
        };
        int cnt=0;
        ru(i,0,(int)l.size()){
            usd.assign(l.size(),0); cnt+=dfs(i);
        }
        if(cnt<(int)l.size()){cout<<-1; return 0;}
        vector<pair<int,int>> ans;
        ru(j,0,(int)r.size()){
            if(with[j]==-1) ans.emplace_back(3*r[j],2*r[j]);
            else ans.emplace_back(2*l[with[j]]+r[j],l[with[j]]+r[j]);
        }
        cout<<ans.size()<<endl;
        for(auto &c: ans) cout<<c.first<<" "<<c.second<<endl;
        return 0;
    }
};

struct h{ // divide, seg
    static const int N=1e4;
    vector<pair<int,int>> seg; int g[N+1];
    void five(){}
    void solve(int l,int r,int k,int n){

    }
    int main(){
        int t;cin>>t;
        while(t--){
            string s;cin>>s; int k=count(s.begin(),s.end(),'1');
            if(!k){
                cout<<-1<<endl; continue;
            }
            seg.clear();
            if(k==5) five();
            else solve(0,(int)s.size()-1,k,g[k]);
            cout<<seg.size()<<endl;
            for(auto &[l,r]:seg){
                cout<<l+1<<' '<<r+1<<endl;
            }
        }
    }
};