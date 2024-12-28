#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()

const char nl = '\n';
typedef long long ll;
typedef long double ld;

using namespace std;

int ans_x = 0, ans_y = 0, cnt_q = 0;
// Coordinates are flipped
int query(int x, int y) {
    cnt_q++;

    int res = 0;
    cout << "? " << y << ' ' << x << endl;
    cout.flush();

    cin >> res;

    if (res < 0) {
        exit(0);
    }

    if (res == 0) {
        ans_x = x;
        ans_y = y;
    }

    return res;
}

/* Explanation:
 * Splits the stripe of three into |a-O-a-b-O-b-a-O-a|.
 * O are the three query points (all in the same column).
 * Cons: hard to correctly account for errors in a non-bruteforce way.
 * Pros: gives a better constant factor (3 / 4 of the original length)
 * Number of queries: n + 3 * 21 + 25 * ceil(log(25, 2)) + eps
 * Though the binary search part uses less queries than that */

void f(int lx, int rx, int ly, int ry) {
    int n = rx - lx + 1;

    // Bruteforce base case (uses binary search)
    if (n <= 25) { // can be n <= 22 or above
        for (int x = lx; x <= rx; x++) {
            int lb = ly, ub = ry;

            while (lb <= ub) {
                int res = query(x, lb);

                int low_y = ((res - 1) + 1) / 2, high_y = res;

                int new_lb = lb + max(1, low_y), new_ub = min(ub, lb + high_y);
                lb = new_lb;
                ub = new_ub;
            }
        }

        return;
    }


    // Here, (2a - 1) + (2b - 1) + (2a - 1) = n
    int a = 3 * (n + 3) / 16;
    int y = min(ry, ly + 1);

    int x1 = lx + a - 1;
    x1 = max(x1, lx);
    x1 = min(x1, rx);

    int x2 = (lx + rx) / 2;
    x2 = max(x2, x1 + 1);
    x2 = min(x2, rx);

    int x3 = rx - a + 1;
    x3 = max(x3, x2 + 1);
    x3 = min(x3, rx);


    int m = min(3, ry - ly + 1);
    vector<vector<bool>> good(n, vector<bool> (m, true));

    int new_lx = lx, new_rx = rx;
    int new_ly = ly, new_ry = ry;

    for (int x: {x1, x2, x3}) {
        int res = query(x, y);

        new_lx = max(new_lx, x - res);
        new_rx = min(new_rx, x + res);

        new_ly = max(new_ly, y - res);
        new_ry = min(new_ry, y + res);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int r_x = lx + i, r_y = ly + j;

                int dx = abs(r_x - x);
                int dy = abs(r_y - y);

                int d = dx + dy;
                int S = (dx + 1) * (dy + 1);

                // d <= res <= d + S must hold
                if (res < d || d + S < res) {
                    good[i][j] = false;
                }
            }
        }
    }

    bool has_good = false;
    for (auto vx: good) {
        for (auto vy: vx) {
            if (vy) {
                has_good = true;
            }
        }
    }
    good.clear();
    good.shrink_to_fit();

    if (has_good) {
        f(new_lx, new_rx, new_ly, new_ry);
    } else {
        f(lx, rx, ly + m, ry);
    }
}

void solve() {
    int n, m;
    cin >> n >> m;
    ans_x = 0; ans_y = 0; cnt_q = 0;

    f(1, m, 1, n);

    cout << "! " << ans_y << ' ' << ans_x << endl;
    cout.flush();

    cerr << n << ' ' << cnt_q << " | " << n + 225 << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int T;
    cin >> T;
    while (T--) {
        solve();
    }
}

//2
//3 4
//
//5
//
//3
//
//5
//
//1 1
//
//0
//
