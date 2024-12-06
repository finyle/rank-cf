#include <bits/stdc++.h>

//2
//3 2
//10 10

#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define L(i, j, k) for(int i = (j); i <= (k); ++i)
#define R(i, j, k) for(int i = (j); i >= (k); --i)
#define ll long long
#define vi vector <int>
#define sz(a) ((int) (a).size())
#define me(f, x) memset(f, x, sizeof(f))
#define ull unsigned long long
#define pb emplace_back
using namespace std;
const int N = 133, mod = 1e9 + 7;
struct mint {
    int x;
    inline mint(int o = 0) {
        x = o;
    }
    inline mint &operator = (int o) {
        return x = o, *this;
    }
    inline mint &operator += (mint o) {
        return (x += o.x) >= mod && (x -= mod), *this;
    }
    inline mint &operator -= (mint o) {
        return (x -= o.x) < 0 && (x += mod), *this;
    }
    inline mint &operator *= (mint o) {
        return x = (ll) x * o.x % mod, *this;
    }
    inline mint &operator ^= (int b) {
        mint w = *this;
        mint ret(1);

        for (; b; b >>= 1, w *= w)
            if (b & 1)
                ret *= w;

        return x = ret.x, *this;
    }
    inline mint &operator /= (mint o) {
        return *this *= (o ^= (mod - 2));
    }
    friend inline mint operator + (mint a, mint b) {
        return a += b;
    }
    friend inline mint operator - (mint a, mint b) {
        return a -= b;
    }
    friend inline mint operator * (mint a, mint b) {
        return a *= b;
    }
    friend inline mint operator / (mint a, mint b) {
        return a /= b;
    }
    friend inline mint operator ^ (mint a, int b) {
        return a ^= b;
    }
};
inline mint qpow(mint x, int y = mod - 2) {
    return x ^ y;
}
mint fac[N], ifac[N], inv[N];
void init(int x) {
    fac[0] = ifac[0] = inv[1] = 1;
    L(i, 2, x) inv[i] = (mod - mod / i) * inv[mod % i];
    L(i, 1, x) fac[i] = fac[i - 1] * i, ifac[i] = ifac[i - 1] * inv[i];
}
mint C(int x, int y) {
    return x < y || y < 0 ? 0 : fac[x] * ifac[y] * ifac[x - y];
}
inline mint sgn(int x) {
    return (x & 1) ? mod - 1 : 1;
}

int n, m;
mint f[N][N];
mint g[N][N];
mint h1[N][N][N];
mint h2[N][N][N];
mint pw[N][N];
int ans[N][N][N];
int main() {
    ios :: sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    n = 130, m = 30;
    // n = m = 10;
    L(i, 0, max(n, m)) {
        pw[i][0] = 1;
        L(j, 1, max(n, m)) pw[i][j] = pw[i][j - 1] * i;
    }
    f[0][0] = 1;
    int c1 = 0, c2 = 0;
    L(test, 1, m) {
        me(g, 0);
        int up = n;
        L(i, 0, up + 1) L(j, 0, i) L(l, 0, i) h1[i][j][l] = h2[i][j][l] = 0;
        h2[0][0][0] = 1;
        L(i, 0, up + 1) {
            L(j, 0, i) L(l, 0, i) h1[i][j][l & 1] -= h1[i][j][l];
            L(j, 0, i) {
                for (int l = (i - j) & 1; l <= i; l += 2)
                    if (h1[i][j][l].x) {
                        L(k, 0, up - i) {
                            if (l > k) {
                                int tr = k - !(l & 1);

                                if (tr < 0)
                                    h2[i + k + 1][j + 3][0] += h1[i][j][l] * pw[test - 1][k];
                                else
                                    h2[i + k + 1][j + 2][tr] += h1[i][j][l] * pw[test - 1][k];
                            } else {
                                h2[i + k + 1][j + 1][k - l] += h1[i][j][l] * pw[test - 1][k];
                            }
                        }
                    }

                for (int r = (i - j) & 1; r <= i; r += 2)
                    if (h2[i][j][r].x) {
                        int l = r & 1;
                        L(k, 0, up - i) {
                            if (l > k) {
                                int tr = k - !(r & 1);

                                if (tr < 0)
                                    h2[i + k + 1][j + 3][0] += h2[i][j][r] * pw[test - 1][k];
                                else
                                    h2[i + k + 1][j + 2][tr] += h2[i][j][r] * pw[test - 1][k];
                            } else {
                                h2[i + k + 1][j + 1][k - l] += h2[i][j][r] * pw[test - 1][k];

                                L(d, r + 1, k) if (f[k][d].x)
                                        h1[i + k + 1][j + 1][d - r] += h2[i][j][r] * f[k][d];
                            }
                        }
                    }
            }
        }
        // cout << "H = " << h[1][1][0][0].x << endl;
        L(i, 1, up + 1)
            L(j, 1, i) {

                L(l, 0, i) if (h1[i][j][l].x) {
                        if (!l)
                            g[i - 1][j - 1] += h1[i][j][l];
                        else
                            g[i - 1][j - 1 + (l % 2 == 0 ? 2 : 1)] += h1[i][j][l];
                    }

                L(r, 0, i) if (h2[i][j][r].x) {
                        if (!(r & 1))
                            g[i - 1][j - 1] += h2[i][j][r];
                        else
                            g[i - 1][j - 1 + (r % 2 == 0 ? 2 : 1)] += h2[i][j][r];
                    }
            }
        L(i, 1, up) {
            mint vl = 0;

            if (i == 1)
                vl = test;
            else if (i % 2 == 1) {
                vl += pw[test - 1][i];
                L(p, 1, i - 2) {
                    int l = p, r = i - p - 1;

                    if (l > r)
                        swap(l, r);

                    L(j, 1, l) {
                        vl += f[r][j] * pw[test - 1][l];
                    }
                }
            }

            g[i][1] = vl;
            mint sum = 0;
            L(j, 1, i) sum += g[i][j];
            int pos = (i & 1) ? 3 : 2;
            g[i][pos] += pw[test][i] - sum;
        }
        swap(f, g);

        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                ans[test][i][j] = f[i][j].x;
            }
        }
    }
    // cout << "clock = " << clock() << endl;
    int T;
    cin >> T;

    while (T--) {
        int N, M;
        cin >> N >> M;
        L(i, 0, (N - 1) / 2)
            cout << ans[M][N][N - i * 2] << " ";
        cout << '\n';
    }

    return 0;
}