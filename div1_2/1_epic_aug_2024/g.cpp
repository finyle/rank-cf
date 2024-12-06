#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define int long long
void dbg_out() {
    cerr << endl;
}
template <typename H, typename... T>
void dbg_out(H h, T... t) {
    cerr << ' ' << h;
    dbg_out(t...);
}
#define dbg(...) { cerr << #__VA_ARGS__ << ':'; dbg_out(__VA_ARGS__); }
using ll = long long;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

const int MAXN = 3e7 + 5;
const int MOD = 1e9 + 7; //998244353;
const int INF = 0x3f3f3f3f;
const ll INF64 = ll(4e18) + 5;

int D[40][40];
int R[40][40];

int L;

int32_t trie[MAXN][2];
int n;
int li = 1;
void add(int x) {
    int at = 0;
    int K = 2 * n - 2;

    for (int i = 0; i <= K; i++) {
        int id = (x >> i) & 1;

        if (trie[at][id] == 0) {
            trie[at][id] = li++;
        }

        at = trie[at][id];
    }
}

void limpa() {
    for (int i = 0; i < li; i++) {
        trie[i][0] = trie[i][1] = 0;
    }

    li = 1;
}

int query(int at, int x, int dep) {
    int id = (x >> dep) & 1;

    if (id == 0) {
        if (trie[at][1]) {
            return query(trie[at][1], x, dep + 1);
        }

        return dep;
    }

    int ans = dep;

    if (trie[at][0])
        ans = max(ans, query(trie[at][0], x, dep + 1));

    if (trie[at][1])
        ans = max(ans, query(trie[at][1], x, dep + 1));

    while ((x >> ans) & 1)
        ans++;

    return ans;
}

void rec_in(int i, int j, int tar1, int tar2, int v) {
    if (i > tar1 || j > tar2)
        return;

    if (i == tar1 && j == tar2) {
        add(v);
    }

    int right = v | (1ll << R[i][j]);
    int down = v | (1ll << D[i][j]);
    rec_in(i + 1, j, tar1, tar2, down);
    rec_in(i, j + 1, tar1, tar2, right);
}

int ANS = 0;
void rec_out(int i, int j, int tar1, int tar2, int v) {
    if (i < tar1 || j < tar2)
        return;

    if (i == tar1 && j == tar2) {
        ANS = max(ANS, query(0, v, 0));
        return;
    }

    int left = v | (1ll << R[i][j - 1]);
    int up = v | (1ll << D[i - 1][j]);
    rec_out(i - 1, j, tar1, tar2, up);
    rec_out(i, j - 1, tar1, tar2, left);
}

void solve() {
    ANS = 0;

    for (int i = 1; i <= li; i++)
        trie[i][0] = trie[i][1] = 0;

    li = 1;
    cin >> n;
    L = 4 * n / 3;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n; j++) {
            cin >> D[i][j];
        }
    }

    if (L > n) {
        L--;
    }

    if (L > n) {
        L--;
    }

    if (L > n) {
        L--;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            cin >> R[i][j];
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i + j == L) {
                limpa();
                rec_in(0, 0, i, j, 0);
                rec_out(n - 1, n - 1, i, j, 0);
            }

    cout << ANS << '\n';

}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}

//2
//3
//1 0 2
//0 1 3
//2 1
//0 3
//3 0
//3
//1 2 0
//0 1 2
//2 0
//1 2
//0 1
