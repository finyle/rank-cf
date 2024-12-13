#include<bits/stdc++.h>
using namespace std;
int vis[200005];
int n , m;
vector<int> E[200005];
int a[200005];
int T = 1;
bool span(int u)
{
    set<pair<int,int> > st;
    st.insert(pair<int,int>{a[u] , u});
    int amt = 0 , df = 0;
    while(st.size()) {
        auto pa = (*st.begin()) ; vis[pa.second] = u;
        if(pa.first > df) {return (amt == n);}
        st.erase(st.begin());
        amt++ ; df++ ;
        for(auto v : E[pa.second]) {
            if(vis[v] < u) {
                st.insert(pair<int,int>{a[v] , v});
            }
        }
    }
    return (amt == n);
}
void solve()
{
    scanf("%d%d",&n,&m);
    for(int i= 1;i <= n;i++) scanf("%d",&a[i]) , vis[i] = 0, E[i].clear();
    for(int i = 1;i <= m;i++) {
        int u,v;scanf("%d%d",&u,&v);E[u].push_back(v) ; E[v].push_back(u);
    }
    for(int i = 1;i <= n;i++) {
        if(a[i] == 0 && !vis[i]) {
            if(span(i)){puts("YES");return;}
        }
    }
    puts("NO");
}
int main()
{
    int t;scanf("%d",&t);
    while(t--) solve();
}