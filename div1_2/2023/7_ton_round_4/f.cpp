#include <bits/stdc++.h>

using namespace std;
int n , m , q;
const int N = 2e5 + 40;
int num[N];
int a[N];
int cov[N*4 + 5] , mx[N*4 + 5] , mn[N*4 + 5];
void rec(int u)
{
    mx[u] = max(mx[u<<1|1] , mx[u<<1]) ; mn[u] = min(mn[u<<1|1] , mn[u<<1]);
}
void pd(int u)
{
    if(cov[u] != -1) {
        cov[u<<1] = mn[u<<1] = mx[u<<1] = cov[u];
        cov[u<<1|1] = mn[u<<1|1] = mx[u<<1|1] = cov[u];
        cov[u] = -1;
    }
    return;
}
void build(int u,int l,int r)
{
    cov[u] = -1;
    if(l == r) {mn[u] = mx[u] = num[l] ; return;}
    build(u<<1 , l , (l + r >> 1)) ; build(u<<1|1 , (l + r >> 1) + 1 , r);
    rec(u) ; return;
}
void modify(int u,int l,int r,int ql,int qr,int v)
{
    if(ql <= l && qr >= r) {
        cov[u] = mn[u] = mx[u] = v; return;
    }
    pd(u);
    int md = (l + r>> 1);
    if(ql <= md) modify(u<<1 , l , md , ql , qr ,v);
    if(qr > md) modify(u<<1|1 , md +1 , r , ql , qr , v);
    rec(u);
    return;
}

int qumax(int u,int l,int r,int ql)
{
    if(mn[u] == m - 1) return -1;
    if(l == r) return l;
    pd(u);
    int md = (l + r>> 1);
    if(ql > md) return qumax(u<<1|1 , md + 1 , r , ql);
    if(ql == l) {
        if(mn[u<<1] < m - 1) return qumax(u<<1 , l , md , ql);
        return qumax(u<<1|1 , md + 1 , r , md + 1);
    }
    int w = qumax(u<<1 , l , md , ql) ;
    if(w == -1) return qumax(u<<1|1 , md + 1 , r , md + 1);
    return w;
}
int qumin(int u,int l,int r,int ql)
{
    if(mx[u] == 0) return -1;
    if(l == r) return l;
    pd(u);
    int md = (l + r>> 1) ;
    if(ql > md) return qumin(u<<1|1 , md + 1 , r , ql);
    if(ql == l) {
        if(mx[u<<1] > 0) return qumin(u<<1 , l , md , ql);
        return qumin(u<<1|1 , md + 1 , r , md + 1);
    }
    int w = qumin(u<<1 , l , md , ql);
    if(w == -1) return qumin(u<<1|1 , md + 1 , r , md + 1);
    return w;
}

int qmax(int u,int l,int r,int ql,int qr)
{
    if(ql <= l && qr >= r) {
        return mx[u];
    }
    pd(u);
    int md = (l + r>> 1) , ans = 0;
    if(ql <= md) ans = max(ans , qmax(u<<1 , l , md , ql , qr ));
    if(qr > md) ans = max(ans , qmax(u<<1|1 , md +1 , r , ql , qr));
    return ans;
}
int qmin(int u,int l,int r,int ql,int qr)
{
    if(ql <= l && qr >= r) {
        return mn[u];
    }
    pd(u);
    int md = (l + r>> 1) , ans = 1e9;
    if(ql <= md) ans = min(ans , qmin(u<<1 , l , md , ql , qr ));
    if(qr > md) ans = min(ans , qmin(u<<1|1 , md +1 , r , ql , qr));
    return ans;
}
int ask(int u,int l,int r)
{
    if(l == r) return l;
    int md = (l + r >> 1);
    pd(u);
    if(mx[u<<1|1] == 0) return ask(u<<1 , l , md);
    return ask(u<<1|1 , md + 1 , r) ;
}
int get()
{
    int highbit = ask(1 , 1 , n+35);
    if(highbit == 1 || qmax(1 , 1 , n+35 , 1 , highbit - 1) == 0) return highbit;
    return highbit + 1;
}
void add(int u)
{
    int l = qumax(1 , 1 , n + 35 , u);
    if(l > u) modify(1 , 1 , n+35 , u , l - 1 , 0) ;
    modify(1 , 1 , n+35 , l , l , qmax(1 , 1 , n + 35 , l , l ) + 1);
    return;
}
void sub(int u)
{
    int l = qumin(1 , 1 , n + 35 , u);
    if(l > u) modify(1 , 1 , n+35 , u , l - 1 , m - 1) ;
    modify(1 , 1 , n+35 , l , l , qmax(1 , 1 , n + 35 , l , l ) - 1);
    return;
}
void solve()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i = 1;i <= n + 35;i++) num[i] = 0;
    for(int i = 1;i <= n;i++) {
        scanf("%d",&a[i]);num[a[i]]++;
    }
    for(int i = 1;i <= n + 35;i++) {
        num[i + 1] += num[i] / m;num[i] %= m;
    }
    build(1 , 1 , n + 35);
    while(q--) {
        int u , v;scanf("%d%d",&u,&v);
        sub(a[u]) ; a[u] = v; add(a[u]) ;
        printf("%d%c",get(), " \n"[q == 0]);
    }
    return;
}

//3
//5 3 3
//3 3 4 4 5
//1 4
//2 4
//3 5
//5 2 4
//3 3 4 4 5
//1 4
//2 5
//3 5
//4 5
//7 3 4
//1 2 2 3 3 3 4
//1 4
//2 1
//5 5
//6 6

int main()
{
    int t;scanf("%d",&t);
    while(t--) solve();
}