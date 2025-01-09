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
//ios::sync_with_stdio(0); cin.tie(0);
struct a{
    int main(){
        int t;cin>>t;
        while(t--){
            int w,d,h; cin>>w>>d>>h;int a,b; cin>>a>>b; int f,g;cin>>f>>g;
            int ans=b+abs(a-f)+g;
            ans=min(ans,a+abs(b-g)+f);
            ans=min(ans,(d-b)+abs(a-f)+(d-g));
            ans=min(ans,(w-a)+abs(b-g)+(w-f));
            cout<<ans+h<<endl;
        }; return 0;
    }
};
struct b{
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n;vector<int>a(n);ru(i,0,n)cin>>a[i];
            sort(a.begin(),a.end()); int ans=0;
            ru_(k,0,n){
                if(k==0||a[k-1]<k)
                    if(k==n||a[k]>k) ans+=1;
            };cout<<ans<<endl;
        };return 0;
    }
};
struct c{
    int main(){
        int t;cin>>t;
        while(t--) {
            int n;
            cin >> n;
            string s;
            cin >> s;
            vector<vector<int>> at(26);
            ru(i, 0, n)at[(int) (s[i] - 'a')].push_back(i);
            vector<int> order(26);
            iota(order.begin(), order.end(), 0);
            sort(order.begin(), order.end(), [&](int i, int j) { return at[i].size() > at[j].size(); });
            string res = "";
            int best = -1;
            ru_(cnt, 1, 26) {
                if (n % cnt == 0) {
                    int cur = 0;
                    ru(i, 0, cnt) cur += min(n / cnt, (int) at[order[i]].size());
                    if (cur > best) {
                        best = cur;
                        res = string(n, ' ');
                        vector<char> extra;
                        ru(it, 0, cnt) {
                            int i = order[it];
                            ru(j, 0, n / cnt) {
                                if (j < (int) at[i].size()) res[at[i][j]] = (char) ('a' + i);
                                else extra.push_back((char) ('a' + i));
                            }
                        }
                        for (char &c: res) {
                            if (c == ' ') {
                                c = extra.back();
                                extra.pop_back();
                            }
                        }
                    }
                }
            }
            cout << n - best << endl;
            cout << res << endl;
        } return 0;
    }
};
struct d{
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n;vector<int>a(n);ru(i,0,n)cin>>a[i];
            int ans=1;
            auto Test=[&](ll x)->void{
                int cnt=0;
                for(int v:a){
                    ll u=llround(sqrtl(v+x));
                    if(u*u==v+x) cnt+=1;
                }
                ans=max(ans,cnt);
            };
            ru(i,0,n)
                ru(j,i+1,n){
                    int diff=a[j]-a[i];
                    for(int k=1;k*k<=diff;k++){
                        if(diff%k==0){
                            ll q=k+diff/k;
                            if(q%2==0){
                                q/=2;
                                if(q*q>=a[j]) Test(q*q-a[j]);
                            }
                        }
                    }
            }
            cout<<ans<<endl;
        } return 0;
    }
};
struct e{ // greedy
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n; vector<int>r1(n),c1(n),r2(n),c2(n);
            ru(i,0,n){
                cin>>r1[i]>>c1[i]>>r2[i]>>c2[i];
                assert(1<=r1[i]&&r1[i]<=r2[i]&&r2[i]<=2&&c1[i]<=c2[i]);
                c1[i]--;
            }
            vector<int>order(n); iota(order.begin(),order.end(),0);
            sort(order.begin(),order.end(),[&](int i,int j){return c1[i]<c1[j];});
            set<pair<int,int>>s; int ans=0,p1=-1,p2=-1;
            for(int i:order){
                if(r1[i]==1&&r2[i]==2){
                    if(p1>=c2[i]) r1[i]=2;
                    if(p2>=c2[i]) r2[i]=1;
                    if(r1[i]>r2[i]) continue;
                }
                if(r1[i]==1&&r2[i]==2){
                    while(!s.empty()){
                        auto it=prev(s.end());
                        if(it->first>=c1[i]){c2[it->second]=c1[i];s.erase(it);}
                        else break;
                    }
                    ans+=(c2[i]-max(c1[i],p1))+(c2[i]-max(c1[i],p2));
                    p1=p2=c2[i]; s.emplace(c2[i],i); continue;
                }
                assert(r1[i]==r2[i]);
                if(r1[i]==1){c1[i]=max(c1[i],p1); p1=max(p1,c2[i]);}
                else {c1[i]=max(c1[i],p2); p2=max(p2,c2[i]);}
                if(c1[i]<c2[i]){ans+=c2[i]-c1[i]; s.emplace(c2[i],i);}
            }
            cout<<ans<<endl;
            ru(i,0,n){
                c1[i]++;
                if(r1[i]<=r2[i]&&c1[i]<=c2[i]){
                    cout<<r1[i]<<" "<<c1[i]<<" "<<r2[i]<<" "<<c2[i]<<endl;
                }else{
                    cout<<"0 0 0 0"<<endl;
                }
            }
        } return 0;
    }
};
#include "../../sum/codeforce-template/mint.cpp"
struct f{ //
    int main(){
        int n; Mint p; cin>>n>>p; p/=10000;
        vector<vector<Mint>> C(n+1,vector<Mint>(n+1));
        ru_(i,0,n){
            C[i][0]=1;
            ru_(j,1,i) C[i][j]=C[i-1][j]+C[i-1][j-1];
        }
        vector<vector<Mint>> dp(n+1,vector<Mint>(n+1));
        vector<vector<Mint>> aux(n+1,vector<Mint>(n+1));
        ru_(b,0,n) dp[0][b]=aux[0][b]=1;
        ru_(i,1,n)ru_(b,0,n-i){
            ru_(y,0,i-1)
                dp[i][b]+=C[i-1][y]*aux[i-1-y][b]*(dp[y][b+1]*p+(b==0?0:dp[y][b-1]*(1-p)));
            ru_(j,0,i) aux[i][b]+=dp[j][b]*dp[i-j][b]*C[i][j];
        }
        auto ans=dp[n][0];
        for(int i=1;i<=n*2;i+=2) ans/=i;
        cout<<ans<<endl; return 0;
    }
};

