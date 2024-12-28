#ifndef LOCAL
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx,avx2,fma")
#pragma GCC target("sse4,popcnt,abm,mmx,tune=native")
#endif
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

#define pb push_back
#define ff first
#define ss second

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<ld, ld> pld;

const int INF = 1e9;
const ll LLINF = 1e18;
const int MOD = 1e9 + 7;

template<class K> using sset =  tree<K, null_type, less<K>, rb_tree_tag, tree_order_statistics_node_update>;

inline ll ceil0(ll a, ll b) {
    return a / b + ((a ^ b) > 0 && a % b);
}

void setIO() {
    ios_base::sync_with_stdio(0); cin.tie(0);
}

struct Matrix {

    array<array<ll, 3>, 3> mat;

    array<ll, 3> &operator[](int x){
        return mat[x];
    }

    const array<ll, 3> &operator[](int x) const {
        return mat[x];
    }

    Matrix(){
        for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) mat[i][j] = 0;
    }

    Matrix operator*(const Matrix &x){
        Matrix ret;
        for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) ret[i][j] = LLINF;
        for(int i = 0; i < 3; i++){
            for(int k = 0; k < 3; k++){
                for(int j = 0; j < 3; j++){
                    ret[i][j] = min(ret[i][j], mat[i][k] + x[k][j]);
                }
            }
        }
        return ret;
    }

    Matrix &operator*=(const Matrix &x){
        (*this) = (*this) * x;
        return *this;
    }
};

struct fastset {

    priority_queue<ll, vector<ll>, greater<ll>> q, rem;

    void insert(ll x){
        q.push(x);
    }

    void erase(ll x){
        rem.push(x);
    }

    ll query(){
        while(rem.size() && q.top() == rem.top()){
            rem.pop();
            q.pop();
        }
        return q.top();
    }

    void clear(){
        while(q.size()) q.pop();
        while(rem.size()) rem.pop();
    }
};

vector<int> g[500005];
int sub[500005];
int head[500005];
int par[500005];
int tim = 0;
vector<int> chain[500005];
int weight[500005];

void dfs1(int x){
    sub[x] = 1;
    for(int &i : g[x]){
        dfs1(i);
        sub[x] += sub[i];
        if(sub[i] > sub[g[x][0]]) swap(i, g[x][0]);
    }
}

int in[500005], out[500005];
int dir[500005];

void dfs2(int x, int p){
    chain[head[x]].pb(x);
    par[x] = p;
    weight[x] = 1;
    in[x] = tim++;
    for(int i : g[x]){
        head[i] = (i == g[x][0] ? head[x] : i);
        dfs2(i, x);
        if(i != g[x][0]) weight[x] += sub[i];
    }
    out[x] = tim - 1;
}

Matrix dp[500005];
Matrix cum[500005];
int rt[500005];
int left0[500005], right0[500005], ppar[500005];

int dnq(int l, int r, int p, const vector<int> &v){
    if(l > r) return 0;
    int sum = 0;
    for(int i = l; i <= r; i++) sum += weight[v[i]];
    int cur = 0;
    int mid = -1;
    for(int i = l; i <= r; i++){
        cur += weight[v[i]];
        if(cur >= sum/2){
            mid = i;
            break;
        }
    }
    if(p == -1) ppar[v[mid]] = v[mid];
    else ppar[v[mid]] = p;
    left0[v[mid]] = dnq(l, mid - 1, v[mid], v);
    right0[v[mid]] = dnq(mid + 1, r, v[mid], v);
    return v[mid];
}

void merge(int x){
    if(right0[x] && left0[x]){
        cum[x] = cum[left0[x]]*dp[x]*cum[right0[x]];
    } else if(left0[x] && !right0[x]){
        cum[x] = cum[left0[x]]*dp[x];
    } else if(right0[x] && !left0[x]){
        cum[x] = dp[x]*cum[right0[x]];
    } else {
        cum[x] = dp[x];
    }
}

void pull(int x){
    while(x != rt[x]){
        merge(x);
        x = ppar[x];
    }
    merge(x);
}

ll a[500005], b[500005], c[500005];
ll dp0[500005][3];

void dfs3(int x){
    dp0[x][0] = a[x];
    dp0[x][2] = b[x] + c[x];
    ll deg1 = a[x] + c[x], deg2 = b[x] + a[x] + c[x];
    ll mn1 = LLINF, mn2 = LLINF;
    for(int i : g[x]){
        dfs3(i);
        dp0[x][0] += dp0[i][0];
        dp0[x][2] += dp0[i][2];
        deg1 += min(dp0[i][0], dp0[i][1]);
        deg2 += min({dp0[i][0], dp0[i][1], dp0[i][2]});
        mn1 = min(mn1, max((ll)0, dp0[i][1] - dp0[i][0]));
        mn2 = min(mn2, max((ll)0, min(dp0[i][1], dp0[i][2]) - dp0[i][0]));
    }
    dp0[x][1] = min(deg1 + mn1, deg2 + mn2);
}

fastset deg1[500005], deg2[500005];
ll sum0[500005], sum2[500005], sum01[500005], sum012[500005];

