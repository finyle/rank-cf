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

struct a{
    static const int maxn=100;
    int t,n,a[maxn];
    int main(){
        ios::sync_with_stdio(0); cin.tie(0);
        cin>>t;
        while(t--){
            cin>>n; ru(i,1,n) cin>>a[i]; int ans=0;
            rup(i,1,n) ans=max(ans,a[i]);
            cout<<ans<<endl;
        }; return 0;
    }
};
struct b{
    static const int maxn=1e4;
    int n,b[maxn],a[maxn];
    void solve(){
        cin>>n; ru(i,1,n)cin>>b[i];
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
};
struct c{
    static const int maxn=1e4;
    int n,a[maxn];
    void solve(){
        cin>>n; ru(i,1,n) cin>>a[i];
        bool has_odd=false, has_even=false;
        ru(i,1,n){
            if(a[i]%2==1) has_odd=true;
            else has_even=true;
        }
        if(has_even && has_odd) {cout<<-1<<endl;}
        else{
            vector<int> operation;
            rd(i,29,0) operation.push_back(1<<i);
            if(has_even) operation.push_back(1);
            cout<<operation.size()<<endl;
            for(auto x: operation) cout<<x<<' ';
            cout<<endl;
        }
    }
    int main() {int t; cin>>t;while(t--) solve();}
};

struct e{
    static const int maxn=1e4;
    int n,m,color[maxn],isBipartite;
    vector<int> graph[maxn];
    void dfs(int vertex){
        for(auto x:graph[vertex]) {
            if(!color[x]) {color[x]=3-color[vertex]; dfs(x);}
            else if(color[x]+color[vertex]!=3) isBipartite=0;
        }
    }
    void solve(){
        cin>>n>>m; ru(i,1,n){graph[i].clear(); color[i]=0;}
        ru(i,1,m){
            int u,v; cin>>u>>v;
            graph[u].push_back(v); graph[v].push_back(u);
        }
        isBipartite=1;color[1]=1;dfs(1);
        if(isBipartite){cout<<"Alice"<<endl;}
        else{cout<<"Bob"<<endl;}
    }
};

struct f{
    static const int maxn=1e4;
    int n,q,a[maxn],p[maxn];
    bool canForm(int l,int r){
        int t=0; ru(i,l,r) p[++t]=a[i];
        sort(p+1,p+t+1);
        ru(i,1,t-5)
            ru(j,i+1,i+5)
                ru(k,j+1,i+5) {
                    int q[t], c = 0;
                    ru(m, i + 1, i + 5) if (m != j && m != k) q[++c] = p[m];
                    if (p[i] + p[j] > p[k] && q[1] + q[2] > q[3]) return true;
                }
        int triCnt=0;
        ru(i,1,t-2) if(p[i]+p[i+1]>p[i+2]){i+=2; triCnt++;}
        return triCnt>1;
    }
    int main(){
        cin>>n>>q; ru(i,1,n) cin>>a[i];
        while(q--){
            int l,r; cin>>l>>r;
            if(r-l+1>=48|| canForm(l,r)) cout<<"yes"<<endl;
            else cout<<"no"<<endl;
        }
    }
};
struct g{
    static const int maxn=1e4; char ope;
    int n,m,k,q,grid[maxn][maxn]; string s;
    int calc(int x1,int y1,int x2,int y2){
        int sum=0;
        ru(i,x1,x2) ru(j,y1,y2) sum+=grid[i][j];
        return sum;
    }
    int perform(int x,int y){
        cout<<x<<' '<<y<<endl;
        ru(i,1,k) {
            grid[x][y]=1;
            if(ope=='h') y++;
            else x++;
        }
        int rowSum[maxn],colSum[maxn];
        ru(i,1,n) ru(j,1,m) {rowSum[i]+=grid[i][j]; colSum[j]+=grid[i][j];}
        ru(i,1,n) ru(j,1,m) if(rowSum[i]==m||colSum[j]==n) grid[i][j]=0;
    }
    void solve(){
        cin>>n>>m>>k>>q>>s; s=' '+s; memset(grid,0,sizeof(grid));
        ru(i,1,q) {
            ope=s[i];
            if(ope=='h'){
                int row=-1;
                ru(j,1,n) if(calc(j,1,j,k)==0){ row=j; if(calc(j,1,j,m)==m-k) break;}
                perform(row,1);
            } else{
                int col=-1;
                ru(j,1,m) if(calc(1,j,k,j)==0) {col=j; if(calc(1,j,n,j)==n-k) break;}
                perform(1,col);
            }
        }
    }
    int main(){int t; cin>>t; while(t--) solve();}
};
struct h{
    static const int maxn=1e4;
    bitset<maxn+1>isCompsite, isWining, isPrimeLosing, isPrimeWining, isGoodPosition;
    void init(){
        isCompsite[1]=true;
        ru(i,2,maxn) ru(j,i*2,maxn){isCompsite[j]=true;}
    }
};

int main(){
//    a a;
//    a.main();
    b b;
    b.main();

}
