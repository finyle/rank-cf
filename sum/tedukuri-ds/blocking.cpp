#include <bits/stdc++.h>
#define ru(i,l,r) for(int i=(l);i<=(r);i++)
#define rd(i,r,l) for(int i=(r);i>=(l);i--)
#define ll long long

using namespace std;

struct a{
    static const int N=1e4+10;
    ll a[N],sum[N],add[N];
    int L[N],R[N];
    int pos[N]; int n,m,t;
    void change(int l, int r, ll d){
        int p=pos[l],q=pos[r];
        if(p==q){
            ru(i,l,r) a[i]+=d;
            sum[p]+=d*(r-l+1);
        }else{
            ru(i,p+1,q-1) add[i]+=d;
            ru(i,l,R[p]) a[i]+=d;
            sum[p]+=d*(R[p]-l+1);
            ru(i,L[q],r) a[i]+=d;
            sum[q]+=d*(r-L[q]+1);
        }
    }
    ll ask(int l, int r){
        int p=pos[l], q=pos[r]; ll ans=0;
        if(p==q){
            ru(i,l,r) ans+=a[i];
            ans+=add[p]*(r-l+1);
        }else{
            ru(i,p+1,q-1) ans+=sum[i]+add[i]*(R[i]-L[i]+1);
            ru(i,l,R[p]) ans+=a[i];
            ans+=add[p]*(R[p]-l+1);
            ru(i,L[q],r) ans+=a[i];
            ans+=add[q]*(r-L[q]+1);
        }; return ans;
    }

    int main(){
        cin>>n>>m;
        ru(i,1,n) scanf("%lld",&a[i]);
        t=sqrt(n*1.0);
        ru(i,1,t){L[i]=(i-1)*sqrt(n*1.0)+1; R[i]=i*sqrt(n*1.0);}
        if(R[t]<n) t++, L[t]=R[t-1]+1,R[t]=n;

        ru(i,1,t) ru(j,L[i],R[i]) {pos[j]=i; sum[i]+=a[j];}

        while(m--){
            char op[3]; int l,r,d; scanf("%s%d%d",op,&l,&r);
            if(op[0]=='C'){scanf("%d",&d); change(l,r,d);}
            else printf("%lld\n", ask(l,r));
        }
    }
};

int main(){
    a a;
    a.main();

}