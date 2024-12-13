#include <bits/stdc++.h>
using namespace std;

char c[1005];
int main() {
    int t;
    scanf("%d", &t);
    int n;
    while (t--) {
        scanf("%d", &n);
        scanf("%s", c + 1);
        int u = 0;
        for (int i = 1; i <= n; ++i) {
            bool fl = (c[i] == '1') && u;
            u ^= (c[i] - '0');
            if (i != 1) putchar(fl ? '-' : '+');
        }
        putchar('\n');
    }
}

// *******************
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, m, k;
        scanf("%d %d %d", &n, &m, &k);
        int fl = 0;
        for (int i = 1; i <= m; ++i) {
            int a;
            scanf("%d", &a);
            if (a == (n + k - 1) / k) ++fl;
            if (a > (n + k - 1) / k) fl = 1 << 30;
        }
        puts(fl <= (n - 1) % k + 1 ? "YES" : "NO");
    }
}

// ************************
#include <bits/stdc++.h>
using namespace std;

const int N = 300005;
int T, n, ps[2];
char a[N];

void solve() {
    scanf("%d %s", &n, a + 1);
    ps[0] = ps[1] = 0;
    for (int i = 1; i < n; ++i) {
        ps[a[i] - 48] = i;
        if (a[i] == '0')
            printf("%d ", ps[1] + 1);
        else
            printf("%d ", ps[0] + 1);
    }
    putchar('\n');
}
int main() {
    scanf("%d", &T);
    while (T--) solve();
    return 0;
}

// ***********************
#include <bits/stdc++.h>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);
        std::vector<std::vector<int>> A(n, std::vector<int>(m, 0));
        std::vector<int> sum(n, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                scanf("%d", &A[i][j]);
                sum[i] += A[i][j];
            }
        }
        int tot = 0;
        for (int i = 0; i < n; ++i) tot += sum[i];
        if (tot % n) {
            puts("-1");
            continue;
        }
        tot /= n;
        std::vector<std::tuple<int, int, int>> ans;
        std::vector<int> Vg, Vl;
        Vg.reserve(n), Vl.reserve(n);
        for (int j = 0; j < m; ++j) {
            for (int i = 0; i < n; ++i) {
                if (sum[i] > tot && A[i][j]) Vg.push_back(i);
                if (sum[i] < tot && !A[i][j]) Vl.push_back(i);
            }
            for (int i = 0; i < (int)std::min(Vl.size(), Vg.size()); ++i) {
                ++sum[Vl[i]], --sum[Vg[i]];
                ans.emplace_back(Vl[i], Vg[i], j);
            }
            Vl.clear(), Vg.clear();
        }
        printf("%d\n", (int)ans.size());
        for (auto [i, j, k] : ans) printf("%d %d %d\n", i + 1, j + 1, k + 1);
    }
    return 0;
}

