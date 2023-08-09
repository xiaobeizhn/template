#include<bits/stdc++.h>
#define N 1005
#define P 10
#define LL long long
using namespace std;
template <typename T> T Max(T a,T b){
    return a>b?a:b;
}
template <typename T> T Min(T a,T b){
    return a<b?a:b;
}
LL ans;
int n;
struct BigInt{
    int l;
    int A[N];
    void Clear(){
    	l=1;
    	memset(A,0,sizeof A);
    	return ;
	}
    BigInt operator + (const BigInt B)const{
        BigInt X;
        X.Clear();
        X.l=Max(l,B.l);
        for(int i=0;i<X.l;i++){
            X.A[i]+=A[i]+B.A[i];
            if(X.A[i]>=10)X.A[i+1]+=X.A[i]/10,X.A[i]%=10;
        }
        while(X.A[X.l]>0)X.l++;
        return X;
    }
    void Read(){
        string res;
        cin>>res;
        l=res.length();
        for(int i=l-1;i>=0;i--){
            A[l-i-1]=res[i]-'0';
        }
        return ;
    }
    void Print(){
        for(int i=l-1;i>=0;i--)printf("%d",A[i]);
        return ;
    }
}a,b;
int main(){
    int T;
    cin>>T;
    for(int ca=1;ca<=T;ca++){
    	printf("Case %d:\n",ca);
    	a.Clear();
    	b.Clear();
        a.Read();
        b.Read();
        a.Print();
        printf(" + ");
        b.Print();
        printf(" = ");
        (a+b).Print();
        puts("");
        if(ca<T)puts("");
    }
    return 0;
}

