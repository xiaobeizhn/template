#include<bits/stdc++.h>
#define N 10005
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

//小根堆
template<class T>
class Priority_queue{
    private:
        T *data;
        int sz,capacity;
        void Up(int now){
            T res=data[now];
            while(now>1 && data[now>>1]>data[now])data[now]=data[now>>1],now>>=1;
            data[now]=res;
        }
        void Down(int now){
            T res=data[now];
            while((now<<1)<=sz && data[now<<1]<data[now])
                if(now<<1|1<=sz && data[now<<1]<data[now<<1|1])data[now]=data[now<<1],now<<=1;
                else data[now]=data[now<<1|1],now=now<<1|1;
            data[now]=res;
        }
    public:
        Priority_queue(T *_data){
            capacity=sizeof(data)/sizeof(int);
            data=new T[capacity];
            sz=0;
        }
        Priority_queue(int _c){
            data=new T[_c];
            capacity=_c;
            sz=0;
        }
        Priority_queue(){
            data=new T[N];
            capacity=N;
            sz=0;
        }
        ~Priority_queue(){
            delete[] data;
        }
        void clear(){
            memset(data,0,sizeof data);
            sz=0;
        }
        void pop(){
            data[1]=data[sz--];
            Down(1);
        }
        void push(int x){
            data[++sz]=x;
            Up(sz);
        } 
        int top(){
            return data[1];
        }
};

Priority_queue<int>Q;

int main(){
    // freopen("C:/Users/zhn/vscode file/helloworld/in.txt","r",stdin);
    Q.push(3);
    Q.push(1);
    Q.push(4);
    cout<<Q.top()<<endl;
    Q.pop();
    cout<<Q.top()<<endl;
    Q.pop();
    Q.push(2);
    cout<<Q.top()<<endl;
    Q.clear();
    Q.push(3);
    cout<<Q.top()<<endl;
    return 0;
}