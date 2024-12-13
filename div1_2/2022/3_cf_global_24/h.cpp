#include <bits/stdc++.h>
using namespace std;

#define int long long
#define ii pair<int,int>
#define iii tuple<int,int,int>
#define fi first
#define se second
#define endl '\n'

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

int n,m,k;
ii arr[600005];
int ans[400005];

vector<int> uni;
int nxt[200005];
int state[200005];
int state2[200005];

bool has(int l,int r,set<int> &s){
    auto it=s.lb(l);
    return *it<r;
}

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin.exceptions(ios::badbit | ios::failbit);

    cin>>n>>m>>k;
    rep(x,0,m) cin>>arr[x].fi>>arr[x].se;
    rep(x,0,m) arr[x].fi--,arr[x].se--;
    rep(x,0,2*m) arr[x+m]=arr[x];

    int l=0;

    while (l<m){
        uni={0,n};
        rep(x,l,l+2*k) uni.pub(arr[x].fi),uni.pub(arr[x].se+1);
        sort(all(uni)); uni.erase(unique(all(uni)),uni.end());
        rep(x,0,sz(uni)-1) nxt[uni[x]]=uni[x+1];

        set<ii> s; for (auto it:uni) s.insert({it,it}); //position, color
        rep(x,0,sz(uni)) state[uni[x]]=state2[uni[x]]=1;

        vector<iii> proc; //time, position, state
        rep(x,l+k,l+2*k){
            if (s.count({arr[x].fi,arr[x].fi}) && state[arr[x].fi]){
                proc.pub({x,arr[x].fi,state[arr[x].fi]});
                state[arr[x].fi]=0;
            }

            while (true){
                auto it=s.ub(ii(arr[x].fi,1e9));
                if ((*it).fi>arr[x].se) break;

                if (arr[x].se+1<(*next(it)).fi) s.insert({arr[x].se+1,(*it).se});
                else{
                    proc.pub({x,(*it).se,state[(*it).se]});
                    state[(*it).se]=0;
                }

                s.erase(it);
            }
        }

        int curr=0;
        set<int> pos={n};
        for (auto [a,b]:s) if (b!=n){
                curr++;
                if (state[b]) curr+=nxt[b]-b-1;
                pos.insert(b);
            }

        s.clear(); for (auto it:uni) s.insert({it,it}); //color, position
        set<ii> ranges; rep(x,0,sz(uni)-1) ranges.insert({uni[x],uni[x+1]});

        rep(x,l+k,l){
            //merge things
            auto it=s.lb({arr[x].fi,-1});
            vector<int> v={(*it).se};
            while ((*it).fi<=arr[x].se){
                it=next(it);
                s.erase(prev(it));
                v.pub((*it).se);
            }

            if (sz(v)>1){
                rep(x,0,sz(v)-1){
                    if (state[v[x]] && state2[v[x]]) curr-=v[x+1]-v[x]-1;
                    state2[v[x]]=0;
                    curr-=has(v[x],v[x+1],pos);
                    ranges.erase({v[x],v[x+1]});
                }
                curr+=has(v[0],v[sz(v)-1],pos);
                s.insert({arr[x].fi,v[0]});
                ranges.insert({v[0],v[sz(v)-1]});
            }

            while (!proc.empty() && get<0>(proc.back())==x+k){
                int a,b,c; tie(a,b,c)=proc.back(); proc.pob();
                if (c){
                    state[b]=c;
                    if (state[b] && state2[b]) curr+=nxt[b]-b-1;
                }

                if (!pos.count(b)){
                    auto it=prev(ranges.ub({b,1e9}));
                    int l,r; tie(l,r)=*it;
                    if (!has(l,r,pos)) curr++;
                    pos.insert(b);
                }
            }

            ans[x]=curr;
        }


        l+=k;
    }

    rep(x,0,m) cout<<ans[x]<<" "; cout<<endl;
}

//7 5 5
//3 5
//2 3
//4 6
//5 7
//1 2
