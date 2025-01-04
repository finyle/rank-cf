#include <bits/stdc++.h>
#define ru_(i,l,r) for(int i=(l);i<=(r);i++)
#define ru(i,l,r) for(int i=(l);i<(r);i++)
#define rd_(i,r,l) for(int i=(r);i>=(l);i--)
#define rd(i,r,l) for(int i=(r);i>(l);i--)
#define ld long long
#define pli pair<ld,int>
#define s1 first
#define s2 second

using namespace std;
#ifdef LOCAL
#include 'algo/debug.h'
#else
#define debug(...)
#endif
//ios::sync_with_stdio(0); cin.tie(0);

struct b{
    int d[110]; pair<int,int>s[110];
    int main(){
       int t;cin>>t;
       while(t--){
         int n,l=0,i,c;cin>>n;
         for(int i=2;i*i<=n;i++){
             if(n%i==0){
                 c=0;
                 while(n%i==0)c++,n/=i;
                 s[++l]= make_pair(c,i);
             }
         }
         if(n!=1)s[++l]=make_pair(1,n); // 下标中的++操作 位置不等价
         sort(s+1,s+1+l),d[l+1]=1;
         rd_(i,l,1)d[i]=d[i+1]*s[i].second;
         int ans=0;
         ru_(i,1,l)
            if(s[i].first!=s[i-1].first)
                ans+=d[i]*(s[i].first-s[i-1].first);
         cout<<ans<<endl;
       }
   }
};
struct c{
    static const int N=2e4+5;
    ld f[N][2],x[N],y[N];
    int main(){
        int t;cin>>t;
        while(t--){
            int i,n,s,j;
            cin>>n>>s;
            ru_(i,1,n){
                cin>>j;
                if(i==1||i==n)x[i]=y[i]=j;
                else if(j<=s)x[i]=0,y[i]=j;
                else x[i]=s,y[i]=j-s;
            }
            f[1][0]=f[1][1]=0;
            ru_(i,2,n){
                f[i][0]=min(f[i-1][0]+y[i-1]*x[i],f[i-1][1]+x[i-1]*x[i]);
                f[i][1]=min(f[i-1][0]+y[i-1]*y[i],f[i-1][1]+x[i-1]*y[i]);
            }
            cout<<f[n][0]<<endl;
        }
    }
};
struct d{ // comb dsu
    static const int N=2e4+5; int a[N],v[N],s[N];
    struct E{int to; E *nex;} *h[N];
    void add(int u,int v){
        E *cur=new E;
        cur->to=v, cur->nex=h[u],h[u]=cur;
    }
    void dfs(int u){
        s[u]=v[u]=1;
        for(E *cur=h[u];cur;cur=cur->nex)
            dfs(cur->to), s[u]+=s[cur->to];
    }
    int main(){
        int t;cin>>t;
        while(t--){
            int i,j,n;cin>>n;
            ru_(i,1,n+1) s[i]=v[i]=0, h[i]=0;
            ru_(i,1,n) {
                cin>>a[i],a[i]=min(i+a[i],n+1);
                if(a[i]<=0)a[i]=n+1;
                add(a[i],i);
            }
            function<void(int)> dfs=[&](int u){
                s[u]=v[u]=1;
                for(E*cur=h[u]; cur; cur=cur->nex)
                    dfs(cur->to), s[u]+=s[cur->to];
            };
            dfs(n+1); ld ans=0;
            if(v[1]==1){
                j=1;do{ans-=s[j]+(n-s[n+1]+1),j=a[j];}
                while(j!=n+1); ans+=1*n*(n*2+1);
            }else{
                j=1;do{ans+=(n+s[n+1]),v[j]=2,j=a[j];}
                while(v[j]!=2);
            }
            cout<<ans<<endl;
        }
    }
};
struct e{
    int main(){
        int t;cin>>t;
        while(t--){
            int n,k,x; cin>>n>>k>>x; int a=0; ru_(i,1,n)a^=i;
            int goal=(k%2==0?0:x);
            if(a!=goal){cout<<"no"<<endl;continue;}
            vector<vector<int>>seq;
            vector<bool>used(n+1,false);
            vector<int>rm;
            ru_(i,1,n){
                if(used[i])continue;
                if(i==x&&(int)seq.size()<k)seq.push_back({i});
                else{
                    if((i^x)>i&&(i^x)<=n&&(int)seq.size()<k){
                        seq.push_back({i,i^x}); used[i^x]=true;
                    } else {rm.push_back(i);}
                }
            }
            if((int)seq.size()<k){cout<<"no"<<endl; continue;}
            seq[0].insert(seq[0].end(),rm.begin(),rm.end());
            cout<<"yes"<<endl;
            for(auto &v:seq){
                cout<<v.size();
                for(int u:v) cout<<" "<<u;
                cout<<endl;
            }
        } return 0;
    }
};
struct f{
    static const int N=2e4+5;
    int dest[N],visit[N],ans[N],mp[N],ansinv[N],sp; vector<int>cyc[N];
    int pow2(int y,int M){
        ld x=2,ans=1;
        while(y){
            if(y&1)ans=ans*x%M;
            x=x*x%M,y>>=1;
        } return ans%M;
    }
    int main(){
        int t;cin>>t;
        while(t--){
            int n,i,j,m,z,o; cin>>n>>m;
            ru_(i,1,n)cyc[i].clear();
            ru_(i,1,n)visit[i]=0; cin>>dest[i];
            ru_(i,1,n){
                if(visit[i])continue;
                j=i,z=0;
                do{z++,visit[j]=1,j=dest[j];}while(j!=i);
                cyc[z].push_back(i);
            }
            int lim=pow2(min(m,20),1e9),s=0,d,t,num,cp;
            ru_(i,1,n){
                if(!cyc[i].size())continue;
                int siz=cyc[i].size();
                if(i%2==0&&siz%lim){cout<<"no"<<endl; break;}
                else{
                    cp=-1;
                    for(j=lim;j>0;j/=2){
                        while(siz>=j){
                            siz-=j,d=s+j*i,t=j;
                            while(t--){
                                s++,cp++,num=s,o=cyc[i][cp];
                                do{
                                    ans[num]=o,num+=pow2(m,i*j);
                                    if(num>d)num-=j*i;
                                    o=dest[o];
                                } while(o!=cyc[i][cp]);
                            }
                            for(int k=sp+1;k<sp+j*i;k++) mp[k]=k+1;
                            mp[sp+j*i]=sp+1,sp+=j*i,s=d;
                        }
                    }
                }

            }
            cout<<"yes"<<endl;
            ru_(i,1,n)ansinv[ans[i]]=i;
            ru_(i,1,n)cout<<ans[mp[ansinv[i]]]<<" \n"[i==n];
        }
    }
};

