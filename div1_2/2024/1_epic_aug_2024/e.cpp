#include <bits/stdc++.h>
#define ll long long
#define N 3000011
#define pii pair<ll,int>
#define s1 first
#define s2 second
using namespace std;
int t, n, prv[N], nxt[N], b[N];
ll a[N];
priority_queue<pair<ll, int>> pq, del;
ll sum = 0, ans[N];
int main() {
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);

        for (int i = 1; i <= n; ++i)
            scanf("%lld%d", a + i, b + i);

        while (!pq.empty())
            pq.pop();

        while (!del.empty())
            del.pop();

        nxt[0] = 1;
        prv[n + 1] = n;

        for (int i = 1; i <= n; ++i)
            pq.push({-a[i], i}), prv[i] = i - 1, nxt[i] = i + 1;
        ll tim = 0;
        int lst = 1;

        for (int _ = 1; _ <= n; ++_) {
            while (!del.empty() && pq.top() == del.top())
                pq.pop(), del.pop();

            pii p = pq.top();
            pq.pop();
            int id = p.s2;
            tim = -p.s1;

            if (nxt[id] <= n && b[id] == b[nxt[id]]) {
                a[nxt[id]] += tim;
                pq.push({-a[nxt[id]], nxt[id]});
            }

            if (prv[id] && nxt[id] <= n && b[prv[id]] == b[nxt[id]]) {
                del.push({-a[nxt[id]], nxt[id]});
                a[nxt[id]] -= tim;
            }

            prv[nxt[id]] = prv[id];
            nxt[prv[id]] = nxt[id];

            while (lst < nxt[0])
                ans[lst++] = tim;
        }

        for (int i = 1; i <= n; ++i)
            printf("%lld ", ans[i]);

        putchar(10);
    }

    return 0;
}

//4
//4
//2 0
//1 1
//3 0
//5 1
//6
//4 6
//1 3
//4 6
//4 0
//7 6
//6 3
//7
//9 0
//7 1
//5 0
//7 1
//9 0
//1 1
//2 0
//10
//10 7
//4 9
//2 2
//7 9
//2 8
//8 5
//11 7
//15 5
//12 7
//4 0
