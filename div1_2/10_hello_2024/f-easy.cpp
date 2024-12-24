#include <bits/stdc++.h>
#define ru(i,l,r) for(int i=(l);i<=(r);i++)
#define ru_(i,l,r) for(int i=(l);i<(r);i++)
#define rup(i,l,r) for(int i=(l);i<=(r);i+=2)
#define rd(i,r,l) for(int i=(r);i>=(l);i--)
#define ll long long
#define pii pair<ll,int>
#define pi priority_queue<pair<int,int>>
#define s1 first
#define s2 second

using namespace std;


static const int INF=1e9+5,maxn=5e3+5;
int n,q,a[maxn],b[maxn];
ll c[maxn],v[maxn],sv[maxn],mx[maxn * 4],lz[maxn * 4];
void init(int u=1,int lo=1,int hi=n){
    lz[u]=0;
    if(lo==hi) mx[u]=sv[lo];
    else{
        int mid=(lo+hi)>>1;
        init(u<<1,lo,mid); init(u<<1^1,mid+1,hi);
        mx[u]=max(mx[u<<1],mx[u<<1^1]);}
}
void propo(int u){
    if(lz[u]==0) return;
    lz[u<<1]+=lz[u];
    lz[u<<1^1]+=lz[u];
    mx[u<<1^1]+=lz[u];
    lz[u]=0;
}
void incre(int s,int e,ll x,int u=1,int lo=1,int hi=n){
    if(lo>=s&&hi<=e){mx[u]+=x;lz[u]+=x;return;}
    propo(u); int mid=lo+hi>>1;
    if(s<=mid) incre(s,e,x,u<<1,lo,mid);
    if(e>mid) incre(s,e,x,u<<1^1,mid+1,hi);
    mx[u]=max(mx[u<<1],mx[u<<1^1]);
}
int main(){
    cin>>n>>q; ru(i,1,n)cin>>a[i]; ru(i,1,n)cin>>b[i]; ru(i,1,n) cin>>c[i];
    ll sma=0; rd(i,n,1){v[i]=a[i]-b[i]; sv[i]=v[i]+sv[i+1]; sma+=a[i];}
    init();
    while(q--){
        int p,x,y; ll z; cin>>p>>x>>y>>z;
        sma-=a[p];
        incre(1,p,-v[p]);
        a[p]=x; b[p]=y; v[p]=a[p]-b[p];
        sma+=a[p];
        incre(1,p,v[p]);
        cout<<sma-max(0ll,mx[0])<<endl;
    }; return 0;
};