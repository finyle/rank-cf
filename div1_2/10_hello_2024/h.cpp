//5
//
//3
//
//1
//
//9
//
//0


#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF = 1000000000;
const int MAXN = 1000;

int n;
int lvl[MAXN + 5];
int pe[MAXN + 5];
vector<int> ch[MAXN + 5];

ll query(vector<int> a) {
    cout << "? 1";
    for (int i = 1; i < n; i++) {
        cout << ' ' << a[i];
    }
    cout << endl;
    ll res; cin >> res;
    return res;
}
int query(int a, int b) {
    cout << "? 2 " << a << ' ' << b << endl;
    int res; cin >> res;
    return res;
}

int main() {
    cin >> n;
    for (int i = 2; i < n; i++) {
        lvl[i] = query(1, i);
    }
    int ptr = 3;
    vector<int> base = {1, 2};
    pe[1] = pe[2] = 1;
    bool iso = 1;
    int piv = -1;
    for (int l = 0; l < n; l++) {
        vector<int> a(n, 1);
        int m = base.size();
        for (int i = 0; i < m; i++) {
            a[pe[base[i]]] = min(i + 1, m - iso) * MAXN;
        }
        if (!iso) {
            a[pe[piv]] = INF;
        }
        bool ciso = 0;
        for (int u = 2; u < n; u++) {
            if (lvl[u] != l) {
                continue;
            }
            a[u] = INF;
            ll res = query(a) - INF;
            a[u] = 1;
            if (!iso || ciso) {
                res -= INF;
            }
            int id = res / MAXN;
            if (iso && l) {
                id -= m - 1;
            }
            int v = ptr++;
            pe[v] = u;
            if (ciso) {
                if ((l == 0 && id == 0) || id == -(m - 1)) {
                    ch[base[m - 2]].push_back(v);
                } else if (id == m - 1) {
                    ch[base[m - 1]].push_back(v);
                } else {
                    ch[base[id - 1]].push_back(v);
                }
            } else if (iso && id == m - 1) {
                ch[base[m - 2]].push_back(v);
                ciso = 1;
                a[u] = INF;
            } else {
                ch[base[id - 1]].push_back(v);
            }
        }
        if (m >= 2 && ch[base[m - 2]].size() > ch[base[m - 1]].size()) {
            swap(base[m - 2], base[m - 1]);
        }
        vector<int> nbase;
        for (int i = 0; i < m; i++) {
            for (int j : ch[base[i]]) {
                nbase.push_back(j);
            }
        }
        if (!iso || ch[base[m - 1]].size() >= 2 || ch[base[m - 2]].size() == 1) {
            base = nbase;
            continue;
        }
        if (ch[base[m - 1]].empty()) {
            piv = base[m - 1];
        } else {
            ll res = query(pe[ch[base[m - 1]][0]], pe[base[m - 1]]);
            if (res) {
                swap(base[m - 2], base[m - 1]);
                swap(ch[base[m - 2]], ch[base[m - 1]]);
            }
            piv = base[m - 2];
        }
        iso = 0;
        base = nbase;
    }
    cout << '!' << endl;
    cout << 1 << ' ' << 2 << endl;
    for (int u = 1; u <= n; u++) {
        for (int v : ch[u]) {
            cout << u << ' ' << v << endl;
        }
    }
}