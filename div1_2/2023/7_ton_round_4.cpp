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
            int n;cin>>n; bool ok=false;
            ru(i,0,n){
                int x; cin>>x;
                if(i+1>=x) ok=true;
            }
            cout<<(ok?"yes":"no")<<endl;
        }
    }
};
struct b{
    int main(){
        int t;cin>>t;
        while(t--){
            ll n;cin>>n; const int m=40; vector<int>ans(m,1);
            if(n%2==0){
                cout<<-1<<endl; continue;
            }
            ru(i,1,m){
                if((n-1)&(1LL<<i)) ans[m-i]=2;
            }
            cout<<m<<endl;
            ru(i,0,m) cout<<ans[i]<<" \n"[i==m-1];
        }
    }
};
struct c{
    int main(){
        int t;cin>>t;
        while(t--){
            int n;ll c,d;cin>>n>>c>>d; vector<int>a(n); ru(i,0,n)cin>>a[i];
            sort(a.begin(),a.end());
            ll ans=c*n+d; int rm=0;
            ru(i,0,n){
                if(i>0&&a[i]==a[i-1]) rm+=1;
                ll cur=c*(n-1-i+rm)+d*(a[i]-(i+1-rm));
                ans=min(ans,cur);
            }
            cout<<ans<<endl;
        }
    }
};
struct d{
    int main(){
        int t;cin>>t;
        while(t--){
            int q;cin>>q;
            auto Calc=[&](ll a,ll b, ll h)-> ll{
                if(h<=a) return 1LL;
                return 1LL+((h-a+(a-b-1))/(a-b));
            };
            ll low=1, high=(ll)2e18;
            while(q--){
                int op; cin>>op;
                if(op==1){
                    ll a,b,n;cin>>a>>b>>n;
                    ll R=(a-b)*(n-1)+a;
                    ll L=(n==1?1LL:(a-b)*(n-2)+a+1);
                    if(R<low||high<L) {
                        cout<<0<<endl; continue;
                    } else{
                        cout<<1<<endl; low=max(low,L); high=min(high,R);
                    }
                } else{
                    ll a,b; cin>>a>>b;
                    ll x=Calc(a,b,low), y=Calc(a,b,high);
                    if(x==y) cout<<x<<endl;
                    else cout<<-1<<endl;
                }
            }
        }
        return 0;
    }
};

struct e{

};

#include "../../sum/template/seg_mx_mn.cpp"
struct f{
    int main(){
        int t;cin>>t;
        while(t--){
            int n,m,q; cin>>n>>m>>q; vector<int>a(n);ru(i,0,n){cin>>a[i];--a[i];}
            segtree st(2*n+2);
            auto Add=[&](int i){
                int x=st.find_first(i,2*n+1,[&](const segtree::node& nd){
                    return nd.mn<m-1;
                });
                if(i<x) st.modify(i,x-1,-(m-1));
                st.modify(x,x,+1);
            };
            auto Remove=[&](int i){
                int x=st.find_first(i,2*n+1,[&](const segtree::node& nd){
                    return nd.mx>0;
                });
                if(i<x) st.modify(i,x-1,+(m-1));
                st.modify(x,x,-1);
            };
            ru(i,0,n) Add(a[i]);
            Remove(0);
            ru(it,0,q){
                int x,y;cin>>x>>y;--x,--y;
                Add(y); Remove(a[x]); a[x]=y;
                ll sum=st.get(0,2*n+1).sum;
                int p=st.find_first(0,2*n+1,[&](const segtree::node& nd){
                    if(nd.sum<sum){
                        sum-=nd.sum;
                        return false;
                    }
                    return true;
                });
                cout<<(n==1?1:p+2)<<" \n"[it==q-1];
            }
        } return 0;
    }
};
int main(){

}