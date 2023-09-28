## 强连通分量

```c++
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
```

## dijsktra

```c++
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
```

## spfa+费用最少的最短路径

```c++
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


```

## 主席树+离散 求区间第k小的数

```c++
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


```

## 线段树 单点修改区间查询

```c++
#include<bits/stdc++.h>
#define N 50005
#define ll long long
using namespace std;
int n;
ll A[N],sum[N<<2];
void clear(int l,int r,int k){
	if(l==r){
		sum[k]=A[l];
		return;
	}
	int mid=(l+r)>>1;
	clear(l,mid,k<<1);
	clear(mid+1,r,(k<<1)+1);
	sum[k]=sum[k<<1]+sum[(k<<1)+1];
	return;
}
void update(int l,int r,int k,int x,ll add){
	if(l>x||r<x)return;
	if(l<=x&&x<=r){
		sum[k]+=add;
		if(l==x&&r==x)return;
	}
	int mid=l+r>>1;
	update(l,mid,k<<1,x,add);
	update(mid+1,r,(k<<1)+1,x,add);
	return;
}
long long query(int l,int r,int k,int x,int y){
	if(l>y||r<x)return 0;
	if(x<=l&&r<=y)return sum[k];
	int mid=l+r>>1;
	return query(l,mid,k<<1,x,y)+query(mid+1,r,(k<<1)+1,x,y);
}
int main(){
	int T;
	scanf("%d",&T);
	for(int i=1;i<=T;i++){
		printf("Case %d:\n",i);
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			ll x;
			scanf("%lld",&x);
			A[i]=x;
		}
		clear(1,n,1);
		char str[10];
		while(~scanf("%s",str)){
			if(str[0]=='E')break;
			int a,b;
			scanf("%d%d",&a,&b);
			if(str[0]=='A')update(1,n,1,a,(ll)b);
			else if(str[0]=='S')update(1,n,1,a,(ll)-b);
			else printf("%lld\n",query(1,n,1,a,b));
		}
	}
	return 0;
}
```

## 线段树 区间修改区间查询

```c++
#include<cstdio>
#include<algorithm>
#define N 100050
using namespace std;
int n,m;
long long sum[N<<2],add[N<<2],A[N];
long long query(int k,int l,int r,int x,int y){
	if(x<=l&&r<=y)return sum[k]+add[k]*(r-l+1);
	int mid=(l+r)>>1;
	long long res=(min(r,y)-max(l,x)+1)*add[k];
	if(x<=mid)res+=query(k<<1,l,mid,x,y);
	if(y>mid)res+=query(k<<1|1,mid+1,r,x,y);
	return res;
}
void build(int k,int l,int r) {
	if(l==r) {
		sum[k]=A[l];
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	sum[k]=sum[k<<1]+sum[k<<1|1];
}
void update(int k,int l,int r,int x,int y,int v){
	if(x<=l&&r<=y){
		add[k]+=v;
		return;
	}
	sum[k]+=(min(y,r)-max(x,l)+1)*v;
	int mid=(l+r)>>1;
	if(x<=mid)update(k<<1,l,mid,x,y,v);
	if(y>mid)update(k<<1|1,mid+1,r,x,y,v);
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++)scanf("%lld",&A[i]);
	build(1,1,n);
	while(m--){
		char str[5];
		int a,b;
		scanf("%s%d%d",str,&a,&b);
		if(str[0]=='Q')printf("%lld\n",query(1,1,n,a,b));
		else if(str[0]=='C'){
			int c;
			scanf("%d",&c);
			update(1,1,n,a,b,c);
		}
	}
	return 0;
}
```

## DSU 树，每个点上一个颜色。每次询问v对应的子树中，有多少种颜色至少出现k次。

```c++
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

```

## 差分约束系统 选出尽可能少的数，使[ai,bi]内至少ci个数被选出

```c++
#include<cstdio>
#include<vector>
#include<queue>
#define N 50005
using namespace std;
int dis[N],mx=-1,mi=1e6;
bool vis[N];
int s[N],n;
struct e {
	int to,v;
};
vector<e>G[N];
void add(int x,int y,int z){G[x].push_back((e)<%y,z%>);}
int spfa(int s) {
	queue<int>q;
	dis[s]=0,vis[s]=1;
	q.push(s);
	while(q.size()) {
		int x=q.front();
		q.pop();
		vis[x]=0;
		for(int i=0; i<G[x].size(); i++) {
			int y=G[x][i].to;
			int v=G[x][i].v;
			if(dis[y]<dis[x]+v) {
				dis[y]=dis[x]+v;
				if(!vis[y]){
					q.push(y);
					vis[y]=1;
				}
			}
		}
	}
	return dis[mx];
}
int main() {
	scanf("%d",&n);
	for(int i=0; i<n; i++) {
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		add(x,y+1,z);
		if(mi>x)mi=x;
		if(mx<y+1)mx=y+1;
	}
	for(int i=mi;i<=mx;i++){
		dis[i]=-1e9;
		add(i,i+1,0);
		add(i+1,i,-1);
	}
	printf("%d\n",spfa(mi));
	return 0;
}
```

## 后缀排序+LCP

```c++
#include<bits/stdc++.h>
#define N 1000005
#define LL long long
using namespace std;
template<typename T>
const T Max(const T a,const T b){
    return a>b?a:b;
}
int n,m;
int SA[N],subSA[N],cnt[N],RK[2][N];
bool cur=0;
char str[N];
void get_SA(){
    for(int i=1;i<=n;i++)cnt[str[i]]++,m=Max((int)str[i],m);
    for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
    for(int i=1;i<=n;i++)RK[cur][i]=cnt[str[i]];
    for(int i=n;i>0;i--)SA[cnt[str[i]]--]=i;
    for(int j=1;j<n;j<<=1,cur^=1){
        int p=0;
        for(int i=n-j+1;i<=n;i++)subSA[++p]=i;
        for(int i=1;i<=n;i++)if(SA[i]>j)subSA[++p]=SA[i]-j;
        memset(cnt,0,sizeof cnt);
        for(int i=1;i<=n;i++)cnt[RK[cur][i]]++;
        for(int i=1;i<=n;i++)cnt[i]+=cnt[i-1];
        for(int i=n;i>0;i--)SA[cnt[RK[cur][subSA[i]]]--]=subSA[i];
        p=1,RK[cur^1][SA[1]]=1;
        for(int i=2;i<=n;i++){
            if(RK[cur][SA[i]]==RK[cur][SA[i-1]]&&RK[cur][SA[i]+j]==RK[cur][SA[i-1]+j])RK[cur^1][SA[i]]=p;
            else RK[cur^1][SA[i]]=++p;
        }
        if(p==n){
            cur^=1;
            break;
        }
    }
    for(int i=1;i<=n;i++)SA[RK[cur][i]]=i;
}
int height[N];
void LCP(){
    int k=0;
    height[1]=0;
    for(int i=2;i<=n;i++){
        if(k)k--;
        while(SA[i]+k<=n&&SA[i-1]+k<=n&&str[SA[i]+k]==str[SA[i-1]+k])k++;
        height[i]=k;
    }
}
int main(){
    scanf("%s",str+1);
    n=strlen(str+1);
    get_SA();
    LCP();
    return 0;
}

```
