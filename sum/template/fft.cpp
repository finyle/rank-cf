#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll mod = 998244353;
const ll root = 15311432; // which is basically 3 ^ 119
const ll root_1 = 469870224;
const ll root_pw = (1 << 23);
ll fxp(ll a,ll n){
    if(!n) return 1;
    else if(n&1) return a*fxp(a,n^1)%mod;
    else {
        ll v=fxp(a,n>>1);
        return v*v%mod;
    }
}
ll inverse(ll a) {return fxp(a%mod, mod-2);}
void fft(vector<ll>&a, bool invert){
    int n=a.size();
    for(int i=1,j=0;i<n;i++){
        int bit=n>>1;
        for(;j&bit;bit>>=1) j^=bit;
        j^=bit;
        if(i<j) swap(a[i],a[j]);
    }
    for(int len=2;len<=n;len<<=1){
        ll wlen=invert?root_1:root;
        for(int i=len;i<root_pw;i<<=1){
            wlen=wlen*wlen%mod;
        }
        for(int i=0;i<n;i+=len){
            ll w=1;
            for(int j=0;j<len/2;j++){
                ll u=a[i+j],v=a[i+j+len/2]*w%mod;
                a[i+j]=u+v<mod?u+v:u+v-mod;
                a[i+j+len/2]=u-v>=0?u-v:u-v+mod;
                w=w*wlen%mod;
            }
        }
    }
    if(invert){
        ll n_1=inverse(n);
        for(ll& x:a) x=x*n_1%mod;
    }
}