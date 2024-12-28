#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

const ll N = (1 << 22) + 5, Mod = 2013265921, G = 31;

inline ll power(ll x, ll y){
    ll ret = 1;
    while(y){
        if(y & 1) ret = ret * x % Mod;
        x = x * x % Mod, y >>= 1;
    }
    return ret;
}

ll p[N] = {}, w[N] = {}, g[N] = {}, iv[N] = {};

inline void dft(ll n, ll a[], bool idft){
    for(ll i = 0 ; i < n ; i ++) if(i < p[i]) swap(a[i], a[p[i]]);
    for(ll m = 1 ; m < n ; m <<= 1) for(ll j = 0, k = 0 ; j < n ; j += m << 1, k ++) for(ll i = j ; i < j + m ; i ++){
                ll x = a[i], y = a[i + m];
                a[i] = x + y, a[i] >= Mod && (a[i] -= Mod);
                a[i + m] = (x - y + Mod) * w[k] % Mod;
            }
    if(!idft) return;
    reverse(a + 1, a + n);
    for(int i = 0 ; i < n ; i ++) a[i] = a[i] * iv[n] % Mod;
}

inline ll sqr(ll x){
    return x * x;
}

ll n = 0, m = 0, a[3][N] = {}, b[3][N] = {}, c[N] = {}, d[N] = {};
char s[N] = {}, t[N] = {};

inline ll work(ll L, ll R, ll l, ll r){
    ll M = 1; while(M < R - L + r - l) M <<= 1;
    w[0] = 1;
    for(ll k = 1 ; k < M ; k <<= 1){
        ll bit = M / 2 / k;
        if(k == M / 2) for(ll i = 0; i < k ; i ++) p[i + k] = p[i] | bit;
        else for(ll i = 0 ; i < k ; i ++){
                w[i + k] = w[i] * g[k] % Mod;
                p[i + k] = p[i] | bit;
            }
    }
    for(ll i = 0 ; i < M ; i ++){
        p[i] = p[i >> 1] >> 1;
        if(i & 1) p[i] |= M >> 1;
    }
    ll z = 0;
    for(ll i = 0 ; i < M ; i ++){
        c[i] = 0;
        for(ll f = 0 ; f < 3 ; f ++)  a[f][i] = b[f][i] = 0;
    }
    for(ll i = L ; i < R ; i ++){
        ll x = (s[i] == '-') ? 0 : (s[i] - 'a' + 1);
        a[0][i - L] = x ? 0 : 1, a[1][i - L] = 2 * x, a[2][i - L] = sqr(x), d[i] = sqr(x);
    }
    d[R] = 0;
    for(ll i = l ; i < r ; i ++){
        ll x = (t[i] == '-') ? 0 : (t[i] - 'a' + 1);
        b[0][r - i] = sqr(x), b[1][r - i] = x, b[2][r - i] = x ? 0 : 1, z += sqr(x);
    }
    for(ll f = 0 ; f < 3 ; f ++){
        dft(M, a[f], 0), dft(M, b[f], 0);
        for(ll i = 0 ; i < M ; i ++) c[i] = (c[i] + a[f][i] * b[f][i]) % Mod;
    }
    dft(M, c, 1);
    for(ll i = 0 ; i < r - l ; i ++) z += d[i + L];
    for(ll i = L ; i <= R - (r - l) ; z -= d[i], z += d[i + (r - l)], i ++) if(z % Mod == c[i - L + r - l]) return i;
    return -1;
}

int main(){
    for(ll i = 1 ; i < N ; i <<= 1) g[i] = power(G, Mod / 4 / i), iv[i] = power(i, Mod - 2);
    scanf("%lld %lld", &n, &m);
    scanf("%s %s", s, t);
    while(n && m && s[n - 1] != '*' && t[m - 1] != '*'){
        if(s[n - 1] != t[m - 1] && s[n - 1] != '-' && t[m - 1] != '-'){
            printf("No");
            return 0;
        }
        else n --, m --;
    }
    reverse(s, s + n), reverse(t, t + m);
    while(n && m && s[n - 1] != '*' && t[m - 1] != '*'){
        if(s[n - 1] != t[m - 1] && s[n - 1] != '-' && t[m - 1] != '-'){
            printf("No");
            return 0;
        }
        else n --, m --;
    }
    reverse(s, s + n), reverse(t, t + m);
    if(min(n, m) == 0){
        while(n && s[n - 1] == '*') n --;
        while(m && t[m - 1] == '*') m --;
        if(max(n, m) == 0) printf("Yes");
        else printf("No");
        return 0;
    }
    bool u = 0, v = 0;
    for(ll i = 0 ; i < n ; i ++) if(s[i] == '*') u = 1;
    for(ll i = 0 ; i < m ; i ++) if(t[i] == '*') v = 1;
    if(u){
        if(v){
            printf("Yes");
            return 0;
        }
        else swap(n, m), swap(s, t);
    }
    ll L = 0, R = 0;
    for(ll l = 1, r = l ; l < m ; l = r + 1, r = l){
        while(t[r] != '*') r ++;
        if(r - l) while(1){
                R = min(n, L + 2 * (r - l));
                if(R - L < r - l){
                    printf("No");
                    return 0;
                }
                ll h = work(L, R, l, r);
                if(h == -1) L = R - (r - l) + 1;
                else{
                    L = h + r - l;
                    break;
                }
            }
    }
    printf("Yes");
    return 0;
}

//10 10
//justmonika
//        j-stsayori
