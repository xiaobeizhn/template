#include<bits/stdc++.h>
#define N 100005
using namespace std;
int n,m,Dfn,cnt[N],col[N],ans[N],res[N];
int id[N],L[N],R[N],son[N],sz[N];
struct ask {
	int k,id;
};
vector<int>G[N];
vector<ask>Q[N];
void dfs(int x,int fa) {
	sz[x]=1,L[x]=++Dfn,id[Dfn]=x;
	for(int i=0; i<G[x].size(); i++) {
		int y=G[x][i];
		if(y==fa)continue;
		dfs(y,x);
		sz[x]+=sz[y];
		if(sz[son[x]]<sz[y])son[x]=y;
	}
	R[x]=Dfn;
}
void del(int x) {
	for(int i=L[x]; i<=R[x]; i++) {
		int t=id[i];
		--res[cnt[col[t]]--];
	}
}
void add(int x) {
	for(int i=L[x]; i<=R[x]; i++) {
		int t=id[i];
		++res[++cnt[col[t]]];
	}
}
void query(int x,int fa) {
	for(int i=0; i<G[x].size(); i++) {
		int y=G[x][i];
		if(y==fa||y==son[x])continue;
		query(y,x);
		del(y);
	}
	if(son[x])query(son[x],x);
	for(int i=0; i<G[x].size(); i++) {
		int y=G[x][i];
		if(y==fa||y==son[x])continue;
		add(y);
	}
	++res[++cnt[col[x]]];
	for(int i=0; i<Q[x].size(); i++)ans[Q[x][i].id]=res[Q[x][i].k];
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++)scanf("%d",&col[i]);
	for(int x,y,i=1; i<n; i++) {
		scanf("%d%d",&x,&y);
		G[x].push_back(y);
		G[y].push_back(x);
	}
	for(int i=1; i<=m; i++) {
		int x,y;
		scanf("%d%d",&x,&y);
		Q[x].push_back((ask)<%y,i%>);
	}
	dfs(1,0);
	query(1,0);
	for(int i=1; i<=m; i++)printf("%d\n",ans[i]);
	return 0;
}
