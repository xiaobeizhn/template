#include<bits/stdc++.h>
#define N 1000005
#define LL long long
using namespace std;
template<typename T>
const T & Max(const T &a,const T &b){
    return a>b?a:b;
}
template<typename T>
const T & Min(const T &a,const T &b){
    return a<b?a:b;
}
int n,m;
int SA[N],subSA[N],cnt[N],RK[2][N];
char str[N];
int main(){
    scanf("%s",str+1);
    n=strlen(str+1);
    bool cur=0;
    for(int i=1;i<=n;i++)cnt[str[i]]++,m=Max((int)str[i],m);
    for(int i=1;i<=m;i++)cnt[i]+=cnt[i-1];
    for(int i=1;i<=n;i++)RK[cur][i]=cnt[str[i]];
    for(int i=n;i>0;i--)SA[cnt[str[i]]--]=i;
    for(int j=1;j<=n;j<<=1,cur^=1){
        int p=0;
        for(int i=n-j+1;i<=n;i++)subSA[++p]=i;
        for(int i=1;i<=n;i++)if(SA[i]>j)subSA[++p]=SA[i]-j;
        memset(cnt,0,sizeof cnt);
        for(int i=1;i<=n;i++)cnt[RK[cur][i]]++;
        for(int i=1;i<=n;i++)cnt[i]+=cnt[i-1];
        for(int i=n;i>0;i--)SA[cnt[RK[cur][subSA[i]]]--]=subSA[i];
        // printf("SA");for(int i=1;i<=n;i++)cout<<SA[i]<<" ";puts("");
        p=1,RK[cur^1][SA[1]]=1;
        for(int i=2;i<=n;i++){
            if(RK[cur][SA[i]]==RK[cur][SA[i-1]]&&RK[cur][subSA[i]]==RK[cur][subSA[i-1]])RK[cur^1][SA[i]]=p;
            else RK[cur^1][SA[i]]=++p;
        }
        if(p==n){
            cur^=1;
            break;
        }
    }
    for(int i=1;i<=n;i++)SA[RK[cur][i]]=i;
    for(int i=1;i<n;i++)printf("%d ",SA[i]);printf("%d",SA[n]);
    return 0;
}