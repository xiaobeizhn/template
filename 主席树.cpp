#include<bits/stdc++.h>
#define N 100005
#define LL long long
using namespace std;
int n,m,A[N],B[N];
int tid,root[N],L[N<<5],R[N<<5],Sum[N<<5];
void Update(int &now,int old,int l,int r,int x){
    now=++tid;
    Sum[now]=Sum[old]+1;
    if(l==r)return ;
    L[now]=L[old];
    R[now]=R[old];
    int mid=l+r>>1;
    if(x<=mid)Update(L[now],L[old],l,mid,x);
    else Update(R[now],R[old],mid+1,r,x);
}
int Query(int l,int r,int lt,int rt,int k){
    if(l==r)return B[l];
    int cnt=Sum[L[rt]]-Sum[L[lt]];
    int mid=l+r>>1;
    if(cnt<k)return Query(mid+1,r,R[lt],R[rt],k-cnt);
    else return Query(l,mid,L[lt],L[rt],k);
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        tid=0;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)scanf("%d",&A[i]),B[i]=A[i];
        sort(B+1,B+1+n);
        int t=unique(B+1,B+1+n)-B-1;
        for(int i=1;i<=n;i++){
            int res=lower_bound(B+1,B+1+t,A[i])-B;
            Update(root[i],root[i-1],1,t,res);
        }
        while(m--){
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);
            printf("%d\n",Query(1,t,root[a-1],root[b],c));
        }
    }
    return 0;
}

