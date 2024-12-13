#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

const int N = 3e5 + 5;
const int mod = 998244353;
const int inv2 = 499122177;

ll qpow (ll n, ll m) {
    ll ret = 1;
    while (m) {
        if (m & 1) ret = ret * n % mod;
        n = n * n % mod;
        m >>= 1;
    }
    return ret;
}
ll getinv (ll a) {
    return qpow(a, mod - 2);
}

int n, k;
int a[N];
int u[N], v[N];

vector <int> e[N];
int fa[N];
ll p[N], sum[N];
void dfs (int u, int f) {
    sum[u] = p[u];
    for (int v : e[u]) if (v != f) {
            dfs(v, u);
            fa[v] = u;
            sum[u] += sum[v];
        }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> k;
    for (int i = 1;i <= k;++i) {
        cin >> a[i];
        p[a[i]] = 1;
    }
    for (int i = 1;i <= n - 1;++i) {
        cin >> u[i] >> v[i];
        e[u[i]].push_back(v[i]);
        e[v[i]].push_back(u[i]);
    }
    dfs(1, -1);

    ll ans = 0;
    for (int i = 1;i <= n - 1;++i) {
        if (fa[u[i]] == v[i]) swap(u[i], v[i]);
        ll puv = p[u[i]] * (1 - p[v[i]] + mod) % mod;
        ll pvu = p[v[i]] * (1 - p[u[i]] + mod) % mod;
        ll delta = 0;
        delta -= puv * sum[v[i]] % mod * (k - sum[v[i]]) % mod;
        delta -= pvu * sum[v[i]] % mod * (k - sum[v[i]]) % mod;
        delta += puv * (sum[v[i]] + 1) % mod * (k - sum[v[i]] - 1) % mod;
        delta += pvu * (sum[v[i]] - 1) % mod * (k - sum[v[i]] + 1) % mod;
        ans = (ans + sum[v[i]] * (k - sum[v[i]]) + delta * inv2) % mod;
        ans = (ans % mod + mod) % mod;
        p[u[i]] = p[v[i]] = 1ll * (p[u[i]] + p[v[i]]) * inv2 % mod;
    }
    cout << ans * getinv(1ll * k * (k - 1) / 2 % mod) % mod << endl;
}

//3 2
//1 3
//1 2
//2 3
