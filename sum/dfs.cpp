#include <bits/stdc++.h>
#define ll long long
#define ld long double

using namespace std;

// tedukuri
// 枚举： 组合， 指数， 排列
struct enum_combination {
    int n, m;
    vector<int> chosen;
    void calc(int x) {
        if (chosen.size() > m || chosen.size() + (n - x + 1) < m) return;
        if (x == n + 1) {
            for(int i = 0; i < chosen.size(); i++) {
                printf("%d ", chosen[i]);
            }
            puts("");
            return;
        }
        chosen.push_back(x);
        calc(x + 1);
        chosen.pop_back();
        calc(x + 1);
    }
    int main() {
        cin >> n >> m;
        calc(1);
    }
};

struct enum_exponotial {
    int n;
    vector<int> chosen;
    void calc(int x) {
        if (x == n + 1) {
            for(int i = 0; i < chosen.size(); i++)
                printf("%d ", chosen[i]);
            puts("");
            return;
        }
        calc(x + 1);
        chosen.push_back(x);
        calc(x + 1);
        chosen.pop_back();
    }
    int main() {
        cin >> n;
        calc(1);
    }
};

// struct no work, 变量定义作用域
struct enum_permute {
    int n;
    int order[20]; // 按顺序依次记录被选择的整数
    bool chosen[20]; // 标记被选择的整数
    void calc(int k) {
        if (k == n + 1) { // 问题边界
            for (int i = 1; i <= n; i++)
                printf("%d ", order[i]);
            puts("");
            return;
        }
        for (int i = 1; i <= n; i++) {
            if (chosen[i]) continue;
            order[k] = i;
            chosen[i] = 1;
            calc(k + 1);
            chosen[i] = 0;
            order[k] = 0; // 这一行可以省略
        }
    }
    int main() {
        cin >> n;
        calc(1);  // 主函数中的调用入口
    }
};

// fractal
struct fractal_streets {
    pair<ll, ll> calc(int n, ll m) {
        if (n == 0) return make_pair(0, 0);
        ll len = 1ll << (n - 1), cnt = 1ll << (2 * n - 2);
        pair<ll, ll> pos = calc(n - 1, m % cnt); // 递归
        ll x = pos.first, y = pos.second;
        ll z = m / cnt;
        if (z == 0) return make_pair(y, x);
        if (z == 1) return make_pair(x, y + len);
        if (z == 2) return make_pair(x + len, y + len);
        if (z == 3) return make_pair(2 * len - y - 1, len - x - 1);
    }

    int main () {
        int data; for (scanf("%d", &data); data; --data) {
            int n; ll h, o;
            scanf("%d %I64d %I64d", &n, &h, &o);
            pair<ll, ll> hp = calc(n, h - 1);
            pair<ll, ll> op = calc(n, o - 1);
            ll dx = hp.first - op.first, dy = hp.second - op.second;
            printf("%.0f\n", (double)sqrt(dx * dx + dy * dy) * 10);
        }
        return 0;
    }
};

// sumdiv
// 50000000 50000000
struct sumdiv {
    const ll P = 9901;
    vector<pair<ll, ll> > w;

    ll ksm(ll a, ll b) {
        ll ans = 1;
        a %= P;
        while (b) {
            if (b & 1) (ans *= a) %= P;
            (a *= a) %= P;
            b >>= 1;
        }
        return ans;
    }

    ll get_sum(ll p, ll c) {
        if (!p) return 0;
        if (!c) return 1;
        if (c & 1) return (ksm(p, (c + 1) / 2) + 1) * get_sum(p, c / 2) % P;
        return ((ksm(p, c / 2) + 1) * get_sum(p, c / 2 - 1) + ksm(p, c)) % P;
    }

    void fj(ll a) {
        for (ll i = 2; i * i <= a; i++)
            if (!(a % i)) {
                ll num = 0;
                while (!(a % i)) {
                    num++;
                    a /= i;
                }
                w.push_back(make_pair(i, num));
            }
        if (a != 1) w.push_back(make_pair(a, 1));
    }

    int main() {
        ll a, b;
        cin >> a >> b;
        fj(a);
        ll ans = 1;
        for (unsigned ll i = 0; i < w.size(); i++) {
            ll p = w[i].first, c = w[i].second;
            (ans *= get_sum(p, b * c)) %= P;
        }
        cout << ans << endl;
        return 0;
    }
};
// pac base
// fractal, raid
struct fractal {
    const int N = 730;
    int n, p[7];
    bool a[730][730];

