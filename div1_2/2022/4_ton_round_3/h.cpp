#include <bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int random(int st, int dr)
{
    uniform_int_distribution<mt19937::result_type> gen(st, dr);
    return gen(rng);
}
vector<int> lg;
struct bit
{
    vector<int> b;
    void resize(int n)
    {
        b.resize(n + 1);
    }
    void update(int pos, int val)
    {
        int n = (int)b.size() - 1;
        for (int i = pos; i <= n; i += i & (-i))
        {
            b[i] += val;
        }
    }
    int query(int pos)
    {
        int ans = 0;
        for (int i = pos; i; i -= i & (-i))
        {
            ans += b[i];
        }
        return ans;
    }
    int query(int st, int dr)
    {
        return query(dr) - query(st - 1);
    }
};
struct stack_rmq
{
    vector<vector<int>> rmq;
    void insert(int val)
    {
        rmq.push_back({val});
        int sz = rmq.size() - 1;
        for (int i = 1; sz - (1 << i) + 1 >= 0; ++i)
        {
            rmq[sz].push_back(
                    max(rmq[sz][i - 1], rmq[sz - (1 << (i - 1))][i - 1]));
        }
    }
    void update(int val)
    {
        int sz = (int)rmq.size() - 1;
        int cine = val + rmq[sz][0];
        rmq.pop_back();
        insert(cine);
    }
    int query(int st, int dr)
    {
        if (st > dr)
        {
            return 0;
        }
        int pow_2 = lg[dr - st + 1];
        return max(rmq[dr][pow_2], rmq[st + (1 << pow_2) - 1][pow_2]);
    }
};
struct maximal
{
    stack_rmq lesgo;
    vector<pair<int, int>> ranges;
    vector<int> qui;
    string s;
    int n;
    void build(string _s, int _n)
    {
        s = _s;
        n = _n;
        qui = vector<int>(n + 1);
        bool este = false;
        for (int i = 1; i <= n; ++i)
        {
            if (s[i] == '0')
            {
                if (este)
                {
                    lesgo.update(1);
                    ranges[(int)ranges.size() - 1].second++;
                }
                else
                {
                    lesgo.insert(1);
                    ranges.push_back({i, i});
                    este = true;
                }
            }
            else
            {
                este = false;
            }
            qui[i] = (int)ranges.size() - 1;
        }
    }
    int query(int st, int dr)
    {
        if (s[st] == '1')
        {
            int l = qui[st] + 1;
            int r = (s[dr] == '0' ? qui[dr] - 1 : qui[dr]);
            int partial = (s[dr] == '0' ? dr - ranges[qui[dr]].first + 1 : 0);
            return max(lesgo.query(l, r), partial);
        }
        if (s[dr] == '1')
        {
            int r = qui[dr];
            int l = qui[st] + 1;
            int partial = (s[st] == '0' ? ranges[qui[st]].second - st + 1 : 0);
            return max(lesgo.query(l, r), partial);
        }
    }
    int next(int lg, int pos, bool fata)
    {
        assert(s[pos] == '1');
        if (fata)
        {
            int st = pos, dr = n;
            int ans = 0;
            while (st <= dr)
            {
                int mid = (st + dr) / 2;
                if (query(pos, mid) <= lg)
                {
                    ans = mid;
                    st = mid + 1;
                }
                else
                {
                    dr = mid - 1;
                }
            }
            return ans;
        }
        else
        {
            int st = 1, dr = pos;
            int ans = 0;
            while (st <= dr)
            {
                int mid = (st + dr) / 2;
                if (query(mid, pos) < lg)
                {
                    ans = mid;
                    dr = mid - 1;
                }
                else
                {
                    st = mid + 1;
                }
            }
            return ans;
        }
    }
};
vector<vector<pair<int, int>>> find_relevant_ranges(string s, int n)
{
    vector<int> sp(n + 1);
    for (int i = 1; i <= n; ++i)
    {
        sp[i] = sp[i - 1] + (s[i] == '1');
    }
    function<int(int, int)> query = [&](int st, int dr)
    {
        return sp[dr] - sp[st - 1];
    };
    vector<vector<pair<int, int>>> cine(n + 1);
    stack_rmq lesgo;
    vector<pair<int, int>> secv;
    bool este = false;
    for (int i = n; i >= 1; --i)
    {
        if (s[i] == '0')
        {
            if (!este)
            {
                lesgo.insert(1);
                secv.push_back({i, i});
                este = true;
            }
            else
            {
                lesgo.update(1);
                secv[(int)secv.size() - 1].first--;
            }
        }
        else
        {
            este = false;
        }
        int cnt = 0;
        int p = i;
        while (p <= n)
        {
            int st = 0, dr = (int)secv.size() - 1;
            int rep = -1;
            while (st <= dr)
            {
                int mid = (st + dr) / 2;
                if (lesgo.query(mid, (int)secv.size() - 1) > cnt)
                {
                    rep = mid;
                    st = mid + 1;
                }
                else
                {
                    dr = mid - 1;
                }
            }
            if (rep == -1)
            {
                cine[i].push_back({p, n});
                break;
            }
            st = secv[rep].first, dr = secv[rep].second;

            int l = (dr - st + 1);
            cnt += (secv[rep].first - p);
            if (st != p)
            {
                cine[i].push_back({p, st - 1});
            }
            p = secv[rep].first;
            if (l > cnt)
            {
                if (dr == n)
                {
                    break;
                }
                int save = dr + 1;
                bool ok = false;
                for (int j = 0; j < cine[save].size(); ++j)
                {
                    if (cine[save][j].second - save + 1 >= l)
                    {
                        pair<int, int> interv = {max(save + l - 1, cine[save][j].first), cine[save][j].second};
                        if (query(interv.first, interv.second))
                        {
                            int low = interv.first, high = interv.second;
                            int qui = -1;
                            while (low <= high)
                            {
                                int mid = (low + high) / 2;
                                if (query(interv.first, mid))
                                {
                                    qui = mid;
                                    high = mid - 1;
                                }
                                else
                                {
                                    low = mid + 1;
                                }
                            }
                            cine[i].push_back({qui, qui});
                            cnt += (qui - p + 1);
                            p = qui + 1;
                            ok = true;
                            break;
                        }
                    }
                }
                if (!ok)
                {
                    break;
                }
            }
            else
            {
                cine[i].push_back({p, dr});
                cnt += dr - p + 1;
                p = dr + 1;
            }
        }
    }
    return cine;
}

