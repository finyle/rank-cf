#include <bits/stdc++.h>
using namespace std;
const int N = 200005;

// *****************2*******************
struct Sol1 {
    #define mp make_pair
    pair<int, int> s[110];
    int d[110];
    void get() {
        int n, l = 0, i, c;
        cin >> n;
        for (i = 2; i * i <= n; i++) {
            if (n % i == 0) {
                c = 0;
                while (n % i == 0) c++, n /= i;
                s[++l] = make_pair(c, i);
            }
        }
        if (n != 1) s[++l] = make_pair(1, n);
        sort(s + 1, s + l + 1), d[l + 1] = 1;
        for (i = l; i >= 1; i--) d[i] = d[i + 1] * s[i].second;
        int ans = 0;
        for (i = 1; i <= l; i++) if (s[i].first != s[i - 1].first) ans += d[i] * (s[i].first - s[i - 1].first);
        cout << ans << endl;
    }
    signed main() {
        ios::sync_with_stdio(0);
        cin.tie(0);
        int T;
        cin >> T;
        while (T--) get();
        return 0;
    }
};

//7
//100
//10
//864
//130056192
//1000000000
//2
//999999018

// *****************3*******************


struct Sol3 {
    long long f[N][2],x[N],y[N];
    void get() {
        int i,n,s,j;
        cin>>n>>s;
        for(i=1; i<=n; i++) {
            cin>>j;
            if(i==1||i==n) x[i]=y[i]=j;
            else if(j<=s) x[i]=0,y[i]=j;
            else x[i]=s,y[i]=j-s;
        }
        f[1][0]=f[1][1]=0;
        for(i=2; i<=n; i++) {
            f[i][0]=min(f[i-1][0]+y[i-1]*x[i],f[i-1][1]+x[i-1]*x[i]);
            f[i][1]=min(f[i-1][0]+y[i-1]*y[i],f[i-1][1]+x[i-1]*y[i]);
        }
        cout<<f[n][0]<<endl;
    }
    int main() {
        ios::sync_with_stdio(0);
        cin.tie(0);
        int T; cin>>T;
        while(T--) get();
        return 0;
    }
};

//10
//5 0
//2 0 1 3 4
//5 1
//5 3 4 3 5
//7 2
//7 6 5 4 3 2 1
//5 1
//1 2 3 4 5
//5 2
//1 2 3 4 5
//4 0
//0 1 1 1
//5 5
//4 3 5 6 4
//4 1
//0 2 1 0
//3 99999
//200000 200000 200000
//6 8139
//7976 129785 12984 78561 173685 15480

// *****************4*******************

struct Sol4 {
    int a[N];
    int v[N]; //= 1 -> in the tree with the end node
    int s[N]; //subtree size
    struct E {
        int to;
        E *nex;
    } *h[N];
    void add(int u, int v) {
        E *cur = new E;
        cur->to = v, cur->nex = h[u], h[u] = cur;
    }
    void dfs(int u) {
        s[u] = v[u] = 1;
        for (E *cur = h[u]; cur; cur = cur->nex)
            dfs(cur->to), s[u] += s[cur->to];
    }
    void get() {
        int i, j, n;
        cin >> n;
        for (i = 1; i <= n + 1; i++)
            s[i] = v[i] = 0, h[i] = 0;
        for (i = 1; i <= n; i++) {
            cin >> a[i], a[i] = min(i + a[i], n + 1);
            if (a[i] <= 0) a[i] = n + 1;
            add(a[i], i);
        }
        dfs(n + 1); //start with the end point, dfs the tree
        long long ans = 0;
        if (v[1] == 1) {
            j = 1; do { ans -= s[j] + (n - s[n + 1] + 1), j = a[j]; }
            while (j != n + 1);
            ans += 1ll * n * (2 * n + 1);
        } else {
            j = 1; do { ans += (n + s[n + 1]), v[j] = 2, j = a[j]; }
            while (v[j] != 2);
        }
        cout << ans << endl;
    }
    int main() {
        ios::sync_with_stdio(0);
        cin.tie(0);
        int T;
        cin >> T;
        while (T--) get();
        return 0;
    }
};


int main() {
//    Sol1 s1;
//    s1.main();

//    Sol3 s3;
//    s3.main();

    Sol4 s4;
    s4.main();
    return 0;
}