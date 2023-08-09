#include<bits/stdc++.h>
#define N 100005
#define LL long long
using namespace std;
template <typename T> T Max(T a,T b){
    return a>b?a:b;
}
template <typename T> T Min(T a,T b){
    return a<b?a:b;
}
struct side{
    int y;
    int v;
};
int dfn[N],low[N],Dfn;
int st,stk[N];
int g[N],gcnt;
vector<side>V[N];
vector<side>G[N];
void Tarjan(int x){
    dfn[x]=low[x]=++Dfn;
    stk[++st]=x;
    for(int i=0;i<G[x].size();i++){
        int y=G[x][i].y;
        if(!dfn[y]){
            Tarjan(y);
            low[x]=Min(low[x],low[y]);
        }else if(!g[x]){
            low[x]=Min(low[x],dfn[y]);
        }
    }
    if(low[x]==dfn[x]){
        ++gcnt;
        do{
            g[stk[st]]=gcnt;
        }while(stk[st--]!=x);
    }
}
void side_rebuild(){
    for(int x=1;x<=n;x++){
        for(int i=0;i<G[x].size();i++){
            int y=G[x][i].y;
            if(g[x]!=g[y]){
                V[g[x]].push_back(g[y]);
            }
        }
    }
}
