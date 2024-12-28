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


const int N=100;
int t,n,m,a,b;
bool is[N]; int pr[N/10];
ll ans=0; bool vis[111][111]; pair<int,int> vv[211];
int vn,c; bool flg=0;
int gcd(int a,int b){while(b) a%=b,swap(a,b); return a;}
inline ll V(int i,int j){return i<=n?1ll*max(i,j)*max(a,b)+1ll*min(i,j)*min(a,b):1ll*i*b+1ll*j*a;}
void dfs(int i,int j){
    c++; bool mk=gcd(i,j)==1;
    if(!mk)return;
    ans=max(ans,V(i,j)); vis[m-i][n-j]=1; vv[vn++]={i,j};
    if(j<n&&!vis[m-i][n-j-1])dfs(i,j+1);
    if(i==m||flg){flg=1;return;}
    if(i<m&&!vis[m-i-1][n-j])dfs(i+1,j);
}
int main(){
    is[0]=is[1]=1;
    ru(i,2,N){
        if(!is[i]) pr[++pr[0]]=i;
        for(int j=1;j<=pr[0]&&i*pr[j]<N;j++){
            is[i*pr[j]]=1;
            if(i%pr[j]==0) break;
        }
    }

    cin>>t;
    while(t--){
        cin>>n>>m>>a>>b;
        int p;
        if(m<=10)p=1;
        else{p=m; while(is[p])p--;}
        vn=0,ans=0,flg=0,c=0;
        for(int i=min(n,p-(p>1));;i--){
            assert(i>0);
            ans=max(ans,V(p,i));
            if(p<m) dfs(p+1,i);
            else break;
            if(flg) break;
        }
        ru_(i,1,vn) vis[m-vv[i].first][n-vv[i].second]=0;
        cout<<ans<<endl;
    }
}