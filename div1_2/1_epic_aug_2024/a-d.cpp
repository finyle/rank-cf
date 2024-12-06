#include <bits/stdc++.h>
using namespace std;
int t, n, m, k;
int main() {
    scanf("%d", &t);

    while (t--) {
        scanf("%d%d%d", &n, &m, &k);
        printf("%d\n", min(n, k)*min(m, k));
    }

    return 0;
}

// *******************

#include <bits/stdc++.h>
#define ll long long
#define lc(x) ((x) << 1)
#define rc(x) ((x) << 1 | 1)
#define ru(i, l, r) for (int i = (l); i <= (r); i++)
#define rd(i, r, l) for (int i = (r); i >= (l); i--)
#define mid ((l + r) >> 1)
#define pii pair<int, int>
#define mp make_pair
#define fi first
#define se second
#define sz(s) (int)s.size()
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
using namespace std;
mt19937 Rand(chrono::steady_clock::now().time_since_epoch().count());
int read() {
    int x = 0, w = 0;
    char ch = getchar();

    while (!isdigit(ch))
        w |= ch == '-', ch = getchar();

    while (isdigit(ch))
        x = x * 10 + ch - '0', ch = getchar();

    return w ? -x : x;
}
int main() {
    int T = read();

    while (T--) {
        int n = read();
        vector<int> a, b;
        ru(i, 1, n) a.push_back(read());
        ru(i, 1, n) b.push_back(read());

        if (a == b) {
            printf("Bob\n");
            continue;
        }

        reverse(a.begin(), a.end());

        if (a == b) {
            printf("Bob\n");
            continue;
        }

        printf("Alice\n");
    }

    return 0;
}

// *******************************
#include <bits/stdc++.h>
#define ll long long
using namespace std;
int t, n, x[100011], y[100011], xs, ys, xt, yt;
ll dis(int x1, int y1, int x2, int y2) {
    return 1ll * (x2 - x1) * (x2 - x1) + 1ll * (y2 - y1) * (y2 - y1);
}
int main() {
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);

        for (int i = 1; i <= n; ++i)
            scanf("%d%d", x + i, y + i);

        scanf("%d%d%d%d", &xs, &ys, &xt, &yt);
        bool ok = 1;

        for (int i = 1; i <= n; ++i) {
            if (dis(xt, yt, x[i], y[i]) <= dis(xt, yt, xs, ys)) {
                ok = 0;
                break;
            }
        }

        printf(ok ? "YES\n" : "NO\n");
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

// *********************************
#include <bits/stdc++.h>
#define ll long long
#define lc(x) ((x) << 1)
#define rc(x) ((x) << 1 | 1)
#define ru(i, l, r) for (int i = (l); i <= (r); i++)
#define rd(i, r, l) for (int i = (r); i >= (l); i--)
#define mid ((l + r) >> 1)
#define pii pair<int, int>
#define mp make_pair
#define fi first
#define se second
#define sz(s) (int)s.size()
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
using namespace std;
#define maxn 500005
mt19937 Rand(chrono::steady_clock::now().time_since_epoch().count());
int read() {
    int x = 0, w = 0; char ch = getchar();
    while(!isdigit(ch)) w |= ch == '-', ch = getchar();
    while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
    return w ? -x : x;
}
int n, Q, fa[maxn], p[maxn], q[maxn], siz[maxn];
set<int> son[maxn];
int chk(int x) {
    return son[x].empty() ? 1 : (q[x] < *son[x].begin() && *--son[x].end() + siz[p[*--son[x].end()]] <= q[x] + siz[x]);
}
void solve() {
    n = read(), Q = read();
    ru(i, 1, n) siz[i] = 1, son[i].clear();
    ru(i, 2, n) fa[i] = read();
    rd(i, n, 2) siz[fa[i]] += siz[i];
    ru(i, 1, n) son[fa[p[i] = read()]].insert(i), q[p[i]] = i;
    int cnt = 0;
    ru(i, 1, n) cnt += chk(i);
    while(Q--) {
        int i = read(), j = read(), x = p[i], y = p[j];
        set<int> s; s.insert(x), s.insert(y), s.insert(fa[x]), s.insert(fa[y]);
        for (auto x: s) if(x) cnt -= chk(x);
        son[fa[x]].erase(i), son[fa[y]].erase(j);
        swap(p[i], p[j]), swap(q[x], q[y]);
        son[fa[x]].insert(j), son[fa[y]].insert(i);
        for (auto x: s) if(x) cnt += chk(x);
        puts(cnt == n ? "YES" : "NO");
    }
}
int main() {
    int T = read();
    while(T--) solve();
    return 0;
}