#include "../../sum/template/seg.cpp"
struct g{ // graph, degree, seg
    int main(){
        int n,t; cin>>n>>t;
        vector<vector<array<int,3>>> edges(n);
        ru(i,0,n-1){
            int u,v,w,c; cin>>u>>v>>w>>c; --u,--v,--c;
            edges[c].push_back({u,v,w});
        }
        vector<vector<int>> g(2*n);
        vector<ld>weight(2*n);
        vector<int>deg(n); int id=n;
        ru(c,0,n){
            if(edges[c].empty()) continue;
            int E=(int)edges[c].size();
            vector<int>vers;
            for(auto &v:edges[c]){
                vers.push_back(v[0]);
                vers.push_back(v[1]);
            }
            sort(vers.begin(),vers.end());
            vers.resize(unique(vers.begin(),vers.end())-vers.begin());
            int V=(int)vers.size();
            if(V==E+1){
                int mx=0;
                for(auto &v:edges[c]){
                    deg[v[0]]+=1; mx=max(mx,deg[v[0]]);
                    deg[v[1]]+=1; mx=max(mx,deg[v[1]]);
                }
                if(mx<=2){
                    for(auto& v:edges[c]) weight[id]+=v[2];
                    for(int v:vers){
                        g[id].push_back(v);
                        g[v].push_back(id);
                    }
                    id+=1;
                }
                for(auto &v:edges[c]){
                    deg[v[0]]-=1;
                    deg[v[1]]-=1;
                }
            }
        }
        vector<int> pv(2*n,-1), from(2*n,-1), to(2*n,-1), que; int qIt=0;
        ru(i,n,id){
            if(pv[i]!=-1) continue;
            que.push_back(i);
            pv[i]=-2;
            while(qIt<(int)que.size()){
                int v=que[qIt];
                from[v]=(int)que.size();
                for(int u:g[v]){
                    if(pv[u]==-1){
                        pv[u]=qIt;
                        que.push_back(u);
                    }
                }
                to[v]=(int)que.size()-1;
                qIt+=1;
            }
        }
        int sz=(int)que.size();
        if(sz==0){
            while(t--) cout<<0<<endl;
            return 0;
        }
        vector<pair<int, ld>> init(sz);
        ru(i,0,sz){init[i]=make_pair(0,-weight[que[i]]);}
        segtree st(init);
        while(t--){
            int op,v;
            cin>>op>>v;
            --v;
            if(pv[v]!=-1){
                st.modify(pv[v],pv[v],op==0?+1:-1);
                if(from[v]<=to[v]){
                    st.modify(from[v],to[v],op==0?+1:-1);
                }
            }
            auto nd=st.get(0,sz-1).val;
            cout<<(nd.first==0?-nd.second:0)<<endl;
        }
    }
};
#include "../../sum/template/mint.cpp"
struct i{ // divide, tedukuri-ds
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n; vector<ld>a(n);ru(i,0,n)cin>>a[i];
            vector<ld>p(n+1);ru(i,0,n)p[i+1]=p[i]+a[i];
            Mint ans=0,sum=0; map<int,ld>mp;
            auto Modify=[&](int l,int r,ld val){
                sum+=Mint(r-l+1)*val;
                if(r<n){
                    mp[r+1]-=val; auto it=mp.find(r+1);
                    if(it->second<0){
                        auto extra=-it->second;
                        sum+=Mint(extra)*(n-(r+1)+1);
                        it=mp.erase(it);
                        while (extra>0&&it!=mp.end()){
                            auto take=min(it->second,extra);
                            extra-=take;
                            it->second-=take;
                            sum-=Mint(take)*(n-it->first+1);
                            if(it->second==0) it=mp.erase(it);
                            else break;
                        }
                    }
                }
            };
            vector<int> smin(1,n+1); vector<int> smax(1,n+1);
            rd_(i,n,0){
                {
                    vector<pair<int,int>>op;
                    while(smin.back()<=n&&p[i]<p[smin.back()]){
                        auto val=p[smin.back()]-p[i];
                        smin.pop_back();
                        op.emplace_back(smin.back()-1,val);
                    }
                    ld last=0;
                    for(int j=(int)op.size()-1;j>=0;j--){
                        ld now=op[j].second;
                        Modify(i+1,op[j].first,now-last);
                        last=now;
                    }
                    smin.push_back(i);
                }
                {
                    vector<pair<int,int>>op;
                    while(smax.back()<=n&&p[i]<p[smax.back()]){
                        auto val=p[smax.back()]-p[i];
                        smax.pop_back();
                        op.emplace_back(smax.back()-1,val);
                    }
                    ld last=0;
                    for(int j=(int)op.size()-1;j>=0;j--){
                        ld now=op[j].second;
                        Modify(i+1,op[j].first,now-last);
                        last=now;
                    }
                    smax.push_back(i);
                }
                if(i<n){
                    Modify(i+1,n,a[i]);
                    if(a[i]>0) mp[i+1]+=2*a[i];
                }
                ans+=sum;
            }
            cout<<ans<<endl;
        }
    }
};

int main(){
//    b b;b.main();
//    c c;c.main();
//    d d; d.main();

//    e e;e.main();
//    f f;f.main();
//    g g;g.main();
    i i; i.main();


}