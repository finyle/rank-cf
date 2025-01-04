#include <bits/stdc++.h>

using namespace std;

const int MAX = 200007;
const int MOD = 998244353;

struct bignum {
    static constexpr long long B = 1LL<<30;
    static constexpr int N = 6;
    array<long long, N> b = {};
    bignum() {}
    bignum(long long a) {
        b[2] = (a / B) / B;
        b[1] = (a / B) % B;
        b[0] = a % B;
    }
    bignum operator*(const bignum& o) {
        bignum res;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j + i < N; j++) {
                res.b[i + j] += b[i] * o.b[j];
                for (int k = i + j; k + 1 < N; k++) {
                    auto tmp = res.b[k] / B;
                    res.b[k + 1] += tmp;
                    res.b[k] -= tmp * B;
                }
            }
        }
        return res;
    }
    bool operator<=(const bignum& o) const {
        if (b == o.b) return true;
        return lexicographical_compare(b.rbegin(),b.rend(),o.b.rbegin(),o.b.rend());
    }
};

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x=0, T y=0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
    bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
    P operator+(P p) const { return P(x+p.x, y+p.y); }
    P operator-(P p) const { return P(x-p.x, y-p.y); }
    P operator*(T d) const { return P(x*d, y*d); }
    P operator/(T d) const { return P(x/d, y/d); }
    T dot(P p) const { return x*p.x + y*p.y; }
    T cross(P p) const { return x*p.y - y*p.x; }
    T cross(P a, P b) const { return (a-*this).cross(b-*this); }
    T dist2() const { return x*x + y*y; }
    double dist() const { return sqrt((double)dist2()); }
    // angle to x-axis in.txt interval [-pi, pi]
    double angle() const { return atan2(y, x); }
    P unit() const { return *this/dist(); } // makes dist()=1
    P perp() const { return P(-y, x); } // rotates +90 degrees
    P normal() const { return perp().unit(); }
    // returns point rotated 'a' radians ccw around the origin
    P rotate(double a) const {
        return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")"; }
    friend istream& operator>>(istream& is, P& p) {
        return is >> p.x >> p.y; }
};

typedef Point<long long> P;
vector<P> convexHull(vector<P> pts) {
    if (pts.size() <= 1) return pts;
    sort(pts.begin(), pts.end());
    vector<P> h(pts.size()+1);
    int s = 0, t = 0;
    for (int it = 2; it--; s = --t, reverse(pts.begin(), pts.end()))
        for (P p : pts) {
            while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
            h[t++] = p;
        }
    return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}

int n, t;
long long inv[MAX], fact[MAX], invfact[MAX];
vector<P> v;

void orient(P &a, P &b, P &c) {
    // move points a, b, c to be in.txt counterclockwise order
    long long val = (b - a).cross(c - a);
    assert(val != 0);
    if (val < 0) {swap(a, c);}
}

pair<long long, long long> angleComp(P a, P b, P c) {
    // get a (scaled) value of f(cos(angle ABC))
    P ab = a - b, cb = c - b;
    long long dt = ab.dot(cb);
    dt *= dt;
    int sgn = (ab.dist2() + cb.dist2() >= (a - c).dist2() ? 1 : -1);
    return make_pair(sgn * dt, ab.dist2() * cb.dist2());
}

bool inCircle(P a, P b, P c, P d) {
    // is D in.txt (or on) (ABC)?
    orient(a, b, c);
    P ad = a - d, bd = b - d, cd = c - d;
    return (
                   ad.dist2() * (bd.x * cd.y - bd.y * cd.x) -
                   bd.dist2() * (ad.x * cd.y - ad.y * cd.x) +
                   cd.dist2() * (ad.x * bd.y - ad.y * bd.x)
           ) >= 0;
}

pair<bool, int> check(int l, int r) {
    int start = l, finish = r;
    if (finish < start) {finish += n;}
    pair<long long, long long> best = make_pair(-MOD, 1);
    int w = -1;
    for (int i = start + 1; i < finish; i++) {
        pair<long long, long long> val = angleComp(v[l], v[i % n], v[r]);
        bignum v1 = bignum(val.first) * bignum(best.second);
        bignum v2 = bignum(val.second) * bignum(best.first);
        if (!(v1 <= v2)) {
            best = val;
            w = i % n;
        }
    }
    if (w == -1) {
        // cout << v[l] << ' ' << v[r] << " empty?\n";
        return make_pair(true, -1);
    }
    // cout << v[l] << ' ' << v[r] << " connects to " << v[w] << "?\n";
    for (P Q : v) {
        if (!inCircle(v[l], v[w], v[r], Q)) {return make_pair(false, -1);}
    }
    return make_pair(true, w);
}

