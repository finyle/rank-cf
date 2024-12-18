#include <bits/stdc++.h>

#define ll long long
#define ld long double

using namespace std;

// 指数型枚举 2^k
// 组合行枚举 C(N,M), 在指数型枚举的基础上剪枝，添加额外的退出判定条件
struct exponotial {
    vector<int> arr;
    int n;
    void dfs(int x) {
        if(x==n+1) {for (auto x: arr) cout << x << " "; puts(""); return;}
        dfs(x+1);arr.push_back(x);dfs(x+1);arr.pop_back();
    }
    int main() {
        cin >> n;
        dfs(1);
    }
};

// 排列行枚举: vi判断是否访问过；arr存放访问路径； 结构体内存segmentfault; arr,vi 必须在静态区
struct permute {
    int n;
    bool vi[20];
    int arr[20];
    void dfs(int x) {
        if(x==n+1) {for(int i=1;i<=n;i++) cout << arr[i] << " "; puts(""); return;}
        for(int i=1;i<=n;i++) {
            if (vi[i]) continue;
            vi[i]=1; arr[x] = i;dfs(x+1);vi[i]=0;
        }
    }
    int main() {
        cin >> n;
        dfs(1);
    }
};

// 分形类问题： 多边形嵌套
// 分治问题： sumdiv， raid
// fractal(分形街道), sumdiv(a的b次幂的约数之和, 等比数列求和(快速幂 log(n))),  (raid(平面上的点中相距最近的两个点的距离) for-dfs)mergeSort  int dfs
struct sumdiv { // 等比数列求和(快速幂）
    const ll P = 9901;
    vector<pair<ll, ll>> w;
    ll ksm(ll a, ll b) { // a^b
        ll ans = 1; a%=P;
        while(b) {if(b&1) (ans*=a)%=P; (a*=a)%=P; b>>=1;}
        return ans;
    }
    ll get_sum(ll p, ll c) {
        if(!p) return 0;
        if(!c) return 1;
        if(c&1) return (ksm(p, (c+1)/2)+1)* get_sum(p,c/2)%P;
        return ((ksm(p,c/2)+1)* get_sum(p,c/2-1)+ksm(p,c))%P;
    }
    void fj(ll a) {
        for(ll i=2;i*i<=a;i++)
            if(!(a%i)) {
                ll num = 0;
                while (!(a%i)) num++, a/=i;
                w.push_back(make_pair(i, num));
            }
        if (a!=1) w.push_back(make_pair(a,1));
    }
    int main() {
        ld a, b; cin >> a >> b;
        fj(a);
        ll ans = 1;
        for (unsigned ll i=0;i<w.size();i++) {
            ll p=w[i].first, c=w[i].second;
            (ans *= get_sum(p,b*c))%=P;
        }
        cout << ans << endl; return 0;
    }
};
// 平面上的最近点对
struct raid {
    static const int N = 1e4+6;
    const double INF = 0x3f3f3f3f, eps = 0.000001;
    struct P {
        int x, y; bool z;
        bool operator<(const P w) const {return x < w.x;}
    } p[N];
    double s(P x, P y) {

    }
    double s(int l, int r) {

    }
    void Raid() {
        int n; cin >> n;
        for(int i=1;i<=n;i++) {scanf("%d %d",&p[i].x,&p[i].y); p[i].z=0;}
        for(int i=1;i<=n;i++) {scanf("%d %d",&p[i+n].x,&p[i+n].y);p[i+n].z=1;}
        sort(p+1,p+2*n+1); printf("%.3f\n",s(1,2*n));
    }
    int main() {
        int t; cin >> t;
        while(t--) Raid();
        return 0;
    }
};

struct fractal {
    int dfs() {

    }
};


//
// 数独， n皇后， bool dfs for-dfs
struct sudoku {
    bool dfs() {
    }
};

// ds: trie, heap, uf
struct uf_game {
    struct {int l, r, ans;} query[10000];
    int a[1000], fa[1000], d[1000], n, m, t;
    void read_discrete() {
        cin>>n>>m;
        for(int i=1;i<=m;i++){
            char str[5]; scanf("%d%d%s",&query[i].l,&query[i].r,str);
            query[i].ans=(str[0]=='o'?1:0);
            a[++t]=query[i].l-1; a[++t]=query[i].r;
        }
    }
    int get(int x) {
        if(x==fa[x]) return x;
        int root=get(fa[x]); d[x]^=d[fa[x]]; return fa[x]=root;
    }
    int main() {
        read_discrete();
        for(int i=1;i<=n;i++) fa[i]=i;
        for(int i=1;i<=m;i++) {
            int x=lower_bound(a+1,a+n+1,query[i].l-1)-a;
            int y= lower_bound(a+1,a+n+1,query[i].r)-a;
            int p=get(x), q=get(y);
            if(p==q) {if((d[x]^d[y])!=query[i].ans) {cout<<i-1<<endl;return 0;}}
            else {fa[p]=q; d[p]=d[x]^d[y]^query[i].ans;}
        }
        cout<<m<<endl;
    }

};

