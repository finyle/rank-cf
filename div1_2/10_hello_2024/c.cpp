#include <bits/stdc++.h>
#define ru(i,l,r) for(int i=(l);i<=(r);i++)
#define rup(i,l,r) for(int i=(l);i<=(r);i+=2)
#define rd(i,r,l) for(int i=(r);i>=(l);i--)
#define ll long long
#define pii pair<ll,int>
#define s1 first
#define s2 second

using namespace std;

static const int maxn=1e4, inf=1e9+5;
int n; int a[maxn];
int main(){
    int t; cin>>t;
    while(t--){
        cin>>n; ru(i,1,n) cin>>a[i];
        int t1=inf, t2=inf, ans=0;
        ru(i,1,n){
            if(t1>t2) swap(t1,t2);
            if(a[i]<=t1) t1=a[i];
            else if(a[i]<=t2) t2=a[i];
            else {t1=a[i]; ans++;}
        }; cout<<ans<<endl;
    }; return 0;
}