#include <bits/stdc++.h>
//#include <codecvt>

#define ru(i,l,r) for(int i=(l);i<=(r);i++)
#define rd(i,r,l) for(int i=(r);i>=(l);i--)
#define ll long long

using namespace std;

struct a{
    static const int SIZE=1e4+10;
    struct seg{
        int l,r; ll sum,add;
#define l(x) tree[x].l
#define r(x) tree[x].r
#define sum(x) tree[x].sum
#define add(x) tree[x].add
    }tree[SIZE*4];
    int a[SIZE],n,m;

    void build(int p,int l,int r){
        l(p)=l,r(p)=r;
        if(l==r) { sum(p)=a[l]; return; }
        int mid=(l+r)/2;
        build(p*2,l,mid);
        build(p*2+1,mid+1,r);
        sum(p)=sum(p*2)+sum(p*2+1);
    }
    void spread(int p){
        if(add(p)){
            sum(p*2)+=add(p)*(r(p*2)-l(p*2)+1);
            sum(p*2+1)+=add(p)*(r(p*2+1)-l(p*2+1)+1);
            add(p*2)+=add(p);
            add(p*2+1)+=add(p);
            add(p)=0;
        }
    }
    void change(int p,int l,int r,int z){
        if(l<=l(p)&&r>=r(p)){
            sum(p)+=(long long)z*(r(p)-l(p)+1);
            add(p)+=z;return;}
        spread(p);
        int mid=(l(p)+r(p))/2;
        if(l<=mid) change(p*2,l,r,z);
        if(r>mid) change(p*2+1,l,r,z);
        sum(p)=sum(p*2)+sum(p*2+1);
    }
    ll ask(int p,int l,int r){
        if(l<=l(p)&&r>=r(p)) return sum(p);
        spread(p);
        int mid=(l(p)+r(p))/2;
        ll ans=0;
        if(l<=mid) ans+=ask(p*2,l,r);
        if(r>mid) ans+=ask(p*2+1,l,r);
        return ans;
    }
    int main(){
        cin>>n>>m; ru(i,1,n)scanf("%d",&a[i]);
        build(1,1,n);
        while(m--){
            char op[2]; int x,y,z;
            scanf("%s%d%d",op,&x,&y);
            if(op[0]=='C'){scanf("%d",&z);change(1,x,y,z);}
            else printf("%I64d\n", ask(1,x,y));
        }
    }
};

int main(){
//    a a;
//    a.main();
    cout<<"test"<<endl;

    // anonymous func
    vector<int> a={1,2,3};
    auto t1=[&](vector<int> arr) ->void{for(auto x:arr)cout<<x<<" ";cout<<endl;}; t1(a);
    function<void(int)> dfs=[&](int u){for(auto v:a) dfs(v);};

    // vector
    a.push_back(4); t1(a);
    a.pop_back();t1(a);
    a.emplace_back(1ll);


    // priority queue
    priority_queue<vector<int>> pq;
    priority_queue<array<int, 3>> pq1;
    pq.push({a});
    pq1.push({a[0],a[1],a[2]});
    auto[x1,x2,x3]=pq1.top();
    auto x=pq.top();
    typeid(x);

    // hash
    pair<int,int> pi={1,2};
    cout<<pi.first<<" "<<pi.second<<endl;

    // for range, 0 <; 1 <=
    int b[]={1,2,3};
    for(int i=0;i<3;i++){
        cout<<b[i]<<" ";
    }; cout<<endl;

    // count
    string s="abc";
    int cnt=count(s.begin(),s.end(),'a'); cout<<cnt<<endl;

    // accumulate
    cout<<"accumulate([1,2,3]) is: "<<accumulate(a.begin(),a.end(),0); cout<<endl;
    // partial_sum
    auto c = partial_sum(a.begin()+1, a.end()-1, a.begin()+1);
    // upper_bound

    // *min_element
    cout<<min(1,2)<<endl;

    // fill
    int d[10]={}; fill(d,d+4,1); cout<<"fill is: ";
    for(int x:d) cout<<x<<' '; cout<<endl;

    // put, putchar
    putchar('putex');putchar('\n'); puts("puts's exp");

    // sort
    vector<int> e ={4,3,2,1};
    sort(e.begin(),e.end(), [&](int a,int b){return a>b;});
    for(auto i:e) cout<<i<<" "; cout<<endl;
    vector<pair<int,int>> f={{1,2},{2,4},{2,3}};
    for(auto i:f) cout<<i.first<<":"<<i.second<<", "; cout<<endl;
    sort(f.begin(),f.end(),[&](pair<int,int> a,pair<int,int> b){return a.first==b.first?a.second<b.second:a.first<b.first;});
    for(auto i:f) cout<<i.first<<":"<<i.second<<", "; cout<<endl;

    // iota, atoi,
    vector<int> g={4,3,2,1};
    iota(g.begin(), g.end(),0);
    cout<<atoi("abc")<<endl;
//    cout<<strtol(reinterpret_cast<const char *>('a'), reinterpret_cast<char **>('b'), 1);

    // int, float
    cout<< 1<<endl;
    cout<< (ll)(1<<20) <<endl;
    cout<< (ll)1<<20<<endl;

    // cout<<el<<"\n"[i==n-1] 打印所有元素后换行
    for(int i=0; i<g.size();i++) cout<<g[i]<<"\n"[i==g.size()-1];

    // multiset
    multiset<int> h ={1,2,3,'a'}; set<int>h1={1,2,3,'a'};


    // move
    cout<<endl; queue<int> i={}; i.emplace(1);
    cout<<"move test: "<< i.front() <<endl;

}

