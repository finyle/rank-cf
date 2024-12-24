#include <bits/stdc++.h>
#define ru_(i,l,r) for(int i=(l);i<=(r);i++)
#define ru(i,l,r) for(int i=(l);i<(r);i++)
#define rup(i,l,r) for(int i=(l);i<=(r);i+=2)
#define rd(i,r,l) for(int i=(r);i>=(l);i--)
#define ll long long
#define pii pair<ll,int>
#define s1 first
#define s2 second

using namespace std;

void solve(){
    int n,k; cin>>n>>k; int A[n+1][n+1];
    ru_(i,1,n) ru_(j,i,n) cin>>A[i][j];
    vector<int> dp[n+1]; dp[0]={0};
    ru_(i,1,n){
        priority_queue<array<int,3>> pq;
        pq.push({dp[i-1][0], i-1,0});
        for(int j=i-2;j>=-1;j--) pq.push({(j<0?0:dp[j][0])+A[j+2][i],j,0});
        while(pq.size() && dp[i].size()<k){
            auto[val,j,num]=pq.top(); pq.pop();
            dp[i].push_back(val);
            if(j<0 or num+1>=dp[j].size()) continue;
            if(j==i-1) pq.push({dp[i-1][num+1],i-1,num+1});
            else pq.push({dp[j][num+1]+A[j+2][i],j,num+1});
        }
    }
    for(int i: dp[n]) cout<<i<<" ";cout<<" \n";
};
int main(){int t;cin>>t;while(t--)solve();}