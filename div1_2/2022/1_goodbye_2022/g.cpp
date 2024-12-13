#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

#define int long long
#define ll long long
#define ii pair<ll,ll>
#define iii pair<ii,ll>
#define fi first
#define se second
#define endl '\n'
#define debug(x) cout << #x << ": " << x << endl

#define pub push_back
#define pob pop_back
#define puf push_front
#define pof pop_front
#define lb lower_bound
#define ub upper_bound

#define rep(x,start,end) for(auto x=(start)-((start)>(end));x!=(end)-((start)>(end));((start)<(end)?x++:x--))
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()

#define indexed_set tree<ll,null_type,less<ll>,rb_tree_tag,tree_order_statistics_node_update>
//change less to less_equal for non distinct pbds, but erase will bug

mt19937 rng(chrono::system_clock::now().time_since_epoch().count());

const int MOD=998244353;

ll qexp(ll b,ll p,int m){
    ll res=1;
    while (p){
        if (p&1) res=(res*b)%m;
        b=(b*b)%m;
        p>>=1;
    }
    return res;
}

ll inv(ll i){
    return qexp(i,MOD-2,MOD);
}

ll fix(ll i){
    i%=MOD;
    if (i<0) i+=MOD;
    return i;
}

ll fac[1000005];
ll ifac[1000005];

ll nCk(int i,int j){
    if (i<j) return 0;
    return fac[i]*ifac[j]%MOD*ifac[i-j]%MOD;
}

//https://github.com/kth-competitive-programming/kactl/blob/main/content/numerical/NumberTheoreticTransform.h
const ll mod = (119 << 23) + 1, root = 62; // = 998244353
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
typedef vector<int> vi;
typedef vector<ll> vl;
void ntt(vl &a) {
    int n = sz(a), L = 31 - __builtin_clz(n);
    static vl rt(2, 1);
    for (static int k = 2, s = 2; k < n; k *= 2, s++) {
        rt.resize(n);
        ll z[] = {1, qexp(root, mod >> s, mod)};
        rep(i,k,2*k) rt[i] = rt[i / 2] * z[i & 1] % mod;
    }
    vi rev(n);
    rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
                ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
                a[i + j + k] = ai - z + (z > ai ? mod : 0);
                ai += (ai + z >= mod ? z - mod : z);
            }
}
vl conv(const vl &a, const vl &b) {
    if (a.empty() || b.empty()) return {};
    int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
    int inv = qexp(n, mod - 2, mod);
    vl L(a), R(b), out(n);
    L.resize(n), R.resize(n);
    ntt(L), ntt(R);
    rep(i,0,n) out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
    ntt(out);
    return {out.begin(), out.begin() + s};
}

vector<int> v;

vector<int> solve(int l,int r,vector<int> poly){
    if (poly.empty()) return poly;

    if (l==r){
        poly=conv(poly,{1,1});
        poly.erase(poly.begin(),poly.begin()+v[l]);
        return poly;
    }

    int m=l+r>>1;
    int num=0;
    rep(x,l,r+1) num+=v[x];
    num=min(num,sz(poly));

    vector<int> small(poly.begin(),poly.begin()+num);
    poly.erase(poly.begin(),poly.begin()+num);

    vector<int> mul;
    rep(x,0,r-l+2) mul.pub(nCk(r-l+1,x));
    poly=conv(poly,mul);

    small=solve(m+1,r,solve(l,m,small));
    poly.resize(max(sz(poly),sz(small)));
    rep(x,0,sz(small)) poly[x]=(poly[x]+small[x])%MOD;

    return poly;
}

int solve(string s){
    if (s=="") return 1;
    v.clear();

    int mn=0,curr=0;
    for (auto it:s){
        if (it=='(') curr++;
        else{
            curr--;
            if (curr<mn){
                mn=curr;
                v.pub(1);
            }
            else{
                v.pub(0);
            }
        }
    }

    return solve(0,sz(v)-1,{1})[0];
}

int n;
string s;
int pref[500005];

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin.exceptions(ios::badbit | ios::failbit);

    fac[0]=1;
    rep(x,1,1000005) fac[x]=fac[x-1]*x%MOD;
    ifac[1000004]=inv(fac[1000004]);
    rep(x,1000005,1) ifac[x-1]=ifac[x]*x%MOD;

    cin>>s;
    n=sz(s);
    pref[0]=0;
    rep(x,0,n) pref[x+1]=pref[x]+(s[x]=='('?1:-1);

    int pos=min_element(pref,pref+n+1)-pref;
    string a=s.substr(0,pos),b=s.substr(pos,n-pos);
    reverse(all(b)); for (auto &it:b) it^=1;
    cout<<solve(a)*solve(b)%MOD<<endl;
}

//())(()