vector<vector<pair<int, int>>> cine1, cine2;
int n;
string s;
void smart()
{
    long long ans = 0;
    vector<vector<pair<int, int>>> events1(n + 1);
    vector<vector<pair<int, int>>> events2(n + 1);
    bit tree1;
    bit tree2;
    maximal cine;
    cine.build(s, n);
    tree1.resize(n + 1);
    tree2.resize(n + 1);
    int p1 = 1;
    int p2 = 1;
    for (int i = 1; i <= n; ++i)
    {
        for (auto j : cine1[i])
        {
            events1[j.first].push_back({i, 1});
            if (j.second + 1 <= n)
            {
                events1[j.second + 1].push_back({i, -1});
            }
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        for (auto j : cine2[i])
        {
            events2[j.first].push_back({i, 1});
            if (j.second + 1 <= n)
            {

                events2[j.second + 1].push_back({i, -1});
            }
        }
    }
    function<void(int)> move1 = [&](int pos)
    {
        while (p1 <= pos)
        {
            for (auto i : events1[p1])
            {
                tree1.update(i.first, i.second);
            }
            p1++;
        }
    };
    function<void(int)> move2 = [&](int pos)
    {
        while (p2 <= pos)
        {
            for (auto i : events2[p2])
            {
                tree2.update(i.first, i.second);
            }
            p2++;
        }
    };
    for (auto x : cine.ranges)
    {
        int lg = x.second - x.first + 1;
        int l = 0, r = 0;
        int ways1 = 0, ways2 = 0;
        if (x.first - 1 >= 1)
        {
            move1(x.first - 1);
            for (int i = 1; i < lg; ++i)
            {
                int qui = cine.next(i, x.first - 1, false);
                int last = x.first - i;
                if (qui <= last)
                {
                    ans += tree1.query(qui, last);
                }
            }
            l = cine.next(lg, x.first - 1, false);
            int last = x.first - lg;
            ways1 = x.first - l + 1;
            if (l <= last)
            {
                ways1 -= tree1.query(l, last);
            }
        }
        else
        {
            l = 1;
            ways1 = 1;
        }
        if (x.second + 1 <= n)
        {
            move2(x.second + 1);
            for (int i = 1; i < lg; ++i)
            {
                int qui = cine.next(i, x.second + 1, true);
                int first = x.second + i;

                if (first <= qui)
                {
                    ans += tree2.query(first, qui);
                }
            }
            r = cine.next(lg, x.second + 1, true);
            int first = x.second + lg;
            ways2 = r - x.second + 1;
            if (first <= r)
            {
                ways2 -= tree2.query(first, r);
            }
        }
        else
        {
            r = n;
            ways2 = 1;
        }
        ans += 1ll * (r - x.second + 1ll) * (x.first - l + 1ll) - 1ll * ways1 * ways2;
    }
    int lg = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (s[i] == '1')
        {
            lg++;
        }
        else
        {
            ans += 1ll * lg * (lg + 1) / 2;
            lg = 0;
        }
    }
    ans += 1ll * lg * (lg + 1) / 2;
    cout << ans << '\n';
}
int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
    int q;
    cin >> q;
    while (q--)
    {
        cin >> n >> s;
        lg = vector<int>(n + 1);
        for (int i = 2; i <= n; ++i)
        {
            lg[i] = lg[i / 2] + 1;
        }
        s = '$' + s;
        cine1 = find_relevant_ranges(s, n);
        reverse(s.begin() + 1, s.end());
        cine2 = find_relevant_ranges(s, n);
        reverse(s.begin() + 1, s.end());
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 0; j < (int)cine2[i].size(); ++j)
            {
                cine2[i][j].first = n - cine2[i][j].first + 1;
                cine2[i][j].second = n - cine2[i][j].second + 1;
                swap(cine2[i][j].first, cine2[i][j].second);
            }
            reverse(cine2[i].begin(), cine2[i].end());
        }
        for (int i = 1; i <= n; ++i)
        {
            if (i < (n - i + 1))
            {
                swap(cine2[i], cine2[n - i + 1]);
            }
        }
        smart();
    }
}