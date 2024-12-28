#include <bits/stdc++.h>
#define ru_(i,l,r) for(int i=(l);i<=(r);i++)
#define ru(i,l,r) for(int i=(l);i<(r);i++)
#define rup(i,l,r) for(int i=(l);i<=(r);i+=2)
#define rd_(i,r,l) for(int i=(r);i>=(l);i--)
#define rd(i,r,l) for(int i=(r);i>(l);i--)
#define ll long long
#define pii pair<ll,int>
#define s1 first
#define s2 second

using namespace std;

static const int maxn=1e5+5;
int n,b[maxn],a[maxn];
void solve(){
    cin>>n; ru(i,1,n) cin>>b[i];
    b[0]=b[n]=0;
    ru_(i,1,n) a[i]=b[i-1]|b[i];
    bool valid=true;
    ru(i,1,n)if((a[i]&a[i+1])!=b[i]){valid=false; break;}
    if(valid){
        ru_(i,1,n)cout<<a[i]<<' ';
        cout<<endl;
    } else cout<<-1<<endl;
}
int main(){ios::sync_with_stdio(0); cin.tie(0);int t; cin>>t; while(t--)solve();}
