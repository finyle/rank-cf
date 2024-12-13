#include <bits/stdc++.h>

#define debug(...) fprintf(stderr ,__VA_ARGS__)
#define LL long long

const int MX = 3e3 + 5;

bool vis[MX];
LL w[MX][MX] ,dis[MX];

std::vector<int> e[MX];

int size[MX];
void dfs(int x ,int f){
    size[x] = 1;
    for(auto i : e[x]){
        if(i == f) continue;
        dfs(i ,x);
        size[x] += size[i];
    }
    for(auto i : e[x]){
        if(i == f) continue;
        printf("%d %d %lld\n" ,x ,i ,(w[1][x] - w[1][i]) / size[i]);
    }
}

int main(){
    int n; scanf("%d" ,&n);
    memset(w ,-0x3f ,sizeof w);
    for(int i = 1 ; i <= n ; ++i){
        for(int j = 1 ; j <= i ; ++j){
            scanf("%lld" ,&w[i][j]);
            w[j][i] = w[i][j];
        }
    }
    memset(dis ,-0x3f ,sizeof dis);
    dis[1] = 0;
    for(int i = 1 ; i <= n ; ++i){
        int x = 0;
        for(int j = 1 ; j <= n ; ++j){
            if(!vis[j] && (!x || dis[j] > dis[x])){
                x = j;
            }
        }
        //debug("x = %d " ,x);
        //ans += dis[x];
        if(i != 1) for(int j = 1 ; j <= n ; ++j){
                if(w[j][x] == dis[x] && vis[j]){
                    e[x].push_back(j);
                    e[j].push_back(x);
                    //debug("%d %d\n" ,x ,j);
                }
            }
        vis[x] = true;
        for(int j = 1 ; j <= n ; ++j){
            dis[j] = std::max(dis[j] ,w[x][j]);
        }
    }
    //return 0;
    dfs(1 ,1);
    return 0;
}

//3
//7
//3 5
//0 2 8
