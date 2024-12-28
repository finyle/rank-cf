#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pll pair<ll, ll>

const int B = 6, MAX = 2e5 + B + 5;

int n, q, offset, numBlocks; ll A[MAX]; pll seg[MAX];

pll comb(pll a, pll b){
    auto [vl, cl] = a;
    auto [vr, cr] = b;

    // Not defined
    if (vl == -1)
        return b;
    if (vr == -1)
        return a;

    // Doesn't cross cutoff
    if (vl < cr - 1)
        return {vr, (ll)2e18};
    if (vl >= cr)
        return {vr + 1, (ll)2e18};

    // If vl == cr - 1
    return {vr, cl};
}
void updSeg(int i, pll v){
    seg[i += numBlocks] = v;

    for (i /= 2; i > 0; i /= 2)
        seg[i] = comb(seg[i * 2], seg[i * 2 + 1]);
}
ll qry(int l = 0, int r = numBlocks - 1){
    pll retL = {-1, -1};
    pll retR = {-1, -1};

    for (l += numBlocks, r += numBlocks; l <= r; r /= 2, l /= 2){
        if (l % 2 == 1)
            retL = comb(retL, seg[l++]);
        if (r % 2 == 0)
            retR = comb(seg[r--], retR);
    }
    return comb(retL, retR).first;
}
void updBlock(int blk){
    int l = blk * B;
    int r = l + B - 1;

    ll val = 0;
    for (int i = l; i <= r; i++)
        val = floor(sqrtl((long double)val + A[i]));

    ll req = val + 1;
    for (int i = r; i >= l; i--){
        if (req > 2e9){
            updSeg(blk, {val, (ll)2e18});
            return;
        }
        req = req * req - A[i];
    }
    updSeg(blk, {val, req});
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> q;

    offset = (B - n % B) % B;
    n += offset;
    numBlocks = n / B;

    for (int i = offset; i < n; i++)
        cin >> A[i];

    for (int b = 0; b < numBlocks; b++)
        updBlock(b);

    while (q--){
        ll k, x;
        cin >> k >> x;
        k--;
        k += offset;

        A[k] = x;
        updBlock(k / B);

        cout << qry() << "\n";
    }
}