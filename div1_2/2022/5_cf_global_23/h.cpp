#include <bits/stdc++.h>
using namespace std;

#ifdef SG
#include <debug.h>
#else
template<typename T> struct outputer;
struct outputable {};
#define PRINT(...)
#define OUTPUT(...)
#define show(...)
#define debug(...)
#define deepen(...)
#define timer(...)
#define fbegin(...)
#define fend
#define pbegin(...)
#define pend
#endif

#define ARG4(_1,_2,_3,_4,...) _4

#define forn3(i,l,r) for (int i = int(l); i < int(r); ++i)
#define forn2(i,n) forn3 (i, 0, n)
#define forn(...) ARG4(__VA_ARGS__, forn3, forn2) (__VA_ARGS__)

#define ford3(i,l,r) for (int i = int(r) - 1; i >= int(l); --i)
#define ford2(i,n) ford3 (i, 0, n)
#define ford(...) ARG4(__VA_ARGS__, ford3, ford2) (__VA_ARGS__)

#define ve vector
#define pa pair
#define tu tuple
#define mp make_pair
#define mt make_tuple
#define pb emplace_back
#define fs first
#define sc second
#define all(a) (a).begin(), (a).end()
#define sz(a) ((int)(a).size())

typedef long double ld;
typedef signed __int128 lll;
typedef unsigned __int128 ulll;
typedef int64_t ll;
typedef uint64_t ull;
typedef uint32_t ui;
typedef uint16_t us;
typedef uint8_t uc;
typedef pa<int, int> pii;
typedef pa<int, ll> pil;
typedef pa<ll, int> pli;
typedef pa<ll, ll> pll;
typedef ve<int> vi;

template<typename T> inline auto sqr (T x) -> decltype(x * x) {return x * x;}
template<typename T1, typename T2> inline bool umx (T1& a, T2 b) {if (a < b) {a = b; return 1;} return 0;}
template<typename T1, typename T2> inline bool umn (T1& a, T2 b) {if (b < a) {a = b; return 1;} return 0;}

const int N = 100000;
const int X = 1000000000;
const int T = 3;

struct Input {
    int n;
    std::array<int, T> k;
    int a[N], t[N], d[N];

    bool read() {
        if (!(cin >> n)) {
            return 0;
        }
        forn (i, T) {
            cin >> k[i];
        }
        forn (i, n) {
            cin >> a[i] >> t[i] >> d[i];
            --t[i];
            --d[i];
        }
        return 1;
    }

    void init(const Input& input) {
        *this = input;
    }
};

struct Data: Input {
    ll ans;

    void write() {
        cout << ans << endl;
    }
};


namespace Main {
    const lll P = 2 * N + 1;
    const lll Q = 2 * N + 2;
    const lll R = 2 * N + 3;
    const lll A[3] = {3 * P * Q, 3 * P * R, 3 * Q * R};
    const lll M = 3 * P * Q * R * N;
    const lll inf = (X + 1) * M;

    struct SNM {
        int rnd = 0;
        int n;
        int pr[N];

        void init(int cnt) {
            n = cnt;
            forn (i, n) {
                pr[i] = i;
            }
        }

        int get_p(int v) {
            if (v < 0 || pr[v] == v) {
                return v;
            }
            return pr[v] = get_p(pr[v]);
        }

        bool add(int v) {
            v = get_p(v);
            if (v == -1) {
                return 0;
            }
            pr[v] = v - 1;
            return 1;
        }
    };

    struct Solution: Data {
        SNM snm;

        int m;
        lll b[N], c[N];
        vi ord[T];

        array<int, T> check(const array<lll, T>& adds) {
            forn (i, n) {
                c[i] = b[i] + adds[t[i]];
            }
            auto cmp = [&](int lhs, int rhs) {
                return c[lhs] > c[rhs];
            };
            static vi q;
            q.clear();
            forn (i, T) {
                static vi w;
                w.resize(sz(q) + sz(ord[i]));
                merge(all(q), all(ord[i]), w.begin(), cmp);
                q.swap(w);
            }

            snm.init(n);
            array<int, T> cnt{};
            int tot = 0;
            ll val = 0;
            for (int i : q) {
                if (tot >= m) {
                    break;
                }
                if (snm.add(d[i])) {
                    cnt[t[i]]++;
                    tot++;
                    val += a[i];
                }
            }
            if (cnt == k) {
                ans = val;
            }
            return cnt;
        }

