#include <bits/stdc++.h>

void solve(__int128 n, __int128 a, __int128 b, __int128 c, __int128 &f) {
    if (n < 0) { f = 0; return; }
    if (a >= c || b >= c) {
        solve(n, a % c, b % c, c, f);
        f += (a / c) * (n * (n + 1) / 2) + (b / c) * (n + 1);
    } else if (a) {
        __int128 m = (a * n + b) / c;
        solve(m - 1, c, c - b - 1, a, f);
        f = n * m - f;
    }
}

const long double k = (1 + sqrt((long double) 5)) / 2;

int n;
long long ans;
__int128 a, b, c, d;

int main() {
    int T;
    scanf("%d", &T);
    __int128 x = (__int128) 2000000000000000000ll * 1000000000;
    __int128 y = (__int128) 1000000000000000000ll * 1000000000;
    __int128 z = (__int128) 1618033988749894848ll * 1000000000 + 204586834;
    for (; T; T--) {
        scanf("%d", &n);
        int i = 0;
        for (int l = 0, r = n - 1, mid; l <= r; ) {
            mid = l + r >> 1;
            if (n - floor(mid / k) <= mid + mid) {
                i = mid; r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        solve((n - 1) / 2, x, 0, z, a);
        solve((i - 1) / 2, x, 0, z, b);
        solve((n - 2) / 2, x, y, z, c);
        solve((i - 2) / 2, x, y, z, d);
        ans = i + (i % 2 ? -1 : 1) * ((a - b) - (c - d));
        if ((n - i) % 2) { ans = n - ans; }
        printf("%lld\n", ans);
    }
    return 0;
}

//5
//2
//4
//7
//15
//177567
