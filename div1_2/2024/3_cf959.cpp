#include <bits/stdc++.h>
#define ru(i,l,r) for(int i=(l);i<=(r);i++)
#define rup(i,l,r) for(int i=(l);i<=(r);i+=2)
#define rd(i,r,l) for(int i=(r);i>=(l);i--)
#define ll long long
#define pii pair<ll,int>
#define s1 first
#define s2 second

using namespace std;

struct a{
    int main() {
        int t;cin >> t;
        while (t--) {
            int n,m; cin>>n>>m;
            vector<vector<int>> a(n,vector<int>(m));
            for(auto &i:a)
                for(auto &j: i) cin>>j;
            if(n*m==1) cout<<"-1\n";
            else{
                ru(i,0,n) {
                    ru(j,0,m) cout<<a[(i+1)%n][(j+1)%m]<<' ';
                    cout<<endl;}
            }
        }
    }
};
struct b{
    void solve(){
        int n; cin>>n; string s,t; cin>>s,t;
        for(int i=0;i<s.size()&&s[i]=='0';++i) {
            if(t[i]!='0') {cout<<"no"<<endl; return;}
        }; cout<<"yes"<<endl;
    }
    int main(){int t; cin>>t; while(t--) solve();}
};
struct c{
    int main(){
        int t; cin>>t;
        while(t--){
            int n; ll x; cin>>n>>x; vector<ll> a(n+1);
            ru(i,1,n) cin>>a[i];
            partial_sum(a.begin()+1,a.end(),a.begin()+1);
            vector<int> dp(n+2);
            rd(i,n-1,0) {
                int q=upper_bound(a.begin(),a.end(),a[i]+x)-a.begin();
                dp[i]=dp[q]+q-i-1;
            }
            cout<<accumulate(dp.begin(),dp.end(),0ll)<<endl;
        }
    }
};
struct d{
    int main(){
        int t; cin>>t;
        while(t--){
            int n; cin>>n; vector<int> a(n);
            for(auto& i:a) cin>>i;
            vector<int> pos(n);
            iota(pos.begin(),pos.end(),0);
            vector<pair<int,int>> ans;
            ru(i,n-1,i){
                vector<int> occ(i,-1);
                for(auto j: pos){
                    if(occ[a[j]%i]!=-1) {
                        ans.emplace_back(j,occ[a[j]%i]);
                        pos.erase(find(pos.begin(),pos.end(),j));
                        break;
                    }
                    occ[a[j]%i]=j;
                }
            }
            reverse(ans.begin(), ans.end()); cout<<"yes\n";
            for(auto [x,y]: ans) cout<<x+1<<' '<<y+1<<endl;
        }
    }
};
struct e{
    void solve(){
        int k; cin>>k; vector<int> a(k);
        ru(i,0,k) {
            cin>>a[i];
            ru(i,0,a[i]){int trash; cin>>trash;}
        }
        sort(a.begin(), a.end(), greater<>());
        int ans=0;
        for(auto x: a){
            for(int h=23;h>=0;--h){
                int ca=ans>>h&1,cx=x>>h&1;
                if(cx==0) continue;
                if(ca==0) ans|=1<<h;
                else{ans|=(1<<h)-1; break;}
            }
        }; cout<<ans<<endl;
    }
    int main(){int t; cin>>t;while(t--)solve();}
};
struct f{
    int n, k; string res, s;
    vector<vector<bool>> memo; vector<int> cnt;
    bool rec(int i,int cur){
        if(i==k){
            if(cur==0) return true;
            return false;
        }
        if(memo[i][cur]) return false;
        for(int c=0;c<2;c++){
            int q=cur;
            if(c==0) q+=cnt[i]; else q+=n-cnt[i];
            if((q&1)==s[i]-'0'){
                if(rec(i+1,q/2)){
                    res+=char(c+'0'); return true;
                }
            }
        }
        return false;
    }
    int main(){
        int t; cin>>t;
        while(t--){
            cin>>n>>k; cin>>s;
            reverse(s.begin(),s.end());
            cnt=vector<int>(k);
            ru(i,0,n){
                string t; cin>>t; reverse(t.begin(),t.end());
                ru(j,0,k) cnt[j]+=t[j]-'0';
            }
            memo=vector<vector<bool>>(k, vector<bool>(n, false));
            res=""; rec(0,0);
            if(res.empty()) cout<<"-1\n";
            else cout<<res<<endl;
        }
    }
};
struct h{
    void solve(){
        cout<<"? aa"<<endl;
        int p,v[10]; cin>>p; p--;
        cout<<"? zzzzz"<<endl;
        int hsh,hsho; ll nom=0,cnt=1; cin>>hsh; hsho=hsh;hsh++;
        ru(i,0,10) {
            nom+=26*cnt; cnt*=p; v[i]=26-(hsh%p); hsh/=p;
        }
        string s; cnt=1; ll ch=0;
        ru(i,0,10){
            if(v[i]<1){v[i]=26; v[i+1]--;}
            ch+=cnt*v[i]; cnt*=p; s+='a'+(v[i]-1);
        }
        cout<<"?"<<s<<endl;
        int ans; cin>>ans;
        cout<<"!"<<p<<' '<<ans+nom-ch-hsho<<endl;
    }
    int main(){
        int t; cin>>t; while(t--) solve();
    }
};

int main(){
    a a;
    a.main();

}