struct g{ // treeDP, constructive
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n;vector<int>p(n);ru(i,1,n){cin>>p[i];p[i]--;}
            ru_(i,2,n){
                if(i==4&&p[1]==0&&p[2]==1&&p[3]==1)cout<<2<<endl;
                else cout<<i%2<<endl;
            }
            vector<vector<int>>g(n); ru(i,1,n) g[p[i]].push_back(i);
            string res="";
            auto Solve=[&](int nn){
                vector<vector<vector<bool>>> good(nn);
                vector<vector<vector<vector<int>>>> prevs(nn);
                vector<int>sz(nn); vector<int>L(nn); vector<int>R(nn);
                function<void(int)> Dfs=[&](int v){
                    sz[v]+=1;
                    for(int u:g[v]){Dfs(u); sz[v]+=sz[u];}
                    L[v]=sz[v]/2;R[v]=L[v]+1;
                    good[v].assign(2,vector<bool>(R[v]-L[v]+1,false));
                    prevs[v].assign(2,vector<vector<int>>(R[v]-L[v]+1));
                    auto Set=[&](int c,int k,vector<int>pr){
                        if(k>=L[v]&&k<=R[v]){
                            good[v][c][k-L[v]]=true; prevs[v][c][k-L[v]]=pr;
                        }
                    };
                    if(g[v].size()==0) Set(0,1,{});
                    if(g[v].size()==1){
                        int u=g[v][0];
                        ru(cu,0,2)ru_(ku,L[u],R[u]){
                            if(good[u][cu][ku-L[u]]){
                                Set(1,1+(sz[u]-ku),{cu,ku,1});
                                if(cu==1) Set(0,1+ku,{cu,ku,0});
                            }
                        }
                    }
                    if(g[v].size()==2){
                        int u=g[v][0], w=g[v][1];
                        ru(cu,0,2)ru_(ku,L[u],R[u])
                        if(good[u][cu][ku-L[u]]){
                            ru(cw,0,2)ru_(kw,L[w],R[w]){
                                if(good[w][cw][kw-L[w]]){
                                    Set(1,1+(sz[u]-ku)+(sz[w]-kw),{cu,ku,1,cw,kw,1});
                                    if(cu==1) Set(1,1+ku+(sz[w]-kw),{cu,ku,0,cw,kw,1});
                                    if(cw==1) Set(1,1+(sz[u]-ku)+kw,{cu,ku,1,cw,kw,0});
                                    if(cu==1&&cw==1) Set(0,1+ku+kw,{cu,ku,0,cw,kw,0});
                                }
                            }
                        }
                    }
                };
                Dfs(0);
                int best=nn+1, best_k=-1;
                ru_(k,L[0],R[0]){
                    if(good[0][1][k-L[0]]){
                        int val=abs(k-(nn-k));
                        if(val<best){best=val; best_k=k;}
                    }
                }
                assert(best<=nn); res=string(nn,'.');
                function<void(int,int,int)> Restore=[&](int v,int c, int k){
                    int ptr=0;
                    for(int u: g[v]){
                        res[u]=(prevs[v][c][k-L[v]][ptr+2]==0?res[v]:(char)('w'^'b'^res[v]));
                        Restore(u,prevs[v][c][k-L[v]][ptr], prevs[v][c][k-L[v]][ptr+1]);
                        ptr+=3;
                    }
                };
                res[0]='w'; Restore(0,1,best_k); return best;
            };
            Solve(n);
            cout<<res<<endl;
        } return 0;
    }
};
struct h{ // comb, math

};

int main(){
//    a a;
//    a.main();
//    b b;
//    b.main();
//    c c;
//    c.main();
//    d d;
//    d.main();

//    e e;
//    e.main();
    f f; f.main();
//    g g; g.main();


}