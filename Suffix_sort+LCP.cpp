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
    for(int j=1;j<n;j<<=1){
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
        cur^=1;
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
    for(int i=1;i<=n;i++){
        if(RK[cur][i]==1)k=0;
        else {
            if(k)k--;
            int j=SA[RK[cur][i]-1];
            while(i+k<=n&&j+k<=n&&str[i+k]==str[j+k])k++;
            height[RK[cur][i]]=k;
        }
    }
}
int main(){
    scanf("%s",str+1);
    n=strlen(str+1);
    get_SA();
    LCP();
    return 0;
}
