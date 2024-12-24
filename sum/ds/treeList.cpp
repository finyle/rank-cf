#include <bits/stdc++.h>
#define ru(i,l,r) for(int i=(l);i<=(r);i++)
#define rd(i,r,l) for(int i=(r);i>=(l);i--)
#define ll long long

using namespace std;

struct a{
    static const int SIZE=1E3+10; int a[SIZE],n,m;
    ll c[2][SIZE], sum[SIZE];
    ll ask(int k, int x){
        ll ans=0; for(;x;x-=x&-x) ans+=c[k][x];
        return ans;
    }
    void add(int k, int x, int y){
        for(;x<=n;x+=x&-x) c[k][x]+=y;
    }
    int main(){
        cin>>n>>m; ru(i,1,n){cin>>a[i];sum[i]=sum[i-1]+a[i];}
        while(m--){
            char op[2]; int l,r,d; scanf("%s%d%d",op,&l,&r);
            if(op[0]=='C'){scanf("%d",&d); add(0,l,d);add(0,r+1,-d);add(1,l,l*d);add(1,r+1,-(r+1)*d);}
            else{
                ll ans=sum[r]+(r+1)*ask(0,r)-ask(1,r);
                ans-=sum[l-1]+l*ask(0,l-1)-ask(1,l-1);
                printf("%lld\n",ans);
            }
        }
    }
};
int main(){
    a a;
    a.main();
}