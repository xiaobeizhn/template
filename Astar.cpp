#include<bits/stdc++.h>
#define LL long long
#define N 23
using namespace std;
template<typename T>
T Abs(T a){
    return a>0?a:-a;
}
int n,m;//行，列
int bx,by,ex,ey;//起点和终点的坐标
struct node{
    int x,y,d;
    inline int h()const {
        return Abs(ex-x)+Abs(ey-y);
    }
    //利用曼哈顿距离估计该点h(x)值
    inline int g()const {
        return d;
    }
    bool operator < (const node &_)const{
        return d+h()>_.d+_.h();
    }
    void Print(){
        cout<<x<<" "<<y<<" "<<g()<<" "<<h()<<endl;
    }
};
int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};
char mp[N][N];

priority_queue<node>OPEN;
bool CLOSE[N][N];
int Ans;

//读入数据
void Init(){
    puts("输入地图行数和列数");
    scanf("%d%d",&n,&m);
    puts("障碍物 #   路 .   起点 A   终点 B");
    for(int i=1;i<=n;i++){
        scanf("%s",mp[i]+1);
        for(int j=1;j<=m;j++){
            if(mp[i][j]=='A')bx=i,by=j;
            else if(mp[i][j]=='B')ex=i,ey=j;
        }
    }
    return ;
}

void Clear(){
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)CLOSE[i][j]=0;
    while(OPEN.size())OPEN.pop();
    Ans=-1;//初始化为无法到达状态
    return ;
}

// void Show_map(node now){
//     for(int i=1;i<=n;i++){
//         for(int j=1;j<=m;j++){
//             if(i==now.x&&j==now.y)putchar('*');
//             else printf("%c",mp[i][j]);
//         }
//         puts("");
//     }
//     puts("");
// }

void Astar(){
    OPEN.push((node)<%bx,by,0%>);
    CLOSE[bx][by]=1;
    while(OPEN.size()>0){
        node now=OPEN.top();
        OPEN.pop();
        // now.Print();
        // Show_map(now);
        for(int i=0;i<4;i++){
            node nxt=(node)<%now.x+dx[i],now.y+dy[i],now.d+1%>;
            if(nxt.x<1||nxt.x>n||nxt.y<1||nxt.y>m||mp[nxt.x][nxt.y]=='#'||CLOSE[nxt.x][nxt.y])continue;
            if(nxt.x==ex&&nxt.y==ey){
                Ans=nxt.d;//广度优先搜索，最先找到的路径最短
                return ;
            }
            CLOSE[nxt.x][nxt.y]=1;
            OPEN.push(nxt);
        }
    }
}

int main(){
    Init();
    // puts("");
    Clear();
    Astar();
    if(Ans==-1)cout<<"无法到达"<<endl;
    else cout<<Ans<<endl;
    return 0;
}