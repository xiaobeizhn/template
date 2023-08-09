int n,m,s,t;
int head[N],nxt[N<<1],to[N<<1],linecnt;
int cur[N];
LL val[N<<1];
void add(int x,int y,LL z){
    nxt[linecnt]=head[x],val[linecnt]=z,to[linecnt]=y,head[x]=linecnt++;
}
LL Ans;
int dis[N];
int L,R,Q[N<<1];
int bfs(){
    memset(dis,-1,sizeof dis);
    dis[s]=0;
    Q[R++]=s;
    while(L<R){
        int x=Q[L++];
        for(int i=head[x];i!=-1;i=nxt[i]){
            int y=to[i];
            if(dis[y]!=-1&&val[i]>0){
                dis[y]=dis[x]+1;
                Q[R++]=y;
            }
        }
    }
    return dis[t]!=-1;
}
LL dfs(int x,LL flow){
    LL tot=flow;
    for(int i=head[x];i!=-1;i=nxt[i]){
        int y=to[i];
        if(dis[y]==dis[x]+1&&val[i]>0){
            int res=dfs(y,Min(val[i],tot));
            tot-=res;
            val[i]-=res;
            val[i^1]+=res;
            if(tot==0)break;
        }
    }
    return flow-tot;
}
int main(){
    scanf("%d%d%d%d",&n,&m,&s,&t);
    memset(head,-1,sizeof head);
    for(int i=0;i<m;i++){
        int a,b;
        LL c;
        scanf("%d%d%lld",&a,&b,&c);
        add(a,b,c),add(b,a,0);
    }
    while(bfs()){
        memcpy(cur,head,sizeof head);
        Ans+=dfs(s);
    }
    printf("%lld\n",Ans);
    return 0;
}
