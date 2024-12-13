#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
int dest[N], visit_[N], ans[N], mp[N], ansinv[N], sp;
int pow2(int y, int M) {
    long long x = 2, ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % M;
        x = x * x % M, y >>= 1;
    }
    return ans % M;
}
vector<int> cyc[N];
void get() {
    sp = 0;
    int n, i, j, m, z, o;
    cin >> n >> m;
    for (i = 1; i <= n; i++) cyc[i].clear();
    for (i = 1; i <= n; i++) visit_[i] = 0, cin >> dest[i];
    for (i = 1; i <= n; i++) {
        if (visit_[i]) continue;
        j = i, z = 0; do { ++z, visit_[j] = 1, j = dest[j]; } while (j != i);
        cyc[z].push_back(i);
    }
    int lim = pow2(min(m, 20), 1e9), s = 0, d, t, num, cp;
    for (i = 1; i <= n; i++) {
        if (!cyc[i].size()) continue;
        int siz = cyc[i].size();
        if (i % 2 == 0 && siz % lim) {
            cout << "NO" << endl; return;
        } else {
            cp = -1;
            for (j = lim; j > 0; j /= 2) {
                while (siz >= j) {
                    siz -= j, d = s + j * i, t = j;
                    while (t--) {
                        ++s, ++cp, num = s, o = cyc[i][cp];
                        do {
                            ans[num] = o, num += pow2(m, i * j);
                            if (num > d) num -= j * i;
                            o = dest[o];
                        } while (o != cyc[i][cp]);
                    }
                    for (int k = sp + 1; k < sp + j * i; k++) mp[k] = k + 1;
                    mp[sp + j * i] = sp + 1, sp += j * i, s = d;
                }
            }
        }
    }
    cout << "YES" << endl;
    for (i = 1; i <= n; i++) ansinv[ans[i]] = i;
    for (i = 1; i <= n; i++) cout << ans[mp[ansinv[i]]] << " \n"[i == n];
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int T;
    cin >> T;
    while (T--) get();
    return 0;
}

//10
//5 3
//1 2 3 4 5
//7 2
//1 2 3 4 5 6 7
//8 998
//1 2 3 4 5 6 7 8
//6 1
//6 3 5 4 1 2
//4 8
//4 2 1 3
//9 1
//1 5 4 8 7 6 3 2 9
//5 9999999
//2 3 4 5 1
//7 97843220
//4 6 1 2 7 5 3
//3 1000000000
//2 1 3
//12 3
//8 9 10 1 5 3 11 4 7 6 12 2
