#include <bits/stdc++.h>

#define debug(...) fprintf(stderr ,__VA_ARGS__)
#define LL long long
const int MX = 2e5 + 5;

int n ,s;
struct Goat{
    int x ,y ,id;
}A[MX];

bool cmp(Goat a ,Goat b){
    return a.x < b.x;
}

int mx[MX];
int calc(int id){
    if(id == 1) return A[id].x;
    int far = std::max(calc(id - 1) ,mx[id - 2]);
    return std::max(std::min(far ,A[id].x) + A[id].y ,A[id].x);
}

int ans[MX];
void solve(){
    scanf("%d%d" ,&n ,&s);
    for(int i = 1 ,x ,y ; i <= n ; ++i){
        scanf("%d%d" ,&x ,&y);
        A[i] = (Goat){x ,y ,i};
        ans[i] = false;
    }
    std::sort(A + 1 ,A + 1 + n ,cmp);
    for(int i = 1 ; i <= n ; ++i){
        mx[i] = std::max(A[i].x + A[i].y ,mx[i - 1]);
    }
    for(int i = 1 ; i < n ; ++i){
        if(A[i].x + A[i].y >= s){
            ans[A[i].id] = true;
        }
    }
    if(calc(n) >= s) ans[A[n].id] = true;
    puts(ans[1] ? "YES" : "NO");
}

int main(){
    int t; scanf("%d" ,&t);
    while(t--) solve();
    return 0;
}

//6
//4 16
//5 3
//8 12
//10 7
//15 1
//4 16
//8 12
//10 7
//15 1
//5 3
//4 16
//10 7
//15 1
//5 3
//8 12
//4 16
//15 1
//5 3
//8 12
//10 7
//1 1000000000
//500000000 500000000
//2 1000000000
//1 999999999
//1 1