    void Fractal(int k, int x, int y) {
        if (!k) {
            a[x][y] = 1;
            return;
        }
        Fractal(k - 1, x, y);
        Fractal(k - 1, x, y + 2 * p[k-1]);
        Fractal(k - 1, x + p[k-1], y + p[k-1]);
        Fractal(k - 1, x + 2 * p[k-1], y);
        Fractal(k - 1, x + 2 * p[k-1], y + 2 * p[k-1]);
    }

    void Fractal() {
        n--;
        Fractal(n, 1, 1);
        for (int i = 1; i <= p[n]; i++) {
            for (int j = 1; j <= p[n]; j++)
                putchar(a[i][j] ? 'X' : ' ');
            printf("\n");
        }
        printf("-\n");
        for (int i = 1; i <= p[n]; i++)
            for (int j = 1; j <= p[n]; j++)
                a[i][j] = 0;
    }

    int main() {
        p[0] = 1;
        for (int i = 1; i < 7; i++) p[i] = p[i-1] * 3;
        while (scanf("%d", &n) == 1 && n != -1) Fractal();
        return 0;
    }
};

struct raid {
    const int N = 100006;
    const double INF = 0x3f3f3f3f, eps = 0.000001;
    struct P {
        int x, y;
        bool z;

        bool operator<(const P w) const {
            return x < w.x;
        }
    } p[100006];
    int n;

    double s(P x, P y) {
        if (x.z == y.z) return INF;
        return sqrt((ld)(x.x - y.x) * (x.x - y.x) + (ld)(x.y - y.y) * (x.y - y.y));
    }

    double s(int l, int r) {
        if (l == r) return INF;
        if (l + 1 == r) return s(p[l], p[r]);
        int mid = (l + r) >> 1;
        double ans = min(s(l, mid), s(mid, r));
        for (int i = mid - 1; i >= l; i--) {
            if (p[mid].x - p[i].x + eps > ans) break;
            for (int j = mid + 1; j <= r; j++) {
                if (p[j].x - p[i].x + eps > ans) break;
                ans = min(ans, s(p[i], p[j]));
            }
        }
        return ans;
    }

    void Raid() {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            scanf("%d %d", &p[i].x, &p[i].y);
            p[i].z = 0;
        }
        for (int i = 1; i <= n; i++) {
            scanf("%d %d", &p[i+n].x, &p[i+n].y);
            p[i+n].z = 1;
        }
        sort(p + 1, p + 2 * n + 1);
        printf("%.3f\n", s(1, 2 * n));
    }

    int main() {
        int t;
        cin >> t;
        while (t--) Raid();
        return 0;
    }

};

// dp treeDP

struct treeDP_dance {
    vector<int> son[10010];
    int f[10010][2], v[10010], h[10010], n;

    void dp(int x) {
        f[x][0] = 0;
        f[x][1] = h[x];
        for (int i = 0; i < son[x].size(); i++) {
            int y = son[x][i];
            dp(y);
            f[x][0] += max(f[y][0], f[y][1]);
            f[x][1] += f[y][0];
        }
    }
//    7
//    1
//    1
//    1
//    1
//    1
//    1
//    1
//    1 3
//    2 3
//    6 4
//    7 4
//    4 5
//    3 5
//    0 0
    int main() {
        cin >> n;
        for (int i = 1; i <= n; i++) scanf("%d", &h[i]);
        for (int i = 1; i < n; i++) {
            int x, y;
            scanf("%d %d", &x, &y);
            v[x] = 1; // x has a father
            son[y].push_back(x); // x is a son of y
        }
        int root;
        for (int i = 1; i <= n; i++)
            if (!v[i]) { // i doesn't have a father
                root = i;
                break;
            }
        dp(root);
        cout << max(f[root][0], f[root][1]) << endl;
    }
};

// datastruct trie heap uf segment
struct trie_xor_longest {
//    const int N = 100006;
#define N 1000006
    int n, d[N], trie[N*33][2], tot;
    vector<pair<int, int> > e[N];
    int Head[N], Edge[N*2], Leng[N*2], Next[N*2], num;
    bool v[N];

    void dfs(int x) {
        for (int i = Head[x]; i; i = Next[i]) {
            int y = Edge[i], z = Leng[i];
            if (v[y]) continue;
            v[y] = 1;
            d[y] = d[x] ^ z;
            dfs(y);
        }
    }

