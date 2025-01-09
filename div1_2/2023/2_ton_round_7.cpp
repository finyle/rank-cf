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
            int n;cin>>n;vector<int>a(n);ru(i,0,n)cin>>a[i];
            if(a[0]==1)cout<<"yes";
            else cout<<"no";
            cout<<endl;
        }
    }
};
struct b{
    char s[20005];
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n;s[n+1]='C';
            ru_(i,1,n)cin>>s[i];
            int pt1=1,pt2=1,ans=0;
            while(s[pt1]=='B')pt1++,pt2++;
            while(pt1<=n){
                int cntA=0,cntB=0;
                while(s[pt1]=='A')pt2++,cntA++;
                while(s[pt2]=='B')pt2++,cntB++;
                if(s[pt2-1]=='B')ans+=pt2-pt1-1;
                if(cntB)pt1=pt2-1;
                else break;
            }
            cout<<ans<<endl;
        }
    }
};
struct c{
    static const int N=1e4+5;
    int main(){
        int t;cin>>t;
        while(t--){
            int n;cin>>n;int a[N],b[N],aid[N],ans[N];
            ru(i,0,n)cin>>a[i];ru(i,0,n)cin>>b[i];
            iota(aid,aid+n,0);sort(aid,aid+n,[&](int l,int r){return a[l]<a[r];});
            sort(b,b+n); int x;
            ru(i,0,x) ans[aid[n-x+i]]=b[i];
            ru(i,x,n) ans[aid[i-x]]=b[i];
            ru(i,0,n) x-=a[i]>ans[i];
            if(x==0){
                cout<<"yes";
                ru(i,0,n) cout<<ans[i]<<' ';
                cout<<endl;
            } else cout<<"no";
        }
    }
};
struct d{
    int main(){
        int t;cin>>t;
        while(t--){
            int n,q;cin>>n>>q;vector<int>a(n);set<int>pos;
            ru(i,0,n){
                cin>>a[i];
                if(a[i]==1)pos.insert(i);
            }
            while(q--){
                int cmd;cin>>cmd;
                if(cmd==1){
                    int v;cin>>v; int num=pos.size();
                    if((v-num)&1){
                        if(num==0)cout<<"no";
                        else{
                            int s1=2**pos.begin()-(num-1);
                            int s2=2*(n-*pos.begin()-1)-(num-1);
                            if(v<=max(s1,s2))cout<<"yes";
                            else cout<<"no";
                        }
                    }else{
                        if(v<=2*n-num)cout<<"yes";
                        else cout<<"no";
                    }
                    cout<<endl;
                }else{
                    int i;cin>>i;i--;
                    pos.erase(i);cin>>a[i];
                    if(a[i]==1)pos.insert(i);
                }
            }
        }
    }
};
struct e{
#define ALL(_a)_a.begin(),_a.end()
    static const int maxn=1e4+5;
    int p[maxn],ans[maxn],fw[maxn*2];
    int n;
    void incre(int i,int x){
        for(;i<=2*n;i+=i&-i) fw[i]+=x;
    }
    int qsm(int i){
        int res=0;
        for(;i>0;i-=i&-i) res+=fw[i];
        return res;
    }
    inline int qsm(int s,int e){
        return qsm(e)-qsm(s-1);
    }
    int main(){
        int t;cin>>t;
        while(t--){
            cin>>n;ru(i,1,n+1)cin>>p[i+1];ru(i,0,2*n+5)fw[i]=0;
            vector<pair<int,int>>rgs;
            ru(i,1,n+1){
                if(i<=p[i]){
                    rgs.push_back({i,p[i]});
                    rgs.push_back({i+n,p[i]+n});
                }else{
                    rgs.push_back({i,p[i]+n});
                }
            }
            sort(ALL(rgs),greater<pair<int,int>>());
            for(auto [l,r]:rgs){
                if(l<=n) ans[p[l]]=r-l-qsm(l,r);
                incre(r,1);
            }
            ru(i,1,n+1) cout<<ans[i]<<' ';
            cout<<endl;
        }
    }
};
struct f{
    void solve(int n,string s){
        vector<int>a; for(char &i:s)a.push_back(i&1);
        if(a.front()!=a.back()){cout<<-1<<endl; return ;}
        if(count(a.begin(),a.end(),1)%2){cout<<-1<<endl;return ;}
        bool flipped=false;
        if(a.front()==1&&a.back()==1){
            for(int &i:a)i^=1; flipped=true;
        }
        string l(2*n,'-'),r(2*n,'='); int cnt=0;
        ru(i,0,2*n){
            if(a[i]){
                l[i]=(cnt)?'(':')';
                r[i]=(cnt^1)?'(':')';
                cnt^=1;
            }
        }
        int tot=count(a.begin(),a.end(),0)/2; cnt=0;
        ru(i,0,n*2){
            if(!a[i]){
                if(cnt<tot)l[i]='(',r[i]='(';
                else l[i]=')',r[i]=')';
                cnt++;
            }
        }
        if(flipped){
            cout<<3<<endl; cout<<l<<endl; cout<<r<<endl;
            ru(i,0,n)cout<<"()";
            cout<<endl;
        }else{
            cout<<2<<endl; cout<<l<<endl; cout<<r<<endl;
        }

    }
    int main(){
        int t;cin>>t;
        while(t--){ios::sync_with_stdio(0); cin.tie(0);int n;cin>>n;string s;cin>>s;solve(n,s);}
    }
};
struct g{ //interactive
};
struct h{ //fft
};

int main(){
    a a;a.main();
}