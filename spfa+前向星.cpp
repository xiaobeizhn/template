#include<bits/stdc++.h>
#define N 1005
#define M 100005
#define ll long long
using namespace std;
template <typename T> T Max(T a,T b){
    return a>b?a:b;
}
template <typename T> T Min(T a,T b){
    return a<b?a:b;
}
int n,m;
int head[M],nxt[M],to[M],lcnt;
ll len[M],cost[M];
ll dis[N],val[N];
int S,T;
void ladd(int x,int y,ll d,ll p){
    nxt[++lcnt]=head[x],to[lcnt]=y,head[x]=lcnt,len[lcnt]=d,cost[lcnt]=p;
}
int st[N];
queue<int>q;
void spfa(){
    memset(st,0,sizeof st);
    memset(dis,0x3f,sizeof dis);
    memset(val,0,sizeof val);
    q.push(S);
    st[S]=1;
    dis[S]=0;
    while(q.size()){
        int x=q.front();
        q.pop();
        st[x]=0;
        for(int i=head[x];i;i=nxt[i]){
            int y=to[i];
            if(dis[y]>dis[x]+len[i]){
                dis[y]=dis[x]+len[i];
                val[y]=val[x]+cost[i];
                if(!st[y]){
                    st[y]=1;
                    q.push(y);
                }
            }else if(dis[y]==dis[x]+len[i]){
                if(val[y]>val[x]+cost[i]){
                    val[y]=val[x]+cost[i];
                    if(!st[y]){
                        st[y]=1;
                        q.push(y);
                    }
                }
            }
        }
    }
}
int main(){
	freopen("try.txt","r",stdin);
    while(1){
        scanf("%d%d",&n,&m);
        if(n==0&&m==0)return 0;
        memset(head,0,sizeof head);
        lcnt=0;
        for(int i=0;i<m;i++){
            int a,b;
			ll d,p;
            scanf("%d%d%lld%lld",&a,&b,&d,&p);
            ladd(a,b,d,p);
            ladd(b,a,d,p);
        }
        scanf("%d%d",&S,&T);
        spfa();
//        if(dis[T]==0x3f3f3f3f3f3f3f3f)puts("-1");
        printf("%lld %lld\n",dis[T],val[T]);
    }
    return 0;
}

