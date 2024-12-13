#include <iostream>

const int P = 998244353;

long long Pow(long long a, int n) {
    long long r = 1;
    while (n) {
        if (n & 1) r = r * a % P;
        a = a * a % P, n >>= 1;
    }
    return r;
}
inline void inc(int& a, int b) {
    if((a += b) >= P) a -= P;
}

int n, m, G[20][2], f[1 << 20];

int main() {
    std::cin >> n >> m;
    while (m--) {
        int t, i, j;
        std::cin >> t >> i >> j;
        i--, j--;
        G[i][t] |= 1 << j;
        G[j][t] |= 1 << i;
    }
    f[0] = 1;
    for (int S = 0; S < 1 << n; S++)
        for (int i = 0; i < n; i++) if (~S >> i & 1) {
                if ((G[i][0] | S) == S) inc(f[S | 1 << i], f[S]);
                if ((G[i][1] | S) == S) inc(f[S | 1 << i], f[S]);
            }
    long long t = 1;
    for (int i = 1; i <= n; i++) t = t * i * 2 % P;
    std::cout << f[(1 << n) - 1] * Pow(t, P - 2) % P << '\n';
}