#include <bits/stdc++.h>

using namespace std;

const int N = 5000 + 8;

int n, ans[N];
vector<int> G[N];

void bfs(int u) {
    static int q[N], dis[N];
    memset(dis, -1, sizeof dis);
    q[1] = u, dis[u] = 0;
    for (int l = 1, r = 2; l < r; l++) {
        u = q[l];
        for (int v : G[u]) if (dis[v] < 0)
                dis[v] = dis[u] + 1, q[r++] = v;
    }
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += dis[q[i]];
        ans[i] = max(ans[i], (n - 1) * i - sum * 2);
    }
}
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v, u--, v--;
        G[u].push_back(v), G[v].push_back(u);
    }
    for (int i = 0; i < n; i++) bfs(i);
    for (int i = 0; i <= n; i++)
        cout << ans[i] << ' ';
}

//4
//1 2
//3 2
//2 4
