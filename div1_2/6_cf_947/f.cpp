#include<bits/stdc++.h>

using namespace std;

const int N = 24, S = (1 << 20) + 5;
int n = 0, f[N][S] = {};
vector<int> ans;

inline void dfs(int s = 0, int i = 0){
    if(i < n){
        int m = 1 << (n - i - 1);
        for(int t = 0 ; t < m ; t ++) f[i + 1][t] = f[i][t] & f[i][m | t];
        dfs(s << 1, i + 1);
        for(int t = 0 ; t < m ; t ++) f[i + 1][t] = f[i][t] & (f[i][m | t] >> 1);
        dfs(s << 1 | 1, i + 1);
    }
    else if(f[n][0] & 1) ans.push_back(s);
}

int main(){
    scanf("%d", &n);
    f[0][0] = 1;
    for(int s = 1 ; s < 1 << n ; s ++) scanf("%d", &f[0][s]);
    dfs();
    printf("%d\n", int(ans.size()));
    for(int s : ans) printf("%d\n", s);
    return 0;
}

//3
//15 15 15 15 15 15 12
