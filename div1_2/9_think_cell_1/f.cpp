#pragma GCC optimize("O3,unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
#define ll long long
#define pb push_back
#define mp make_pair
#define nline "\n"
#define f first
#define s second
#define pll pair<ll,ll>
#define all(x) x.begin(),x.end()
const ll MAX=100100;
void solve(){
    ll n,q; cin>>n>>q;
    ll till=1,len=1;
    while(till<n){
        till*=2;
        len++;
    }
    ll ans=0;
    vector<vector<ll>> track(2,vector<ll>(till+5,0));
    auto add=[&](ll x,ll p){
        queue<ll> trav;
        if(track[p][x]){
            return;
        }
        trav.push(x); track[p][x]=1;
        while(!trav.empty()){
            auto it=trav.front();
            trav.pop();
            if(track[0][it]&track[1][it]){
                ans=max(ans,it);
            }
            for(ll j=0;j<len;j++){
                if(it&(1<<j)){
                    ll cur=(it^(1<<j));
                    if(!track[p][cur]){
                        track[p][cur]=1;
                        trav.push(cur);
                    }
                }
            }
        }
    };
    ll supermask=till-1;
    vector<ll> a(q+5);
    for(ll i=1;i<=q;i++){
        ll h; cin>>h;
        a[i]=(h+ans)%n;
        add(a[i],0);
        add(supermask^a[i],1);
        cout<<ans<<" \n"[i==q];
    }
    return;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);
#endif
    ll test_cases=1;
    cin>>test_cases;
    while(test_cases--){
        solve();
    }
    cout<<fixed<<setprecision(10);
    cerr<<"Time:"<<1000*((double)clock())/(double)CLOCKS_PER_SEC<<"ms\n";
}

//2
//5 2
//1 2
//7 4
//3 1 5 2
