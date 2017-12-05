#include <stdio.h>
#include <queue>
#include <string.h>
#include <algorithm>
using namespace std;

const int inf = 1<<30;
const int L = 1000+10;

struct Edges
{
    int x,y,w,next;
};
struct node
{
    int d;
    int u;
    node (int dd = 0,int uu = 0):d(dd),u(uu) {}
    bool operator < (const node &x) const
    {
        return u>x.u;
    }
};

priority_queue<node> Q;
Edges e[L<<2];
int head[L];
int dis[L];
int vis[L];

void AddEdge(int x,int y,int w,int k)
{
    e[k].x = x;
    e[k].y = y;
    e[k].w = w;
    e[k].next = head[x];
    head[x] = k++;
    e[k].x = y;
    e[k].y = x;
    e[k].w = w;
    e[k].next = head[y];
    head[y] = k++;
}

void init(int n,int m)
{
    int i;
    memset(e,-1,sizeof(e));
    for(i = 0; i<n; i++)
    {
        dis[i] = inf;
        vis[i] = 0;
        head[i] = -1;
    }
    for(i = 0; i<2*m; i+=2)
    {
        int x,y,w;
        scanf("%d%d%d",&x,&y,&w);
        AddEdge(x,y,w,i);
    }
}

int Dijkstra(int n,int src)
{
    node mv;
    int i,j,k,pre;
    vis[src] = 1;
    dis[src] = 0;
    Q.push(node(src,0));
    for(pre = src,i = 1; i<n; i++)
    {
        for(j = head[pre]; j!=-1; j=e[j].next)
        {
            k = e[j].y;
            if(!vis[k] && dis[pre]+e[j].w<dis[k])
            {
                dis[k] = dis[pre]+e[j].w;
                Q.push(node(e[j].y,dis[k]));
            }
        }
        while(!Q.empty()&&vis[Q.top().d]==1)
            Q.pop();
        if(Q.empty())
            break;
        mv = Q.top();
        Q.pop();
        vis[pre=mv.d] = 1;
    }
}

int main()
{
    int n,m,x,y;
    while(~scanf("%d%d",&n,&m))
    {
        init(n,m);
        scanf("%d%d",&x,&y);
        Dijkstra(n,x);
        printf("%d\n",dis[y]==inf?-1:dis[y]);
    }

    return 0;
}
