#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for (int i = 0; i < (n); ++i)
#define Inf32 1000000001
#define Inf64 4000000000000000001

int main(){

    int _t;
    cin>>_t;

    rep(_,_t){
        int n,m;
        cin>>n>>m;
        vector<long long> a(n+m);
        rep(i,n+m)scanf("%lld",&a[i]);

        sort(a.begin(),a.end()-1);
        reverse(a.begin(),a.end());

        long long ans = 0;
        rep(i,n)ans += a[i];

        cout<<ans<<endl;
    }


    return 0;
}

// ************************
#include <iostream>
#define MULTI int _T; cin >> _T; while(_T--)
using namespace std;
typedef long long ll;

int n, k;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    MULTI {
        cin >> n >> k;
        int l = 1, r = n, _ = 1;
        while (l <= r) cout << ((_ ^= 1) ? l++ : r--) << ' ';
        cout << endl;
    }
}

// *******************
#include <iostream>
#include <algorithm>
#define MULTI int _T; cin >> _T; while(_T--)
using namespace std;
typedef long long ll;

const int N = 105;
const int INF = 0x3f3f3f3f;
template <typename T> bool chkmin (T &x, T y) {return y < x ? x = y, 1 : 0;}
template <typename T> bool chkmax (T &x, T y) {return y > x ? x = y, 1 : 0;}

int n;
ll a[N];

int cnt[N];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    MULTI {
        cin >> n;
        for (int i = 1;i <= n;++i) {
            cin >> a[i];
        }

        int isDistinct = 1;
        sort(a + 1, a + n + 1);
        for (int i = 1;i <= n - 1;++i) {
            if (a[i] == a[i + 1]) isDistinct = 0;
        }
        if (isDistinct == 0) {
            cout << "NO" << endl;
            continue;
        }

        int CRT_able = 1;
        for (int mod = 2;mod <= n / 2;++mod) {
            fill(cnt, cnt + mod, 0);
            for (int i = 1;i <= n;++i) {
                cnt[a[i] % mod]++;
            }
            if (*min_element(cnt, cnt + mod) >= 2) CRT_able = 0;
        }
        cout << (CRT_able ? "YES" : "NO") << endl;
    }
}

// ***********************
#include <iostream>
#include <numeric>
#define MULTI int _T; cin >> _T; while(_T--)
using namespace std;
typedef long long ll;

const int N = 1e5 + 5;
const int mod = 998244353;

int n;
int a[N], b[N];

int fa[N], cnt_v[N], cnt_e[N], selfloop[N];
int vis[N];
void init () {
    iota(fa + 1, fa + n + 1, 1);
    fill(cnt_v + 1, cnt_v + n + 1, 1);
    fill(cnt_e + 1, cnt_e + n + 1, 0);
    fill(selfloop + 1, selfloop + n + 1, 0);
    fill(vis + 1, vis + n + 1, 0);
}
int getfa (int x) {
    return fa[x] == x ? x : fa[x] = getfa(fa[x]);
}
void merge (int u, int v) {
    u = getfa(u);
    v = getfa(v);
    cnt_v[u] += cnt_v[v];
    cnt_e[u] += cnt_e[v];
    selfloop[u] |= selfloop[v];
    fa[v] = u;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    MULTI {
        cin >> n;
        for (int i = 1;i <= n;++i) {
            cin >> a[i];
        }
        for (int i = 1;i <= n;++i) {
            cin >> b[i];
        }

        init();
        for (int i = 1;i <= n;++i) {
            if (getfa(a[i]) != getfa(b[i])) merge(a[i], b[i]);
            cnt_e[getfa(a[i])]++;
            if (a[i] == b[i]) selfloop[getfa(a[i])] = 1;
        }

        ll ans = 1;
        for (int i = 1;i <= n;++i) if (vis[getfa(i)] == 0) {
                if (cnt_v[getfa(i)] != cnt_e[getfa(i)]) ans = 0;
                else ans = ans * (selfloop[getfa(i)] ? n : 2) % mod;
                vis[getfa(i)] = 1;
            }
        cout << ans << endl;
    }
}