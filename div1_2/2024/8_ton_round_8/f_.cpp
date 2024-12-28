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