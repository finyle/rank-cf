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
            int n;cin>>n;string s;cin>>s;
            if(s==string(n,s[0])){cout<<"-1"<<endl; continue;}
            int ans=-1;
            ru(i,0,n-1){
                if(s[i]=='R'&&s[i+1]=='L'){ans=0; break;}
                if(s[i]=='L'&&s[i+1]=='R'){ans=i+1; break;}
            }
            cout<<ans<<endl;
        } return 0;
    }
};
struct b{
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n;
            if(n==3){cout<<"no"<<endl; continue;}
            if(n%2==0){
                cout<<"yes"<<endl;
                ru(i,0,n){cout<<(i%2==0?1:-1)<<" \n"[i==n-1];}
                continue;
            }
            int a=n/2-1, b=n/2;
            cout<<"yes"<<endl;
            ru(i,0,n){cout<<(i%2==0?a:-b)<<" \n"[i==n-1];}
        }
    }
};
struct c{
    int main(){
        int t;cin>>t;
        while(t--){
            int n,k; cin>>n>>k;
            vector<int> a(n);ru(i,0,n) cin>>a[i];
            vector<int> b(n);ru(i,k,n) b.push_back(a[i]);
            vector<int> c(n);rd(i,k-1,0) c.push_back(-a[i]);
            auto Solve=[&](vector<int>a)->int{
                ll sum=0; multiset<int> s; int ret=0;
                for(int x:a){
                    sum+=x; s.insert(x);
                    while(sum<0){
                        sum-=2*(*s.begin());
                        ret+=1;
                        s.erase(s.begin());
                    }
                } return ret;
            };
            cout<<Solve(b)+Solve(c)<<endl;
        } return 0;
    }
};
struct d{
    template <typename T>
    class fenwick{
    public:
        vector<T> fenw;
        int n;
        fenwick(int _n): n(_n){fenw.resize(n);}
        void modify(int x,T v){
            while(x<n){fenw[x]+=v; x|=(x+1);}
        }
        T get(int x){
            T v{};
            while(x>=0){v+=fenw[x]; x=(x&(x+1))-1;}
            return v;
        }
    };
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n;
            vector<int>a(n);ru(i,0,n)cin>>a[i];
            vector<int>b(n);ru(i,0,n)cin>>b[i];
            int m;cin>>m;vector<int>x(m);ru(i,0,n)cin>>x[i];
            bool ok=true;
            vector<pair<int,int>>need;
            ru(i,0,n){
                if(a[i]<b[i]){ok=false;break;}
                need.emplace_back(b[i],i);
            }
            if(!ok){cout<<"no"<<endl; continue;}
            sort(need.begin(),need.end()); sort(x.rbegin(),x.rend());
            int ptr=0,last_val=-1,last_pos=-1; vector<int> to_put; fenwick<int>fenw(n);
            rd_(id,n-1,0){
                if(id<n-1&&need[id].first!=need[id+1].first){
                    for(int xx: to_put) fenw.modify(xx,+1);
                    to_put.clear();
                }
                int i=need[id].second; bool use=false;
                if(a[i]>b[i]){
                    use=true;
                    if(last_val==b[i]){
                        assert(last_pos>i);
                        if(fenw.get(last_pos-1)-fenw.get(i)==0) use=false;
                    }
                }
                if(use){
                    while(ptr<m&&x[ptr]!=b[i])ptr+=1;
                    if(ptr<m&&x[ptr]==b[i]) ptr+=1;
                    else {ok=false; break;}
                    last_val=b[i]; last_pos=i;
                }
                to_put.push_back(i);
            }
            cout<<(ok?"yes":"no")<<endl;
        } return 0;
    }
};
int main(){
//    a a; a.main();
//    b b; b.main();
//    c c; c.main();
    d d;d.main();
}