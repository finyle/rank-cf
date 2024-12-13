#include <iostream>

void solve(){
    int n; std::cin >> n;
    for(int i = 1 ,nouse ; i <= n ; ++i){
        std::cin >> nouse;
    }
    std::cout << "1 " << n << std::endl;
}

int main(){
    int t; std::cin >> t;
    while(t--) solve();
    return 0;
}

// *******************
#include<bits/stdc++.h>
using namespace std;
const int maxn=100005;
int a[maxn];
int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}
int main(){
    int t;scanf("%d",&t);
    while(t--){
        int n;scanf("%d",&n);
        int tmp=0;
        for(int i=1;i<=n;++i){
            scanf("%d",&a[i]);
            tmp=gcd(tmp,a[i]);
        }
        printf("%d\n",a[n]/tmp+(a[1]==0));
    }
    return 0;
}

// ******************
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define ch() getchar()
#define pc(x) putchar(x)
using namespace std;
template<typename T>void read(T&x){
    static char c;static int f;
    for(f=1,c=ch();c<'0'||c>'9';c=ch())if(c=='-')f=-f;
    for(x=0;c>='0'&&c<='9';c=ch()){x=x*10+(c&15);}x*=f;
}
template<typename T>void write(T x){
    static char q[64];int cnt=0;
    if(x==0)return pc('0'),void();
    if(x<0)pc('-'),x=-x;
    while(x)q[cnt++]=x%10+'0',x/=10;
    while(cnt--)pc(q[cnt]);
}
const int maxn=200005;
int a[maxn];
int main(){
    int t;read(t);
    while(t--){
        int n;read(n);
        for(int i=1;i<=n;++i)
            read(a[i]);
        sort(a+1,a+n+1);
        if(a[1]==a[n]){
            write(n/2),pc('\n');
            continue;
        }
        long long ans=0;
        for(int l=1,r=1;l<=n;l=r=r+1){
            while(r+1<=n&&a[r+1]==a[l])++r;
            ans=max(ans,1ll*(n-r)*r);
        }
        write(ans),pc('\n');
    }
    return 0;
}

// **********************
#include <cstdio>
#include <iostream>

#define LL long long

const int MX = 5000 + 233;
LL C[MX][MX] ,n ,p ,fac[MX];

void init(){
    for(int i = 0 ; i < MX ; ++i) C[i][0] = 1;
    for(int i = 1 ; i < MX ; ++i)
        for(int j = 1 ; j < MX ; ++j)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % p;
    fac[0] = fac[1] = 1 % p;
    for(int i = 2 ; i < MX ; ++i) fac[i] = fac[i - 1] * i % p;
}

int main(){
    std::cin >> n >> p;
    init();
    int t = n / 2;
    LL Ans = 0;
    for(int i = t ; i <= n - 1 ; ++i){
        if((n & 1) && i == n - 1) break;
        int upper = (i == n - 1) ? n - i - 1 : n - i - 2;
        for(int j = 0 ; j <= upper ; ++j){
            Ans = (Ans + n * (2 * t - i) * C[upper][j] % p * fac[j + i - 1]) % p;
        }
    }
    std::cout << Ans << std::endl;
    return 0;
}