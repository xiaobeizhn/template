#include<bits/stdc++.h>
#define N 100005
#define ll long long
using namespace std;
int n,m;
int s,t;
ll dis[N];
struct node{
    int y;
    ll s;
    bool operator < (const node &a)const{
        return s>a.s;
    }
};
vector<node>G[N];
priority_queue<node>Q;
bool vis[N];
void dij(){
    dis[s]=0;
    Q.push((node)<%s,0%>);
    while(Q.size()){
        node now=Q.top();
        Q.pop();
        int x=now.y;
        if(vis[x])continue;
        vis[x]=1;
        for(int i=0;i<G[x].size();i++){
            int y=G[x][i].y;
            if(dis[y]>dis[x]+G[x][i].s){
                dis[y]=dis[x]+G[x][i].s;
                Q.push((node)<%y,dis[y]%>);
            }
        }
    }
}
int main(){
	freopen("try.txt","r",stdin);
    while(~scanf("%d%d",&n,&m)){
        if(n==0&&m==0)return 0;
        for(int i=1;i<=n;i++)G[i].clear();
        memset(dis,0x3f,sizeof dis);
        memset(vis,0,sizeof vis);
        for(int i=0;i<m;i++){
            int a,b;
            ll s,w;
            scanf("%d%d%lld",&a,&b,&s);
            G[a].push_back((node)<%b,s%>);
            G[b].push_back((node)<%a,s%>);
        }
        dij();
        printf("%lld\n",dis[n]);
    }
    return 0;
}