// tree dp, void dfs for-dfs
// dance(normal); lesson(背包); accumulation(二次扫描&换根)
struct treeDP_dance {
    vector<int> son[10010];
    int f[10010][2], v[10010], h[10010], n;
    void dfs(int x) {
        f[x][0] = 0;f[x][1] = h[x];
        for (int i = 0; i < son[x].size(); i++) {
            int y = son[x][i];dfs(y);
            f[x][0] += max(f[y][0], f[y][1]);f[x][1] += f[y][0];
        }
    }
    int main() {
        cin >> n;
        for (int i = 1; i <= n; i++) scanf("%d", &h[i]);
        for (int i = 1; i < n; i++) {
            int x, y; scanf("%d %d", &x, &y);
            v[x] = 1; // x has a father
            son[y].push_back(x); // x is a son of y
        }
        int root;
        for (int i = 1; i <= n; i++)
            if (!v[i]) { // i doesn't have a father
                root = i;break;}
        dfs(root);
        cout << max(f[root][0], f[root][1]) << endl;
    }
};
struct treeDP_lesson {
    vector<int> son[310];
    int f[310][310], s[310], n, m;
    void dp(int x) {
        f[x][0] = 0;
        for (int i = 0; i < son[x].size(); i++) { // 循环子节点（物品）
            int y = son[x][i]; dp(y);
            for (int t = m; t >= 0; t--) // 倒序循环当前选课总门数（当前背包体积）
                for (int j = 0; j <= t; j++) // 循环更深子树上的选课门数（组内物品）
                    f[x][t] = max(f[x][t], f[x][t-j] + f[y][j]);
        }
        if (x != 0) // x不为0时，选修x本身需要占用1门课，并获得相应学分
            for(int t = m; t > 0; t--)f[x][t] = f[x][t-1] + s[x];
    }
    int main(){
        cin >> n >> m;
        for(int i = 1; i <= n; i++){
            int x; cin >> x >> s[i];
            son[x].push_back(i);
        }
        memset(f, 0xcf, sizeof(f)); // -INF
        dp(0); cout << f[0][m] << endl;
    }
};
struct treeDP_accumulation {
    int d[2000], v[2000], f[2000], deg[2000];
    int head[2000], ver[4000], edge[4000], Next[4000];
    int n, T, tot, root, ans;
    void add(int x, int y, int z) {ver[++tot] = y, edge[tot] = z, Next[tot] = head[x], head[x] = tot;}
    void dp(int x) {
        v[x] = 1; // 访问标记
        d[x] = 0;
        for (int i = head[x]; i; i = Next[i]) { // 邻接表存储
            int y = ver[i];
            if (v[y]) continue;
            dp(y);
            if (deg[y] == 1) d[x] += edge[i]; // edge[i]保存c(x,y)
            else d[x] += min(d[y], edge[i]);
        }
    }
    void dfs(int x) {
        v[x] = 1;
        for (int i = head[x]; i; i = Next[i]) {
            int y = ver[i];
            if (v[y]) continue;
            if (deg[x] == 1) f[y] = d[y] + edge[i];
            else if (deg[y] == 1) f[y] = d[y] + min(f[x] - edge[i], edge[i]);
            else f[y] = d[y] + min(f[x] - min(d[y], edge[i]), edge[i]);
            dfs(y);
        }
    }
    int main() {
        cin >> T;
        while (T--) {
            tot = 1; cin >> n; tot = 1;
            for (int i = 1; i <= n; i++) head[i] = f[i] = d[i] = deg[i] = v[i] = 0;
            for (int i = 1; i < n; i++) {
                int x, y, z;
                scanf("%d%d%d", &x, &y, &z);
                add(x, y, z), add(y, x, z);
                deg[x]++, deg[y]++;
            }
            int root = 1; // 任选一个点为源点
            dp(root);
            for (int i = 1; i <= n; i++) v[i] = 0;
            f[root] = d[root];
            dfs(root);
            int ans = 0;
            for (int i = 1; i <= n; i++) ans = max(ans, f[i]);
            cout << ans << endl;
        }
    }
};

// 最短路，最小生成树，lca&直径， tarjan， 二分图， 网络流
struct graph {
    void dfs()  {

    }
};

int main() {
    int a = 2e10;
    int b[] = {1,2,3};
    vector<int> c = {3,2,1};
    printf("2e10 is %d\n", a);
    for (auto x: b) printf("b's num is %d\n", x);

    printf("================== \n");

//    exponotial ex;
//    ex.main();

//    permute pe;
//    pe.main();

//    treeDP_dance td;
//    td.main();
//    treeDP_lesson tl;
//    tl.main();
//    treeDP_accumulation ta;
//    ta.main();

    uf_game ug;
    ug.main();
    return 0;

}