#include <bits/stdc++.h>
#define ll long long
#define N 20000011
using namespace std;
int t, n, m, a, b;
bool is[N];
int pr[N / 10];
int gcd(int a, int b) {
    while (b)
        a %= b, swap(a, b);

    return a;
}
ll ans = 0;
bool vis[1011][1011];
pair<int, int> vv[200011];
int vn, c;
bool flg = 0;
inline ll V(int i, int j) {
    return i <= n ? 1ll * max(i, j) * max(a, b) + 1ll * min(i, j) * min(a, b) : 1ll * i * b + 1ll * j * a;
}
void dfs(int i, int j) {
    ++c;
    bool mk = gcd(i, j) == 1;

    if (!mk)
        return;

    ans = max(ans, V(i, j));
    vis[m - i][n - j] = 1;
    vv[++vn] = {i, j};

    if (j < n && !vis[m - i][n - j - 1])
        dfs(i, j + 1);

    if (i == m || flg) {
        flg = 1;
        return;
    }

    if (i < m && !vis[m - i - 1][n - j])
        dfs(i + 1, j);
}
int main() {
    is[0] = is[1] = 1;

    for (int i = 2; i < N; ++i) {
        if (!is[i])
            pr[++pr[0]] = i;

        for (int j = 1; j <= pr[0] && i * pr[j] < N; ++j) {
            is[i * pr[j]] = 1;

            if (i % pr[j] == 0)
                break;
        }
    }

    scanf("%d", &t);

    while (t--) {
        scanf("%d%d%d%d", &n, &m, &a, &b);
        int p;

        if (m <= 10)
            p = 1;
        else {
            p = m;

            while (is[p])
                --p;
        }

        vn = 0;
        ans = 0;
        flg = 0;
        c = 0;

        for (int i = min(n, p - (p > 1));; --i) {
            assert(i > 0);
            ans = max(ans, V(p, i));

            if (p < m)
                dfs(p + 1, i);
            else
                break;

            if (flg)
                break;
        }

        for (int i = 1; i <= vn; ++i)
            vis[m - vv[i].first][n - vv[i].second] = 0;

        printf("%lld\n", ans);
    }

    return 0;
}

//8
//3 4 2 5
//4 4 1 4
//6 6 2 2
//7 9 2 3
//8 9 9 1
//2 7 1 4
//5 9 1 4
//5 6 6 7