        // x[i] == adds[(i + 1) % T] - adds[i]

        array<lll, T> get_middle_point(const array<lll, T>& lb, const array<lll, T>& rb) {
            array<lll, T> x;
            forn (i, T) {
                x[i] = lb[i] + rb[i];
            }
            lll sum = accumulate(all(x), lll(0));
            forn (i, T) {
                x[i] = T * x[i] - sum;
                if (x[i] >= 0) {
                    x[i] /= (2 * T);
                } else {
                    x[i] = (x[i] - 2 * T + 1) / (2 * T);
                }
            }
            sum = accumulate(all(x), lll(0));
            forn (i, T) {
                if (sum < 0 && x[i] < rb[i]) {
                    x[i]++;
                    sum++;
                }
                assert(x[i] >= lb[i]);
                assert(x[i] <= rb[i]);
            }
            assert(sum == 0);
            return x;
        }

        bool search() {
            array<lll, T> lb, rb;
            forn (i, T) {
                lb[i] = -2 * inf;
                rb[i] = 2 * inf;
            }

            while (true) {
                {
                    lll sum_l = accumulate(all(lb), lll(0));
                    lll sum_r = accumulate(all(rb), lll(0));
                    forn (i, T) {
                        lll sol = sum_l - lb[i];
                        lll sor = sum_r - rb[i];
                        umx(lb[i], -sor);
                        umn(rb[i], -sol);
                        if (lb[i] > rb[i]) {
                            return 0;
                        }
                    }
                }
                array<lll, T> x = get_middle_point(lb, rb);
                array<lll, T> adds{};
                forn (i, T - 1) {
                    adds[i + 1] = adds[i] + x[i];
                }
                array<int, T> cnt = check(adds);
                assert(accumulate(all(cnt), 0) == m);
                if (cnt == k) {
                    return 1;
                }
                forn (i, T) {
                    lll d1 = cnt[i] - k[i];
                    lll d2 = cnt[(i + 1) % T] - k[(i + 1) % T];
                    if (d1 > 0 && d2 < 0) {
                        lb[i] = x[i] + 1;
                    }
                    if (d1 < 0 && d2 > 0) {
                        rb[i] = x[i] - 1;
                    }
                }
            }
        }

        void solve() {
            forn (i, n) {
                b[i] = a[i] * M + i * A[t[i]];
            }
            forn (i, n) {
                ord[t[i]].pb(i);
            }
            forn (i, T) {
                sort(all(ord[i]), [&](int lhs, int rhs) {
                    return b[lhs] > b[rhs];
                });
            }
            m = accumulate(all(k), 0);

            {
                array<int, T> r = check({});
                if (accumulate(all(r), 0) != m) {
                    ans = -1;
                    return;
                }
            }
            forn (i, T) {
                array<lll, T> adds{};
                adds[i] = inf;
                if (check(adds)[i] < k[i]) {
                    ans = -1;
                    return;
                }
                adds[i] = -inf;
                if (check(adds)[i] > k[i]) {
                    ans = -1;
                    return;
                }
            }
            assert(search());
        }

        void clear() {
            forn (i, T) {
                ord[i].clear();
            }
        }
    };
}


Main::Solution sol;

int main() {
#ifdef SG
    freopen((problemname + ".in").c_str(), "r", stdin);
//		freopen((problemname + ".out").c_str(), "w", stdout);
#endif

    int t;
    cin >> t;
    forn (i, t) {
        sol.read();
        sol.solve();
        sol.write();
        sol.clear();
    }

    return 0;
}

//4
//4 1 1 0
//1 2 1
//1 1 1
//0 1 2
//1 2 2
//3 1 1 1
//1 1 2
//7 2 1
//9 3 2
//4 2 1 0
//100 2 1
//5 2 3
//7 1 2
//5 1 2
//5 1 1 1
//10 3 1
//9 2 3
//20 1 1
//16 1 4
//1 3 4
