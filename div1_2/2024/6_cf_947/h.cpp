#include<bits/stdc++.h>
using namespace std;
struct ch{
    string c;
    ch(){c = "";}
    ch(string cc){c=cc;}
    bool operator == (const ch& p)const{
        return c==p.c;
    }
    bool operator != (const ch& p)const{
        return c!=p.c;
    }
    void add(ch& p){
        c.append(p.c);
    }
};
vector<ch> solve(vector<ch> cs){
    int n = cs.size();
    int t = 0;
    if(cs.empty())return cs;
    for(int i=n-2;i>=0;i--){
        if(cs[i]!=cs[n-1])break;
        t++;
    }
    if(t==0){
        vector<ch> res;
        res.push_back(cs[n-1]);
        return res;
    }
    int p = n-(t+1);
    if(p<=t){
        vector<ch> res;
        vector<ch> nxt;
        int k = (t+1)/(p+1);
        int le = (t+1)%(p+1);
        ch m = cs[n-1];
        for(int j=1;j<k;j++){
            m.add(cs[n-1]);
        }
        for(int i=0;i<p;i++){
            ch tmp = m;
            tmp.add(cs[i]);
            nxt.push_back(tmp);
        }
        for(int i=0;i<le;i++){
            nxt.push_back(cs[n-1]);
        }
        auto nxt_solved = solve(nxt);
        for(auto i:nxt_solved)res.push_back(i);
        res.push_back(m);
        return res;
    }else{
        vector<ch> res;
        vector<ch> nxt;
        ch m = cs[n-1];
        for(int i=0;i<t;i++){
            nxt.push_back(m);
        }
        int now = 0,beg=0;
        for(int i=0;i<p;i++){
            nxt[now].add(cs[i]);
            if(now>=1){
                if(cs[i]!=cs[i-1]){
                    beg=now;
                }
            }
            now++;
            if(now>=t)now=beg;
        }
        auto nxt_solved = solve(nxt);
        for(auto i:nxt_solved)res.push_back(i);
        res.push_back(m);
        return res;
    }
}
vector<ch> trans(string s){
    vector<ch> tmp;
    for(auto i:s){
        string tmpp = "";
        tmpp+=i;
        tmp.push_back(tmpp);
    }
    return tmp;
}
int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        string s;
        cin>>s;
        sort(s.begin(),s.end());
        auto tmp = trans(s);
        auto ans= solve(tmp);
        for(auto c:ans)cout<<c.c;
        cout<<"\n";
    }
}

//6
//3
//qaq
//4
//cccc
//6
//bazoka
//6
//zazzzz
//7
//ababbbb
//7
//ccbabcc