void reset(int n) {
    v.clear();
    // for (int i = 0; i < n + 5; i++) {
    // g[i].clear();
    // child[i].clear();
    // }
    t = 1;
}

void solve() {
    cin >> n;
    reset(n);
    vector<P> pts(n);
    for (int i = 0; i < n; i++) {
        cin >> pts[i];
    }
    vector<P> us{pts[0], pts[1]};
    vector<int> us_vals;
    v = convexHull(pts);
    n = v.size();
    for (auto P : us) {
        int i = 0; bool hit = false;
        for (auto Q : v) {
            if (P == Q) {us_vals.push_back(i); hit = true;}
            i++;
        }
        if (!hit) {cout << 0 << '\n'; return;}
    }
    if (v.size() <= 3) {cout << 1 << '\n'; return;}
    queue<pair<pair<int, int>, int>> q;
    vector<int> child[MAX];
    q.push(make_pair(make_pair(us_vals[0], us_vals[1]), -1));
    q.push(make_pair(make_pair(us_vals[1], us_vals[0]), -1));
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        pair<bool, int> resp = check(p.first.first, p.first.second);
        if (!resp.first) {cout << 0 << '\n'; return;}
        if (resp.second == -1) {continue;}
        q.push(make_pair(make_pair(p.first.first, resp.second), t));
        q.push(make_pair(make_pair(resp.second, p.first.second), t));
        if (p.second != -1) {
            child[p.second].push_back(t);
        }
        t++;
    }
    // for (int i = 1; i <= n - 2; i++) {
    // cout << i << ": ";
    // for (int j : child[i]) {cout << j << ' ';}
    // cout << '\n';
    // }
    bool edge_case = true; // both 1 and 2 are roots
    for (int j : child[1]) {
        if (j == 2) {edge_case = false;} // only 1 is root
    }

    vector<long long> dp(n + 7);
    vector<int> sz(n + 7);

    auto cnt = [&](auto self, int v) -> int {
        if (sz[v] != -1) {return sz[v];}
        int res = 1;
        if (!child[v].empty()) {
            for (int u : child[v]) {
                res += self(self, u);
            }
        }
        sz[v] = res;
        return res;
    };

    auto f = [&](auto self, int v) -> long long {
        if (dp[v] != -1LL) {return dp[v];}
        long long res = 1LL;
        if (!child[v].empty()) {
            res = (res * fact[cnt(cnt, v) - 1]) % MOD;
            for (int u : child[v]) {
                res = (res * self(self, u)) % MOD;
                res = (res * invfact[cnt(cnt, u)]) % MOD;
            }
        }
        dp[v] = res;
        return res;
    };

    if (edge_case) {child[1].push_back(2);}

    fill(dp.begin(), dp.end(), -1LL);
    fill(sz.begin(), sz.end(), -1);
    long long res = f(f, 1);

    if (edge_case) {
        child[1].erase(remove(child[1].begin(), child[1].end(), 2), child[1].end());
        child[2].push_back(1);
        fill(dp.begin(), dp.end(), -1LL);
        fill(sz.begin(), sz.end(), -1);
        res = (res + f(f, 2)) % MOD;
    }

    cout << res << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    inv[0] = inv[1] = 1;
    for (int i = 2; i < MAX; i++) {
        inv[i] = MOD - (long long)(MOD / i) * inv[MOD % i] % MOD;
    }
    fact[0] = fact[1] = 1; invfact[0] = invfact[1] = 1;
    for (int i = 2; i < MAX; i++) {
        fact[i] = (fact[i - 1] * (long long)i) % MOD;
        invfact[i] = (invfact[i - 1] * inv[i]) % MOD;
    }
    int tt; cin >> tt; for (int i = 1; i <= tt; i++) {solve();}
//     solve();
}

//3
//5
//1 1
//2 5
//3 3
//4 2
//5 4
//6
//1 1
//3 3
//1 2
//2 1
//3 10000
//19 84
//7
//2 7
//-4 -3
//-3 6
//3 1
//-5 2
//1 -4
//-1 7
