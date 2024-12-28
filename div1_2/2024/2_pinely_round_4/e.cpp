#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1e4 + 5;
int n, m, color[MAX_N], isBipartite;
vector<int> graph[MAX_N];
void dfs(int vertex) {
    for (auto neighbor: graph[vertex])
        if (!color[neighbor]) {
            color[neighbor] = 3 — color[vertex];
            dfs(neighbor);
        } else if (color[neighbor] + color[vertex] != 3)
            isBipartite = 0;
}
void solve() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        graph[i].clear();
        color[i] = 0;
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    isBipartite = 1;
    color[1] = 1;
    dfs(1);
    if (!isBipartite) {
        cout << "Alice" << endl;
        for (int i = 1; i <= n; i++) {
            cout << 1 << ' ' << 2 << endl;
            int vertex, chosenColor;
            cin >> vertex >> chosenColor;
        }
    } else {
        cout << "Bob" << endl;
        vector<int> part1, part2;
        for (int i = 1; i <= n; i++)
            if (color[i] == 1)
                part1.push_back(i);
            else
                part2.push_back(i);
        for (int i = 1; i <= n; i++) {
            int color1, color2;
            cin >> color1 >> color2;
            if ((color1 == 1 || color2 == 1) && part1.size()) {
                cout << part1.back() << ' ' << 1 << endl;
                part1.pop_back();
            } else if ((color1 == 2 || color2 == 2) && part2.size()) {
                cout << part2.back() << ' ' << 2 << endl;
                part2.pop_back();
            } else if (!part1.size()) {
                int chosenColor = (color1 == 1 ? color2 : color1);
                cout << part2.back() << ' ' << chosenColor << endl;
                part2.pop_back();
            } else {
                int chosenColor = (color1 == 2 ? color2 : color1);
                cout << part1.back() << ' ' << chosenColor << endl;
                part1.pop_back();
            }
        }
    }
}
int main() {
    int t;
    cin >> t;
    while (t--)
        solve();
}