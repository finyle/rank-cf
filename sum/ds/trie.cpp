#include <bits/stdc++.h>
#define ru(i,l,r) for(int i=(l);i<=(r);i++)
#define rd(i,r,l) for(int i=(r);i>=(l);i--)

using namespace std;

struct a{
    static const int SIZE=1e2+10;
    int trie[SIZE*32+5][2], tot=1; int a[SIZE], n, ans;
    void insert(int val){
        int p=1;

        rd(k,30,0){
            int ch=val>>k&1;
            if(trie[p][ch]==0) trie[p][ch]=++tot;
            p=trie[p][ch];
        }
    }
    int search(int val){
        int p=1, ans=0;
        rd(k,30,0){
            int ch=val>>k&1;
            if(trie[p][ch^1]){p=trie[p][ch^1]; ans|=1<<k;}
            else p=trie[p][ch];
        }; return ans;
    }
    int main(){
        cin>>n; ru(i,1,n) {scanf("%d",&a[i]); insert(a[i]); ans=max(ans,search(a[i]));}
        cout<<ans<<endl;
    }
};

struct c{

};

int main(){
    a a;
    a.main();
}