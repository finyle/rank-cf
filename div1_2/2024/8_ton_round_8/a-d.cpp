#include <iostream>
using namespace std;
int main(){
    int t; cin >> t;
    while(t--){
        int n, k; cin >> n >> k;
        if(k == 1) for(int i = 0; i < n; i++) cout << i + 1 << " ";
        else if(k == n) for(int i = 0; i < n; i++) cout << 1 << " ";
        else cout << -1;
        cout << "\n";
    }
}

// ***********************************

void solve(){
    int n; cin >> n;
    vector<int> a(n);
    for(int& i: a) cin >> i;
    vector<int> p(n), has(n + 1);
    int mex = 0;
    for(int i = 0; i < n; i++){
        if(a[i] >= 0){
            p[i] = mex;
        }
        else{
            p[i] = mex - a[i];
        }
        has[p[i]] = true;
        while(has[mex]) mex++;
    }
    for(int i: p) cout << i << " ";
    cout << "\n";
}

int main(){
    cin.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
}

// ***************************************

void solve(){
    int n, x, y; cin >> n >> x >> y;
    int initial_y = y;
    vector<int> chosen(x);
    for(int& i: chosen) cin >> i;
    sort(chosen.begin(), chosen.end());
    int ans = x - 2;
    int triangles_from_even_g = 0;
    vector<int> odd_g;
    auto process_gap = [&](int g) -> void{
        if(g <= 1){
            // already two apart
            ans += g;
        }
        else if(g % 2 == 1){
            odd_g.push_back(g / 2);
        }
        else{
            triangles_from_even_g += g / 2;
        }
    };
    for(int i = 0; i < x - 1; i++){
        process_gap(chosen[i + 1] - chosen[i] - 1);
    }
    process_gap((chosen[0] + n) - chosen[x - 1] - 1);
    sort(odd_g.begin(), odd_g.end());
    for(int g: odd_g){
        if(y >= g){
            // all vertices are good, so we can make g + 1 triangles
            ans += g + 1;
            y -= g;
        }
        else{
            ans += y;
            y = 0;
            break;
        }
    }
    int even_triangles = min(triangles_from_even_g, y);
    y -= even_triangles;
    ans += even_triangles;
    int used_vertices = initial_y - y;
    ans += used_vertices;
    cout << ans << "\n";
}

int main(){
    cin.tie(0) -> sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--) solve();
}

// **************************************************************
void solve(){
    int n, k;
    cin >> n >> k;

    int A[n + 1][n + 1];

    for (int i = 1; i <= n; i++)
        for (int j = i; j <= n; j++)
            cin >> A[i][j];

    // dp[i] = Answer if we consider 1...i
    vector<int> dp[n + 1];
    dp[0] = {0};

    for (int i = 1; i <= n; i++){
        priority_queue<array<int, 3>> pq;

        // Don't create an interval
        pq.push({dp[i - 1][0], i - 1, 0});

        // Create interval j+2...i (transition from j)
        for (int j = i - 2; j >= -1; j--){
            pq.push({(j < 0 ? 0 : dp[j][0]) + A[j + 2][i], j, 0});
        }

        while (pq.size() and dp[i].size() < k){
            auto [val, j, num] = pq.top(); pq.pop();
            dp[i].push_back(val);

            if (j < 0 or num + 1 >= dp[j].size())
                continue;

            // Don't create interval
            if (j == i - 1)
                pq.push({dp[i - 1][num + 1], i - 1, num + 1});

                // Create interval j+2...i (transition from j)
            else
                pq.push({dp[j][num + 1] + A[j + 2][i], j, num + 1});
        }
    }
    for (int i : dp[n])
        cout << i << " ";
    cout << "\n";
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int tc;
    cin >> tc;

    while (tc--)
        solve();
}