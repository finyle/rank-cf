#include <bits/stdc++.h>
#define ru(i,l,r) for(int i=(l);i<=(r);i++)
#define ru_(i,l,r) for(int i=(l);i<(r);i++)

#define rup(i,l,r) for(int i=(l);i<=(r);i+=2)
#define rd(i,r,l) for(int i=(r);i>=(l);i--)
#define ll long long
#define pii pair<ll,int>
#define s1 first
#define s2 second

using namespace std;

const int MAX=5e6+500, MOD=998244353;
vector<ll> fact(MAX+2,1), inv_fact(MAX+2,1);
ll n, k;
ll binpow(ll a,ll b, ll MOD){
    ll ans=1; a%=MOD;
    while(b){
        if(b&1) ans=(ans*a)%MOD;
        b/=2; a=(a*a)%MOD;
    }; return ans;
}
ll inverse(ll a,ll MOD){return binpow(a,MOD-2,MOD);}
void precompute(ll MOD){
    ru_(i,2,MAX) fact[i]=(fact[i-1]*i)%MOD;
    inv_fact[MAX-1]=inverse(fact[MAX-1],MOD);
    rd(i,MAX-2,0) inv_fact[i]=(inv_fact[i+1]*(i+1))%MOD;
}
ll nCr(ll a,ll b,ll MOD){
    if(a==b) return 1;
    if((a<0)||(a<b)||(b<0)) return 0;
    ll denom=(inv_fact[b]*inv_fact[a-b])%MOD;
    return (denom*fact[a])%MOD;
}
ll ways(ll gaps, ll options){
    gaps--; ll now=nCr(gaps+options-1, options-1,MOD); return now;
}
void solve(){
    cin>>n;
    ru(i,1,(n-1)/2){
        ll ans=1;
        for(ll deleted=2*k;deleted<=n-1;deleted+=2*k){
            ll options=2*k, left_elements=n-deleted;
            ans=(ans+ways(left_elements+1,deleted+1)-ways(left_elements+1,options)+MOD)%MOD;
        }; cout<<ans<<" ";
    }; cout<<endl;
}
int main(){
    ll t; cin>>t; precompute(MOD); while(t--) solve();
}