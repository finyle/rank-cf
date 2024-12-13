#include<bits/stdc++.h>
using namespace std;


// *********************1***********************
struct Sol1 {

    int a[100005];
    void solve()
    {
        int n;
        scanf("%d",&n);
        for(int i  =1;i <= n;i++) scanf("%d",&a[i]);
        for(int i = 1;i <= n;i++) {
            if(a[i] <= i) {
                puts("YES");
                return;
            }
        }
        puts("NO");
    }
    int main()
    {
        int t;scanf("%d",&t);
        while(t--) solve();
    }
};

//7
//3
//3 2 1
//4
//2 4 3 5
//5
//2 3 5 5 6
//2
//3 1
//5
//2 4 5 2 3
//4
//5 6 7 8
//6
//6 5 4 3 2 1


// *********************2***********************
struct Sol2 {
    void solve()
    {
        int n;scanf("%d",&n);
        if(n % 2 == 0) {
            puts("-1");return;
        }
        vector<int> v;
        int f = 0;
        for(int i = 29;i >= 1;i--) {
            if((n >> i) & 1) {
                f = 1;
                v.push_back(2);
            }
            else if(f) {
                v.push_back(1);
            }
        }
        printf("%d\n",v.size());
        for(auto x : v) {
            printf("%d ",x);
        }
        printf("\n");
    }
    int main()
    {
        int t;scanf("%d",&t);
        while(t--) solve();
        return 0;
    }
};
//4
//2
//3
//7
//17

// *********************3***********************
struct Sol3 {
    int p[100005];
    typedef long long ll;
    void solve()
    {
        int n,a,b;scanf("%d%d%d",&n,&a,&b);
        set<int> st;
        ll sol = 0 , ans = 2e18;
        for(int i = 1;i <= n;i++) {
            int x;scanf("%d",&x);
            if(st.find(x) == st.end()) st.insert(x);
            else sol += a;
        }
        int c = 0;
        for(auto x : st) p[++c] = x;
        for(int i = 1;i <= c;i++) {
            ans = min(ans , 1LL*(p[i] - i)*b + 1LL*(c-i)*a);
        }
        ans = min(ans , 1LL*c*a + b) ;
        printf("%lld\n",ans+sol);
    }
    int main()
    {
        int t;scanf("%d",&t);
        while(t--) solve();
    }
};
//8
//3 3 3
//1 2 3
//5 1 5
//1 2 3 5 6
//5 2 3
//1 1 1 3 3
//5 1 10
//2 4 6 8 10
//6 2 8
//7 3 5 4 4 8
//4 10 1
//1 2 6 7
//4 3 3
//2 5 8 7
//2 1000000000 1
//1000000000 1

// *********************4***********************

struct Sol4 {
    typedef long long ll;
    void solve()
    {
        int q;scanf("%d",&q);
        ll L = 1 , R = 1e18;
        while(q--) {
            int op;scanf("%d",&op) ;
            if(op == 1) {
                int a,b,n;scanf("%d%d%d",&a,&b,&n);
                ll ql = 1LL*(n - 2)*(a - b) + a + 1, qr = 1LL*(n - 1)*(a - b) + a;
                if(n == 1) ql = 1 , qr = a;
                if(ql > R || qr < L) {
                    puts("0");
                }
                else L = max(L , ql) , R = min(R , qr) , puts("1");
            }
            else {
                int a,b;scanf("%d%d",&a,&b);
                ll ans1 = max(1LL,(L - b - 1) / (a - b) + 1) , ans2 = max(1LL,(R - b - 1) / (a - b) + 1);
                if(ans1 == ans2) printf("%lld\n",ans1);
                else puts("-1");
            }
        }
        return;
    }
    int main()
    {
        int t;scanf("%d",&t);
        while(t--) solve();
    }
};

//5
//3
//1 3 2 5
//2 4 1
//2 3 2
//3
//1 6 5 1
//2 3 1
//2 6 2
//3
//1 4 2 2
//1 2 1 3
//2 10 2
//9
//1 7 3 6
//1 2 1 8
//2 5 1
//1 10 9 7
//1 8 1 2
//1 10 5 8
//1 10 7 7
//2 7 4
//1 9 4 2
//9
//1 2 1 6
//1 8 5 6
//1 4 2 7
//2 9 1
//1 5 1 4
//1 5 2 7
//1 7 1 9
//1 9 1 4
//2 10 8

int main() {
//    Sol1 s1;
//    s1.main();

//    Sol2 s2;
//    s2.main();

//    Sol3 s3;
//    s3.main();

    Sol4 s4;
    s4.main();
    return 0;
}