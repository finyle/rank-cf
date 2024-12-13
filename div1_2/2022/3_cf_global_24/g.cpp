#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int n;
int query(int l,int r,int k){
    printf("? %d %d %d\n",l,r,k);
    fflush(stdout);int re;scanf("%d",&re);
    return re;
}
void answer(int x){
    printf("! %d\n",x);
    fflush(stdout);
}
int rt=-1;
void divide(int l,int r,int l1,int l2,int r1,int r2){
    if(l==r){
        answer(l);
        return;
    }
    if(l+1==r){
        if(r1==r2+1){
            if(query(r,n,2)==r2+1)answer(r);
            else answer(l);
        }
        else if(l1==l2+1){
            if(query(1,l,2)==l2+1)answer(l);
            else answer(r);
        }
        else{
            if(l>1){
                if(query(1,l,n)==2)answer(r);
                else answer(l);
            }
            else{
                if(query(r,n,n)==2)answer(l);
                else answer(r);
            }
        }
        return;
    }
    int mid=(l+r)>>1;
    int L=query(1,mid,2),R=query(mid+1,n,2);
    if(L*2-mid>R*2-(n-mid))divide(l,mid,L,l2,r1,R);
    else if(L*2-mid<R*2-(n-mid))divide(mid+1,r,l1,L,R,r2);
    else{
        if(~rt){
            if(rt)divide(l,mid,L,l2,r1,R);
            else divide(mid+1,r,l1,L,R,r2);
        }
        if(query(1,mid,n)==2)rt=0,divide(mid+1,r,l1,L,R,r2);
        else rt=1,divide(l,mid,L,l2,r1,R);
    }
}
int main(){
    scanf("%d",&n);
    divide(1,n,n/2+1,0,n/2+1,0);
    return 0;
}

//5
//
//2
//
//2
//
//1
//
//3