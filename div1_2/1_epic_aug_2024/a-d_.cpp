#include <bits/stdc++.h>

#define ru(i, l, r) for (int i = (l); i <= (r); i++)
#define pb push_back
#define ll long long

using namespace std;

struct Sol1 {
    int main() {
        int t, n, m, k;
        scanf("%d", &t);
        while (t--) {
            scanf("%d%d%d", &n, &m, &k);
            printf("%d\n", min(n, k) * min(m, k));
        }
        return 0;
    }
};

struct Sol2 {
    int read() {
        int x = 0, w = 0;
        char ch = getchar();
        while (!isdigit(ch)) w |= ch == '-', ch = getchar();
        while (isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
        return w ? -x : x;
    }
    int main() {
        int t = read();
        while (t--) {
            int n = read();
            vector<int> a, b;
            ru(i, 1, n) a.pb(read());
            ru(i, 1, n) b.pb(read());

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
    }
};

struct Sol3 {
    ll dis(int x1, int y1, int x2, int y2) {
        return 1ll * (x2 - x1) * (x2 - x1) + 1ll * (y2 - y1) * (y2 - y1);
    }
    int main() {
        int t, n, x[100011], y[100011], xs, ys, xt, yt;
        scanf("%d", &t);
        while (t--) {
            scanf("%d", &n);
            ru(i, 1, n) scanf("%d%d", x + i, y + i);
            scanf("%d%d%d%d", &xs, &ys, &xt, &yt);
            bool ok = 1;
            ru(i, 1, n) {
                if (dis(xt, yt, x[i], y[i]) <= dis(xt, yt, xs, ys)) {
                    ok = 0;
                    break;
                }
            }
            printf(ok ? "YES\n" : "NO\n");
        }
        return 0;
    }
};

struct Sol4 {
    
};
int main() {
//    Sol1 s1;
//    s1.main();

//    Sol2 s2;
//    s2.main();

    Sol3 s3;
    s3.main();
    return 0;
}