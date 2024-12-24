#include <bits/stdc++.h>
#define ru_(i,l,r) for(int i=(l);i<=(r);i++)
#define ru(i,l,r) for(int i=(l);i<(r);i++)
#define rup(i,l,r) for(int i=(l);i<=(r);i+=2)
#define rd(i,r,l) for(int i=(r);i>=(l);i--)
#define ll long long
#define pli pair<ll,int>
#define pll pair<ll,ll>
#define s1 first
#define s2 second

using namespace std;

struct a{
    int main(){
        int t; cin>>t;
        while(t--){
            int n,k; cin>>n>>k;
            if(k==1) ru(i,0,n) cout<<i+1<<" ";
            else if(k==n) ru(i,0,n) cout<<1<<" ";
            else cout<<-1;
            cout<<endl;
        }; return 0;
    }
};
struct b{
    int main(){
        int t; cin>>t;
        while(t--){
            int n; cin>>n; vector<int> a(n); for(auto &x:a) cin>>x;
            vector<int>p(n),has(n+1); int mex=0;
            ru(i,0,n){
                if(a[i]>=0) p[i]=mex;
                else p[i]=mex-a[i];
                has[p[i]]=true;
                while(has[mex]) mex++;
            }
            for(int i: p) cout<<i<<" "<<endl;
        }; return 0;
    }
};
struct c{
    void solve(){
        int n,x,y; cin>>n>>x>>y;
        int initial_y=y; vector<int> chosen(x); for(int &i:chosen) cin>>i;
        sort(chosen.begin(), chosen.end());
        int ans=x-2; int tri=0; vector<int> odd_g;
        auto pro=[&](int g) -> void{
            if (g<=1) ans+=g;
            else if(g%2==1) odd_g.push_back(g/2);
            else tri+=g/2;
        };
        ru(i,0,x-1) pro(chosen[i+1]-chosen[i]-1);
        pro((chosen[0]+n)-chosen[x-1]-1);
        sort(odd_g.begin(), odd_g.end());
        for(int g: odd_g){
            if(y>=g){ans+=g+1; y-=g;}
            else {ans+=y; y=0; break;}
        }
        int even_tri=min(tri,y);
        y-=even_tri;
        ans+=even_tri;
        int used_vertices=initial_y-y;
        ans+=used_vertices; cout <<ans<<endl;
    }
    int main(){int t; cin>>t; while(t--) solve();return 0;}
};
struct d{
    void solve(){
        int n,k; cin>>n>>k; int A[n+1][n+1];
        ru_(i,1,n) ru_(j,i,n) cin>>A[i][j];
        vector<int> dp[n+1]; dp[0]={0};
        ru_(i,1,n){
            priority_queue<array<int,3>> pq;
            pq.push({dp[i-1][0], i-1,0});
            for(int j=i-2;j>=-1;j--) pq.push({(j<0?0:dp[j][0])+A[j+2][i],j,0});
            while(pq.size() && dp[i].size()<k){
                auto[val,j,num]=pq.top(); pq.pop();
                dp[i].push_back(val);
                if(j<0 or num+1>=dp[j].size()) continue;
                if(j==i-1) pq.push({dp[i-1][num+1],i-1,num+1});
                else pq.push({dp[j][num+1]+A[j+2][i],j,num+1});
            }
        }
        for(int i: dp[n]) cout<<i<<" ";cout<<endl;
    };
    int main(){int t;cin>>t;while(t--)solve();return 0;}
};

// math
struct e{
    static const int max=1e4+5,mod=998244353;
    ll fact[max],ifact[max];
    ll bpow(ll a,ll p){
        ll ans=1;
        for(;p;p/=2,a=(a*a)%mod) if(p&1) ans=(ans*a)%mod;
        return ans;
    }
    ll ncr(int n,int r){
        if(n<0) return 0;
        if(r>n) return 0;
        return fact[n]*ifact[r]%mod*ifact[n-r]%mod;
    }
    void solve(){
        int l,n; cin>>l>>n; ll all_even=0;
        for(int s=0;s<=l;s+=2){all_even+=2*ncr(s/2+n-1,n-1)%mod*ncr(l-s-n,n)%mod; all_even%=mod;}
        cout<<(2*ncr(l,2*n)%mod-all_even+mod)%mod<<" \n";
    }
    int main(){
        ru(i,0,max) fact[i]=!i?1:fact[i-1]*i%mod;
        rd(i,max-1,0) ifact[i]=(i==max-1)?bpow(fact[max-1],mod-2):ifact[i+1]*(i+1)%mod;
        int t;cin>>t;while(t--)solve();return 0;
    };
};

// seg
struct f{

    static const int B=6, MAX=2e4+B+5;
    static int n,q,offset,numBlocks; ll A[MAX]; pll seg[MAX];
    pll comb(pll a,pll b){
        auto[vl,cl]=a; auto[vr,cr]=b;
        if(vl==-1) return b;
        if(vr==-1) return a;
        if(vl<cr-1) return {vr,(ll)2e18};
        return {vr,cl};
    }
    void updSeg(int i,pll v){
        seg[i+=numBlocks]=v;
        for(i/=2;i>0;i/=2) seg[i]=comb(seg[i*2],seg[i*2+1]);
    }
    ll qry(int l=0,int r=numBlocks-1){
        pll retL={-1,-1}, retR={-1,-1};
        for(l+=numBlocks,r+=numBlocks;l<=r;r/=2,l/=2){
            if(l%2==1) retL=comb(retL,seg[l++]);
            if(r%2==0) retR=comb(seg[r--],retR);
        }; return comb(retL,retR).first;
    }
    void upBlock(int blk){
        int l=blk*B, r=l+B-1; ll val=0;
        ru_(i,l,r) val=floor(sqrtl((long double) val+A[i]));
        ll req=val+1;
        rd(i,r,l){
            if(req>2e9){updSeg(blk,{val,(ll)2e18}); return;}
            req=req*req-A[i];
        }; updSeg(blk,{val,req});
    }
    int main(){
        cin>>n>>q; offset=(B-n%B)%B; n+=offset; numBlocks=n/B;
        ru(i,offset,n) cin>>A[i];
        ru(i,0,numBlocks) upBlock(i);
        while(q--) {
            ll k,x; cin>>k>>x; k--; k+=offset;
            A[k]=x; upBlock(k/B); cout<<qry()<<endl;
        }; return 0;
    }
};

int main(){
//    a a;
//    a.main();

//    c c;
//    c.main();

//    d d;
//    d.main();

//    e e;
//    e.main();

//    f f;
//    f.main();

}