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
            int n;cin>>n; vector<int>a(n); ru(i,0,n)cin>>a[i];
            if(!is_sorted(a.begin(),a.end())) cout<<"yes"<<endl;
            cout<<"no"<<endl;
        }
    }
};

struct b{
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n; vector<int>a(n);ru(i,0,n)cin>>a[i];
            int ans=0;
            ru(i,0,n){
                ans+=(i+1)*(n-i);
                if(a[i]==0) ans+=(i+1)*(n-i);
            }
            cout<<ans<<endl;
        }
    }
};

struct c{
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n; vector<int>a(n);ru(i,0,n) cin>>a[i];
            if(*max_element(a.begin()+1,a.end()-1)==1||(n==3&&a[1]%2==1)){
                cout<<"-1\n"; exit(0);}
            ll ans=0;
            ru(i,1,n-1) ans+=(a[i]+1)/2;
            cout<<ans;
        }
    }
};

struct d{
    static const int MAXSUM=1e4+10;
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n;vector<int>a(n),b(n);
            for(auto& u:a)cin>>u; for(auto& v:b)cin>>v;
            int sumMin=0,sumMax=0,sumSeq=0;
            auto sqr=[&](int x)->int{return x*x;};
            ru(i,0,n){
                if(a[i]>b[i]) swap(a[i],b[i]);
                sumSeq+=sqr(a[i])+sqr(b[i]);
                sumMin+=a[i]; sumMax+=b[i];
            }
            bitset<MAXSUM> dp; dp[0]=1;
            ru(i,0,n) dp|=dp<<(b[i]-a[i]);
            int ans=sqr(sumMin)+sqr(sumMax);
            ru_(i,0,sumMax-sumMin){
                if(dp[i]) ans=min(ans,sqr(sumMin+i)+sqr(sumMax-i));
            }
            cout<<sumSeq*(n-2)+ans<<endl;
        }
    }
};

struct e{ // sort
    int main(){
        int t; cin>>t;
        while(t--){
            int n,m; cin>>n>>m; vector<int>a(n);map<int,int>cnt;for(auto &x:a){cin>>x;cnt[x]++;}
            vector<pair<int,int>> bad_pairs;
            bad_pairs.reserve(2*m);
            ru(i,0,m){
                int x,y; cin>>x>>y;
                bad_pairs.emplace_back(x,y);
                bad_pairs.emplace_back(y,x);
            }
            sort(bad_pairs.begin(),bad_pairs.end());

            vector<vector<int>> occ(n); for(auto &[x,c]:cnt) occ[c].push_back(x);
            for(auto &v:occ) reverse(v.begin(),v.end());
            ll ans=0;
            ru(cnt_x,1,n){
                for(int x:occ[cnt_x]){
                    ru(cnt_y,1,cnt_x){
                        for(auto y:occ[cnt_y]){
                            if(x!=y&&!binary_search(bad_pairs.begin(),bad_pairs.end(),pair<int,int>{x,y})){
                                ans=max(ans,1ll*(cnt_x+cnt_y)*(x+y)); break;
                            }
                        }
                    }
                }
            }
            cout<<ans<<endl;
        }
    }
};

struct f{ // graph, degree

};

struct g{ // divide conquer
    vector<pair<int,int>> ops; vector<int>a;
    void rec(int n, int coeff){
        if(n<=2) {
            ru_(i, 1, n) a.push_back(i * coeff);
            return ;
        }
        int p=1; while(p*2<=n)p*=2;
        if(p==n){
            a.push_back(n*coeff);
            n--,p/=2;
        }
        a.push_back(p*coeff);
        for(int i=p+1;i<=n;i++){
            a.push_back(2*p*coeff);
            ops.emplace_back(i*coeff,(2*p-i)*coeff);
        }
        rec(2*p-n-1,coeff);
        rec(n-p,coeff*2);
    }
    int main(){
        int t;cin>>t;while(t--){
            int n;cin>>n; if(n==2){cout<<"-1\n"; exit(0);}
            ops.clear(); a.clear(); rec(n,1); sort(a.begin(),a.end());
            int ans=1; while(ans<n) ans*=2;
            for(int i=0;;i++){
                if(a[i]==a[i+1]){
                    assert(a[i]!=ans);
                    ops.emplace_back(a[i],a[i]);
                    a[i+1]*=2;
                    a.erase(a.begin()+i);
                    break;
                }
            }
            for(auto x:a){
                while(x!=ans){
                    ops.emplace_back(0,x);
                    ops.emplace_back(x,x);
                    x*=2;
                }
            }
            ops.emplace_back(0,ans);
            cout<<ops.size()<<endl;
            for(auto &[x,y]:ops) cout<<x<<' '<<y<<endl;
        }
    }
};

struct h{// datastruct
    struct binary_index_tree{
        int n; vector<int>bit;
        binary_index_tree(int n):n(n),bit(n+1){}
        void increase(int pos){
            for(pos++;pos<=n;pos+=pos&-pos) bit[pos]++;
        }
        int query(int pref) const{
            int sum=0;
            for(;pref;pref-=pref&-pref) sum+=bit[pref];
            return sum;
        }
    };
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n; vector<int>d(n);
            binary_index_tree bit(n);
            ll inversions=0;
            ru(i,0,n){
                int p; cin>>p; p--;
                d[i]=i-2*p;
                inversions+=i-bit.query(p);
                bit.increase(p);
            }
            sort(d.rbegin(),d.rend()); cout<<inversions;
            ll sum=0;
            ru(i,0,n){
                sum+=d[i]; cout<<' '<<inversions-sum-1ll*i*(i+1)/2;
            }
            cout<<endl;
        }
    }
};