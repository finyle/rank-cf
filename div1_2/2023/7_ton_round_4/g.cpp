#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
const int N = 5005;
int p[N] , q[N];
int n;
int f[N][N];
int h[N];
int fpow(int a,int b)
{
    int ans = 1;
    while(b){
        if(b & 1) ans = 1LL*ans*a%mod;
        a = 1LL*a*a%mod;b >>= 1;
    }
    return ans;
}
void solve()
{
    scanf("%d",&n);
    for(int i = 1;i <= n;i++) {
        int a,b;scanf("%d%d",&a,&b);
        p[i] = 1LL*a*fpow(b , mod - 2) % mod;
        q[i] = (1 - p[i] + mod) % mod;
    }
    for(int i = 0;i <= n;i++) scanf("%d",&h[i]);
    for(int i = 0;i <= n;i++) f[0][i] = h[i];
    for(int i = 1;i <= n;i++) {
        for(int j = 0;j <= n;j++) {
            f[i][j] = (1LL*p[i]*f[i - 1][j + 1] + 1LL*q[i]*f[i - 1][max(0 , j - 1)] ) % mod;
        }
        printf("%d ",f[i][0]);
    }
    printf("\n");
    return;
}

//4
//2
//1 2
//1 2
//1 2 3
//3
//1 3
//1 4
//5 5
//1 1 1 1
//3
//2 5
//4 6
//0 2
//4 3 2 1
//5
//5 6
//5 7
//1 6
//1 3
//4 7
//9 0 4 5 2 4

int main()
{
    int t;scanf("%d",&t);
    while(t--) solve();
    return 0;
}