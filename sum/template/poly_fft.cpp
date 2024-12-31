#include<bits/stdc++.h>
using namespace std;
const int M1=998244353,M2=1004535809,M3=469762049,E=524288,N=200005;
struct poly{
    const int M;
    poly(int _M):M(_M){}
    int R[N*4];
    long long qpow(long long a,long long b){
        long long ans=1;
        while(b){
            if(b&1)
                ans=ans*a%M;
            a=a*a%M;
            b>>=1;
        }
        return ans;
    }
    long long wn[N*4],iwn[N*4],inv[N*4],fac[N*4],ifac[N*4];
    void init(int E,int g){
        int i;
        iwn[E/2]=wn[E/2]=1;
        long long s1=qpow(g,(M-1)/E);
        long long s2=qpow(s1,M-2);
        for(i=E/2+1;i<E;++i){
            wn[i]=wn[i-1]*s1%M;
            iwn[i]=iwn[i-1]*s2%M;
        }
        for(i=E/2-1;i;--i){
            wn[i]=wn[i<<1];
            iwn[i]=iwn[i<<1];
        }
        ifac[0]=fac[0]=inv[1]=1;
        for(i=2;i<E;++i)
            inv[i]=inv[M%i]*(M-M/i)%M;
        for(i=1;i<E;++i){
            ifac[i]=inv[i]*ifac[i-1]%M;
            fac[i]=fac[i-1]*i%M;
        }
    }
    unsigned long long ccc[N*4];
    void NTT(long long *f,int lim,int op){
        int i,j,k;
        for(i=0;i<lim;++i){
            R[i]=(R[i>>1]>>1)|(i&1?lim>>1:0);
            if(R[i]<i)
                swap(f[R[i]],f[i]);
        }
        for(i=0;i<lim;++i)
            ccc[i]=(f[i]%M+M)%M;
        for(i=1;i<lim;i<<=1)
            for(j=0;j<lim;j+=(i<<1))
                for(k=j;k<j+i;++k){
                    long long w=(op==1?wn[k-j+i]:iwn[k-j+i]);
                    unsigned long long p=ccc[k+i]*w%M;
                    ccc[k+i]=ccc[k]+M-p;
                    ccc[k]+=p;
                }
        for(i=0;i<lim;++i)
            f[i]=ccc[i]%M;
        if(op==-1){
            long long inv=qpow(lim,M-2);
            for(i=0;i<lim;++i)
                f[i]=f[i]*inv%M;
        }
    }
    long long ta[N*4],tb[N*4];
    void mult(long long *a,int n,long long *b,int m,long long *c){
        int lim=1;
        while(lim<n+m)
            lim<<=1;
        copy(a,a+n,ta);
        copy(b,b+m,tb);
        for(int i=n;i<lim;++i)
            ta[i]=0;
        for(int i=m;i<lim;++i)
            tb[i]=0;
        NTT(ta,lim,1);
        NTT(tb,lim,1);
        for(int i=0;i<lim;++i)
            ta[i]=ta[i]*tb[i]%M;
        NTT(ta,lim,-1);
        copy(ta,ta+lim,c);
    }
}X(M1),Y(M2),Z(M3);