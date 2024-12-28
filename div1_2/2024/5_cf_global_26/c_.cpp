#include <bits/stdc++.h>
#define ru_(i,l,r) for(int i=(l);i<=(r);i++)
#define ru(i,l,r) for(int i=(l);i<(r);i++)
#define rup(i,l,r) for(int i=(l);i<=(r);i+=2)
#define rd(i,r,l) for(int i=(r);i>=(l);i--)
#define ll long long
#define pii pair<ll,int>
#define s1 first
#define s2 second

using namespace std;

static const ll maxn=1e3, mod=1e4+9;
vector<ll> p2(maxn);
void solve(){
    int n; cin>>n; vector<int>arr(n); for(auto &x:arr) cin>>x;
    ll sum=0,mn=0,ans=0,abses=0;
    ru(i,0,n) sum+=arr[i],mn=min(mn,sum);
    if(mn==0){cout<<p2[n]<<endl; return;}
    sum=0;
    ru(i,0,n){
        sum+=arr[i];
        if(sum==mn) ans=(ans+p2[n-i-1+abses])%mod;
        if(sum>=0)++abses;
    }; cout<<ans<<endl;
}
int main(){
    p2[0]=1;
    ru(i,1,maxn) p2[i]=2*p2[i-1]%mod;
    int t; cin>>t; while(t--)solve();
    return 0;
}