void rebuild(int x){
    dp[x][0][0] = a[x] + sum0[x];
    dp[x][0][1] = LLINF;
    dp[x][0][2] = LLINF;
    if(g[x].size()){
        dp[x][1][0] = min(a[x] + b[x] + c[x] + deg2[x].query() + sum012[x], a[x] + c[x] + deg1[x].query() + sum01[x]);
        dp[x][1][1] = min(a[x] + c[x] + sum01[x], a[x] + b[x] + c[x] + sum012[x]);
        dp[x][1][2] = a[x] + b[x] + c[x] + sum012[x];
    } else {
        dp[x][1][0] = dp[x][1][1] = dp[x][1][2] = LLINF;
    }
    dp[x][2][0] = LLINF;
    dp[x][2][1] = LLINF;
    dp[x][2][2] = b[x] + c[x] + sum2[x];
}

ll eval(int x, int ind){
    return min({cum[rt[x]][ind][0], cum[rt[x]][ind][1], cum[rt[x]][ind][2]});
}

void rem(int x){
    while(head[x] != 1){
        if(x == head[x]){
            ll v0 = eval(x, 0), v1 = eval(x, 1), v2 = eval(x, 2);
            deg1[par[x]].erase(max((ll)0, v1 - v0));
            deg2[par[x]].erase(max((ll)0, min(v1, v2) - v0));
            sum012[par[x]] -= min({v0, v1, v2});
            sum01[par[x]] -= min(v0, v1);
            sum0[par[x]] -= v0;
            sum2[par[x]] -= v2;
            x = par[x];
        }
        x = head[x];
    }
}

void add(int x){
    while(head[x] != 1){
        if(x == head[x]){
            ll v0 = eval(x, 0), v1 = eval(x, 1), v2 = eval(x, 2);
            deg1[par[x]].insert(max((ll)0, v1 - v0));
            deg2[par[x]].insert(max((ll)0, min(v1, v2) - v0));
            sum012[par[x]] += min({v0, v1, v2});
            sum01[par[x]] += min(v0, v1);
            sum0[par[x]] += v0;
            sum2[par[x]] += v2;
            rebuild(par[x]);
            pull(par[x]);
            x = par[x];
        }
        x = head[x];
    }
}

int main(){
    setIO();
    int t;
    cin >> t;
    while(t--){
        int n, q;
        cin >> n >> q;
        for(int i = 2; i <= n; i++){
            int x;
            cin >> x;
            g[x].pb(i);
        }
        ll sum = 0;
        for(int i = 1; i <= n; i++) cin >> b[i], sum += b[i];
        dfs1(1);
        head[1] = 1;
        dfs2(1, 1);
        dfs3(1);
        for(int i = 1; i <= n; i++){
            if(chain[i].size()){
                int p = dnq(0, chain[i].size() - 1, -1, chain[i]);
                for(int j : chain[i]) rt[j] = p;
            }
        }
        for(int i = 1; i <= n; i++){
            deg1[i].insert(LLINF);
            deg2[i].insert(LLINF);
            for(int j : g[i]){
                if(head[j] == head[i]) continue;
                deg1[i].insert(max((ll)0, dp0[j][1] - dp0[j][0]));
                deg2[i].insert(max((ll)0, min(dp0[j][1], dp0[j][2]) - dp0[j][0]));
                sum012[i] += min({dp0[j][0], dp0[j][1], dp0[j][2]});
                sum01[i] += min(dp0[j][0], dp0[j][1]);
                sum0[i] += dp0[j][0];
                sum2[i] += dp0[j][2];
            }
            rebuild(i);
            pull(i);
        }
        while(q--){
            int t, x, v;
            cin >> t >> x >> v;
            rem(x);
            if(t == 1) a[x] += v;
            else c[x] += v, sum += v;
            rebuild(x);
            pull(x);
            add(x);
            cout << (min({eval(1, 0), eval(1, 1), eval(1, 2)}) == sum ? "YES" : "NO") << "\n";
        }
        tim = 0;
        for(int i = 1; i <= n; i++){
            a[i] = b[i] = c[i] = 0;
            g[i].clear();
            chain[i].clear();
            deg1[i].clear();
            deg2[i].clear();
            sum0[i] = sum2[i] = sum01[i] = sum012[i] = 0;
        }
    }
}

//2
//8 8
//1 1 1 4 3 6 6
//5 6 2 9 8 4 1 3
//1 3 14
//1 4 17
//1 2 7
//2 2 1
//1 6 1
//2 1 1000000
//1 4 999999
//1 3 1
//10 20
//1 1 1 2 5 2 4 7 2
//311353 270334 74853 385085 315501 183346 234819 417314 103862 429437
//1 1 837541
//1 10 933876
//1 1 565958
//1 4 791455
//2 3 85054
//2 3 440978
//1 4 981040
//1 5 68522
//2 1 858305
//2 4 184308
//1 4 905081
//2 8 519626
//2 2 269090
//1 1 43016
//2 2 517644
//1 5 355792
//1 9 319241
//2 10 125447
//2 10 523890
//1 10 241045
