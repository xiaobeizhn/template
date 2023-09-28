#include<bits/stdc++.h>
#define N 1005
#define LL long long
using namespace std;
char A[N],B[N];
int P[N];
int n,m;
int main(){
    while(~scanf("%s%s",A+1,B+1)){
        n=strlen(A+1),m=strlen(B+1);
        P[1]=0;
        int j=0;
        for(int i=2;i<=n;i++){
            while(j>0&&A[j+1]!=A[i])j=P[j];
            if(A[j+1]==A[i])j++;
            P[i]=j;
        }
        j=0;
        for(int i=1;i<=m;i++){
            while(j>0&&A[j+1]!=B[i])j=P[j];
            if(A[j+1]==B[i])j++;
            if(i==m){
                if(j==0)puts("0");
                else {
                    for(int t=1;t<=j;t++)printf("%c",A[t]);
                    putchar(' ');
                    printf("%d\n",j);
                }
            }
        }
    }
    return 0;
}