    void add(int x, int y, int z) {
        Edge[++tot] = y;
        Leng[tot] = z;
        Next[tot] = Head[x];
        Head[x] = tot;
    }

    void The_xor_longest_Path() {
        memset(d, 0, sizeof(d));
        memset(trie, 0, sizeof(trie));
        memset(v, 0, sizeof(v));
        memset(Head, 0, sizeof(Head));
        num = 0;
        v[0] = 1;
        tot = 1;
        for (int i = 1; i < n; i++) {
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            add(u, v, w);
            add(v, u, w);
        }
        dfs(0);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int p = 1;
            for (int j = 31; j >= 0; j--) {
                int k = (d[i] >> j) & 1;
                if (!trie[p][k]) trie[p][k] = ++tot;
                p = trie[p][k];
            }
            p = 1;
            if (i) {
                int w = 0;
                for (int j = 31; j >= 0; j--) {
                    int k = (d[i] >> j) & 1;
                    if (trie[p][k^1]) {
                        w = (w << 1) + (k ^ 1);
                        p = trie[p][k^1];
                    } else {
                        w = (w << 1) + k;
                        p = trie[p][k];
                    }
                }
                ans = max(ans, w ^ d[i]);
            }
        }
        cout << ans << endl;
    }

    int main() {
        while (cin >> n) The_xor_longest_Path();
        return 0;
    }
};

struct uf_game {
    struct { int l, r, ans; } query[10010];
    int a[20010], fa[20010], d[20010], n, m, t;
    void read_discrete() { // 读入、离散化
        cin >> n >> m;
        for (int i = 1; i <= m; i++) {
            char str[5];
            scanf("%d%d%s", &query[i].l, &query[i].r, str);
            query[i].ans = (str[0] == 'o' ? 1 : 0);
            a[++t] = query[i].l - 1;
            a[++t] = query[i].r;
        }
        sort(a + 1, a + t + 1);
        n = unique(a + 1, a + t + 1) - a - 1;
    }
    int get(int x) {
        if (x == fa[x]) return x;
        int root = get(fa[x]);
        d[x] ^= d[fa[x]];
        return fa[x] = root;
    }
    int main() {
        read_discrete();
        for (int i = 1; i <= n; i++) fa[i] = i;
        for (int i = 1; i <= m; i++) {
            // 求出l-1和r离散化之后的值
            int x = lower_bound(a + 1, a + n + 1, query[i].l - 1) - a;
            int y = lower_bound(a + 1, a + n + 1, query[i].r) - a;
            // 执行get函数，得到树根，并进行路径压缩
            int p = get(x), q = get(y);
            if (p == q) { // 已经在同一集合内
                if ((d[x] ^ d[y]) != query[i].ans) { // 矛盾，输出
                    cout << i - 1 << endl;
                    return 0;
                }
            }
            else { // 不在同一集合，合并
                fa[p] = q;
                d[p] = d[x] ^ d[y] ^ query[i].ans;
            }
        }
        cout << m << endl; // 没有矛盾
    }
};

struct seg_integer_pro {
    static const int SIZE=100010;
    struct SegmentTree{
        int l,r;
        long long sum,add;
#define l(x) tree[x].l
#define r(x) tree[x].r
#define sum(x) tree[x].sum
#define add(x) tree[x].add
    }tree[SIZE*4];
    int a[SIZE],n,m;

    void build(int p,int l,int r)//No.p, [l,r]
    {
        l(p)=l,r(p)=r;
        if(l==r) { sum(p)=a[l]; return; }
        int mid=(l+r)/2;
        build(p*2,l,mid);
        build(p*2+1,mid+1,r);
        sum(p)=sum(p*2)+sum(p*2+1);
    }

    void spread(int p)
    {
        if(add(p))
        {
            sum(p*2)+=add(p)*(r(p*2)-l(p*2)+1);
            sum(p*2+1)+=add(p)*(r(p*2+1)-l(p*2+1)+1);
            add(p*2)+=add(p);
            add(p*2+1)+=add(p);
            add(p)=0;
        }
    }

    void change(int p,int l,int r,int z)
    {
        if(l<=l(p)&&r>=r(p))
        {
            sum(p)+=(long long)z*(r(p)-l(p)+1);
            add(p)+=z;
            return;
        }
        spread(p);
        int mid=(l(p)+r(p))/2;
        if(l<=mid) change(p*2,l,r,z);
        if(r>mid) change(p*2+1,l,r,z);
        sum(p)=sum(p*2)+sum(p*2+1);
    }

