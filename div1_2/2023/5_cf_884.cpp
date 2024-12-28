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
            int a,b; cin>>a>>b;
            cout<<a+b<<endl;
        }
    }
};
struct b{
    int main(){
        int t,i,n,a[2000];cin>>t;
        while(t--){
            cin>>n;
            if(n==1)cout<<1<<endl;
            else if(n==2)cout<<"1 2"<<endl;
            else{
                int c=4; fill(a,a+n,0); a[0]=2,a[n/2]=1,a[n-1]=3;
                ru(i,0,n) if(a[i]==0) a[i]=c++;
                ru(i,0,n) printf("%d%c",a[i],(i==n-1)?'\n':' ');
            }
        }
    }
};
struct c{
    int main(){
        int i,t,n,c[2000];cin>>t;
        while(t--){
            cin>>n; ru(i,0,n)cin>>c[i];
            int allneg=1;ru(i,0,n)allneg&=(c[i]<0);
            if(allneg)cout<<*max_element(c,c+n)<<endl;
            else{
                long long int ans1=0,ans2=0;
                ru(i,0,n){
                    if(i&1)ans1+=max(c[i],0);
                    else ans2+=max(c[i],0);
                }
            }
        }
        return 0;
    }
};
struct d{
    char s[10001];
    int main(){
        int i,t,n;cin>>t;
        while(t--){
            cin>>n; int c=1; while((n%c)==0)c++;
            ru(i,0,n)s[i]='a'+(i%c);
            s[n]='\0'; cout<<s<<endl;
        }
        return 0;
    }
};
struct e{
    vector<pair<int,int>> adjList[4000];
    int colour[4000], bad=0;
    int dfs(int u,int c){
        if(colour[u]!=-1){
            if(colour[u]!=c)bad=1;
            return 0;
        }
        colour[u]=c;
        for(auto [v,e]: adjList[u]) dfs(v,c^e);
        return 0;
    }
    int main(){
        int x1,y1,x2,y2;
        int t;cin>>t;
        while(t--){
            int n,m,k; cin>>n>>m>>k;
            ru(i,0,k){
                cin>>x1>>y1>>x2>>y2;
                x1--,y1--,x2--,y2--;
                adjList[min(x1,x2)].push_back(make_pair(n+min(y1,y2),(x1+y1!=x2+y2)));
                adjList[n+min(y1,y2)].push_back(make_pair(n+min(x1,x2),(x1+y1!=x2+y2)));
            }
            fill(colour,colour+n+m,-1),bad=0;
            ru(i,0,n+m) if(colour[i]==-1)dfs(i,0);
            printf(bad?"no\n":"yes\n");
            ru(i,0,n+m) adjList[i].clear();
        }
    }
};
struct f{
};
struct g{

};