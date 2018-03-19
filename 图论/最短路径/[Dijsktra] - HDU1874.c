#include <stdio.h>
#include <string.h>
const int inf = 1<<30;//无穷大

int n,m;
int map[300][300];
int vis[300],cast[300];//vis记录当前点是否已经被访问，访问过记为1；反之，记为0。
								 //cast用于表示以s为起点到各个点的最短路径，在循环中会一直改变元素值

void Dijkstra(int s,int e);

int main()
{
    int i,j,x,y,z,start,end;
    while(~scanf("%d%d",&n,&m))
    {
        for(i = 0; i<200; i++)
        {
            for(j = 0; j<200; j++)
                map[i][j] = inf;
            map[i][i] = 0;
        }
        for(i = 0; i<m; i++)
        {
            scanf("%d%d%d",&x,&y,&z);
            if(z<map[x][y])
            map[x][y] = map[y][x] = z;
        }
        scanf("%d%d",&start,&end);
        Dijkstra(start,end);
        printf("%d\n",cast[end]==inf?-1:cast[end]);
    }

    return 0;
}

void Dijkstra(int s,int e)
{
    int min,pos;
    memset(vis,0,sizeof(vis));
    cast[s] = 0;//从s到s一定是0
    vis[s] = 1;//把s标记为已访问
    for(int i = 0;i<n;i++) cast[i] = map[s][i];//把第s行复制到cast数组
    for(int i = 0;i<n;i++)
    {
        min = inf;//初始化比较元素为无穷大
        for(int j = 0;j<n;j++)
        {
            if(cast[j]<min && !vis[j])
            {
                pos = j;
                min = cast[j];
            }
        }
        vis[pos] = 1;//从cast数组中挑选出未访问过，而且距起点最近的点，标记为已访问
        for(int j = 0;j<n;j++)
        {
            if(cast[pos]+map[pos][j]<cast[j] && !vis[j]) cast[j] = cast[pos]+map[pos][j];//以该点为中心，向外辐射，判断是否以该点为中转的路径更短
																																//与Floyd算法类似，也是以某点为中转，比较两条路径。
																																//不同之处在于，Floyd是遍历每一个点，Dijkstra是由近及远遍历
        }
    }
}
