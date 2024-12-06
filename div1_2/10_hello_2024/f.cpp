
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll LINF = 1000000000000000005ll;
const int MAXN = 500005;

int n, q;
int a[MAXN], b[MAXN];
ll c[MAXN];

ll st[MAXN * 4][2][2];
void merge(int u, int lo, int hi) {
    int mid = lo + hi >> 1, lc = u << 1, rc = u << 1 ^ 1;
    for (int l = 0; l < 2; l++) {
        for (int r = 0; r < 2; r++) {
            st[u][l][r] = min({st[lc][l][0] + st[rc][0][r],
                               st[lc][l][1] + st[rc][1][r],
                               st[lc][l][0] + st[rc][1][r],
                               st[lc][l][1] + st[rc][0][r] + c[mid]});
        }
    }
}
void init(int u = 1, int lo = 1, int hi = n) {
    if (lo == hi) {
        st[u][0][0] = a[lo];
        st[u][1][1] = b[lo];
        st[u][1][0] = st[u][0][1] = LINF;
        return;
    }
    int mid = lo + hi >> 1, lc = u << 1, rc = u << 1 ^ 1;
    init(lc, lo, mid);
    init(rc, mid + 1, hi);
    merge(u, lo, hi);
}
void upd(int p, int u = 1, int lo = 1, int hi = n) {
    if (lo == hi) {
        st[u][0][0] = a[lo];
        st[u][1][1] = b[lo];
        st[u][1][0] = st[u][0][1] = LINF;
        return;
    }
    int mid = lo + hi >> 1, lc = u << 1, rc = u << 1 ^ 1;
    if (p <= mid) {
        upd(p, lc, lo, mid);
    } else {
        upd(p, rc, mid + 1, hi);
    }
    merge(u, lo, hi);
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    for (int i = 1; i < n; i++) {
        cin >> c[i];
    }
    init();
    while (q--) {
        int p, x, y; ll z; cin >> p >> x >> y >> z;
        a[p] = x; b[p] = y; c[p] = z;
        upd(p);
        cout << min({st[1][0][0], st[1][0][1], st[1][1][0], st[1][1][1]}) << '\n';
    }
}

//4 3
//3 3 3 3
//1 4 2 8
//5 2 1
//4 3 8 1000000000
//2 5 1 1
//3 0 0 0
