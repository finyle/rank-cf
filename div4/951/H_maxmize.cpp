#include <bits/stdc++.h>

//6
//1 1
//.
//4 2
//..
//#.
//#.
//.#
//3 5
//.#.#.
//..#..
//.#.#.
//5 5
//#...#
//....#
//#...#
//.....
//...##
//6 6
//.#..#.
//#..#..
//.#...#
//#.#.#.
//.#.##.
//###..#
//6 8
//..#....#
//.####.#.
//###.#..#
//.##.#.##
//.#.##.##
//#..##.#.

using namespace std;

int n, m, minR, maxR, minC, maxC, sz, ans; vector<int> R, C, freeR, freeC;
vector<vector<int>> RC; vector<vector<bool>> vis; vector<vector<char>> A;

void dfs(int i, int j){
    if (i <= 0 or i > n or j <= 0 or j > m or vis[i][j] or A[i][j] == '.')
        return;

    vis[i][j] = true;

    sz++;
    minR = min(minR, i);
    maxR = max(maxR, i);
    minC = min(minC, j);
    maxC = max(maxC, j);

    dfs(i - 1, j);
    dfs(i + 1, j);
    dfs(i, j - 1);
    dfs(i, j + 1);
}

void solve(){
    cin >> n >> m;

    R.assign(n + 5, 0);
    C.assign(m + 5, 0);
    freeR.assign(n + 5, 0);
    freeC.assign(m + 5, 0);
    RC.assign(n + 5, vector<int>(m + 5, 0));
    vis.assign(n + 5, vector<bool>(m + 5, false));
    A.assign(n + 5, vector<char>(m + 5, ' '));

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            cin >> A[i][j];

            if (A[i][j] == '.'){
                freeR[i]++;
                freeC[j]++;
            }
        }
    }

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            if (vis[i][j] or A[i][j] == '.')
                continue;

            // Reset
            sz = 0;
            minR = 1e9;
            maxR = -1e9;
            minC = 1e9;
            maxC = -1e9;

            dfs(i, j);

            // Expand by 1 since adjacent cells also connect
            minR = max(minR - 1, 1);
            maxR = min(maxR + 1, n);
            minC = max(minC - 1, 1);
            maxC = min(maxC + 1, m);

            // Update prefix sums
            R[minR] += sz;
            R[maxR + 1] -= sz;

            C[minC] += sz;
            C[maxC + 1] -= sz;

            RC[minR][minC] += sz;
            RC[maxR + 1][minC] -= sz;
            RC[minR][maxC + 1] -= sz;
            RC[maxR + 1][maxC + 1] += sz;
        }
    }

    for (int i = 1; i <= n; i++)
        R[i] += R[i - 1];

    for (int i = 1; i <= m; i++)
        C[i] += C[i - 1];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            RC[i][j] += RC[i - 1][j] + RC[i][j - 1] - RC[i - 1][j - 1];

    ans = 0;

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            ans = max(ans, (R[i] + C[j] - RC[i][j]) + (freeR[i] + freeC[j] - (A[i][j] == '.')));

    cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;

    while (tc--)
        solve();
}