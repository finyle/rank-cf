#include <bits/stdc++.h>

#define File(a) freopen(a ".in", "r", stdin), freopen(a ".out", "w", stdout)

using tp = std::tuple<int, int, int>;
const int sgn[] = {1, 998244352};
const int N = 200005;

int x[N], y[N];
std::vector<tp> V;
bool del[N];
int fa[20][N];
int m, q;

int main() {
    scanf("%d %d", &m, &q);
    for (int i = 1; i <= m; ++i)
        scanf("%d %d", x + i, y + i), V.emplace_back(y[i], -x[i], i);
    std::sort(V.begin(), V.end());
    int mxl = 0;
    for (auto [y, x, i] : V) {
        if (-x <= mxl) del[i] = true;
        mxl = std::max(mxl, -x);
    }
    V.clear();
    x[m + 1] = y[m + 1] = 1e9 + 1;
    for (int i = 1; i <= m + 1; ++i) {
        if (!del[i]) V.emplace_back(x[i], y[i], i);
    }
    std::sort(V.begin(), V.end());
    for (auto [x, y, id] : V) {
        int t = std::get<2>(*std::lower_bound(V.begin(), V.end(), tp{y + 1, 0, 0}));
        fa[0][id] = t;
    }
    fa[0][m + 1] = m + 1;
    for (int k = 1; k <= 17; ++k) {
        for (int i = 1; i <= m + 1; ++i) fa[k][i] = fa[k - 1][fa[k - 1][i]];
    }
    for (int i = 1; i <= q; ++i) {
        int l, r;
        scanf("%d %d", &l, &r);
        int u = std::lower_bound(V.begin(), V.end(), tp{l, 0, 0}) - V.begin(), v = u + 1;
        u = std::get<2>(V[u]);
        if (x[u] != l || y[u] > r) {
            puts("0");
            continue;
        }
        if (y[u] == r) {
            puts("998244352");
            continue;
        }
        v = std::get<2>(V[v]);
        if (y[v] > r || x[v] > y[u]) {
            puts("0");
            continue;
        }
        int numu = 0, numv = 0;
        for (int i = 17; i >= 0; --i) {
            if (y[fa[i][u]] <= r) {
                u = fa[i][u];
                numu += !i;
            }
        }
        for (int i = 17; i >= 0; --i) {
            if (y[fa[i][v]] <= r) {
                v = fa[i][v];
                numv += !i;
            }
        }
        if (u == v || (y[u] != r && y[v] != r))
            puts("0");
        else
            printf("%d\n", sgn[numu ^ numv]);
    }
    return 0;
}

//4 2
//1 3
//4 6
//2 4
//3 5
//1 4
//1 5