    long long ask(int p,int l,int r)
    {
        if(l<=l(p)&&r>=r(p)) return sum(p);
        spread(p);
        int mid=(l(p)+r(p))/2;
        long long ans=0;
        if(l<=mid) ans+=ask(p*2,l,r);
        if(r>mid) ans+=ask(p*2+1,l,r);
        return ans;
    }

    int main()
    {
        cin>>n>>m;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        build(1,1,n);
        while(m--)
        {
            char op[2]; int x,y,z;
            scanf("%s%d%d",op,&x,&y);
            if(op[0]=='C')
            {
                scanf("%d",&z);
                change(1,x,y,z);
            }
            else printf("%I64d\n",ask(1,x,y));
        }
    }
};

// search dfs, sudoku, climb | purge: stick, sudoku, cake | ida: chain, gift
struct dfs_sukoku {
    char str[10][10];
    int row[9], col[9], grid[9], cnt[512], num[512], tot;

    inline int g(int x, int y) {
        return ((x / 3) * 3) + (y / 3);
    }

    inline void flip(int x, int y, int z) {
        row[x] ^= 1 << z;
        col[y] ^= 1 << z;
        grid[g(x, y)] ^= 1 << z;
    }

    bool dfs(int now) {
        if (now == 0) return 1;
        int temp = 10, x, y;
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++) {
                if (str[i][j] != '.') continue;
                int val = row[i] & col[j] & grid[g(i, j)];
                if (!val) return 0;
                if (cnt[val] < temp) {
                    temp = cnt[val];
                    x = i, y = j;
                }
            }
        int val = row[x] & col[y] & grid[g(x, y)];
        for (; val; val -= val&-val) {
            int z = num[val&-val];
            str[x][y] = '1' + z;
            flip(x, y, z);
            if (dfs(now - 1)) return 1;
            flip(x, y, z);
            str[x][y] = '.';
        }
        return 0;
    }

    int main() {
        for (int i = 0; i < 1 << 9; i++)
            for (int j = i; j; j -= j&-j) cnt[i]++;
        for (int i = 0; i < 9; i++)
            num[1 << i] = i;
        char s[100];
        while (~scanf("%s", s) && s[0] != 'e') {
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 9; j++) str[i][j] = s[i * 9 + j];
            for (int i = 0; i < 9; i++) row[i] = col[i] = grid[i] = (1 << 9) - 1;
            tot = 0;
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 9; j++)
                    if (str[i][j] != '.') flip(i, j, str[i][j] - '1');
                    else tot++;
            dfs(tot);
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 9; j++) s[i * 9 + j] = str[i][j];
            puts(s);
        }
    }

};

struct dfs_climb {
    int c[20], cab[20], n, w, ans;
    void dfs(int now, int cnt) {
        if (cnt >= ans) return;
        if (now == n+1) {
            ans = min(ans, cnt);
            return;
        }
        for (int i = 1; i <= cnt; i++) {  // 分配到已租用缆车
            if (cab[i] + c[now] <= w) {   // 能装下
                cab[i] += c[now];
                dfs(now+1, cnt);
                cab[i] -= c[now];         // 还原现场
            }
        }
        cab[cnt+1] = c[now];
        dfs(now+1, cnt+1);
        cab[cnt+1] = 0;
    }
    int main() {
        cin >> n >> w;
        for (int i = 1; i <= n; i++) cin >> c[i];
        sort(c + 1, c + n + 1);
        reverse(c + 1, c + n + 1);
        ans = n;    // 最多用n辆缆车，每只猫一辆
        dfs(1, 0);  // 搜索入口
        cout << ans << endl;
    }
};
//4 10
//5
//6
//3
//7

// graph, lca | base circle | tarjan | 2-part




int main() {
//    enum_combination ec;
//    ec.main();

//    enum_exponotial ee;
//    ee.main();

//    enum_permute ep;
//    ep.main();

//    sumdiv sd;
//    sd.main();

//    fractal_streets fs;
//    fs.main();

//    fractal f;
//    f.main();

//    raid r;
//    r.main();

//    trie_xor_longest t;
//    t.main();

//    uf_game ug;
//    ug.main();

//    dfs_sukoku ds;
//    ds.main();

//    dfs_climb dc;
//    dc.main();

    treeDP_dance td;
    td.main();

//    printf("hi");
    return 0;
}