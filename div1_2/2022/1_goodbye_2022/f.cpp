#include <bits/stdc++.h>
using namespace std;

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

#define rep(x,start,end) for(int x=(start)-((start)>(end));x!=(end)-((start)>(end));((start)<(end)?x++:x--))
#define all(x) (x).begin(),(x).end()
#define sz(x) (int)(x).size()

mt19937 rng(chrono::system_clock::now().time_since_epoch().count());

int n,a,b;

bool isSub(int i,int j){
    if (i<0 || j<0) return false;
    return (j&i)==i;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin.exceptions(ios::badbit | ios::failbit);

    cin>>n>>a>>b;

    int ans=0;
    for (int sub=b;sub;sub=(sub-1)&b) rep(bit,0,20) if (sub&(1<<bit)){
                if (isSub(a-(1<<bit),n*sub-(1<<bit))){
                    ans^=(1<<bit);
                }
            }

    cout<<ans*(n%2)<<endl;
}

// 3 5 3