Problem Description
某省自从实行了很多年的畅通工程计划后，终于修建了很多路。不过路多了也不好，每次要从一个城镇到另一个城镇时，都有许多种道路方案可以选择，而某些方案要比另一些方案行走的距离要短很多。这让行人很困扰。

现在，已知起点和终点，请你计算出要从起点到终点，最短需要行走多少距离。


Input
本题目包含多组数据，请处理到文件结束。
每组数据第一行包含两个正整数N和M(0<N<200,0<M<1000)，分别代表现有城镇的数目和已修建的道路的数目。城镇分别以0～N-1编号。
接下来是M行道路信息。每一行有三个整数A,B,X(0<=A,B<N,A!=B,0<X<10000),表示城镇A和城镇B之间有一条长度为X的双向道路。
再接下一行有两个整数S,T(0<=S,T<N)，分别代表起点和终点。


Output
对于每组数据，请在一行里输出最短需要行走的距离。如果不存在从S到T的路线，就输出-1.


Sample Input
3 3
0 1 1
0 2 3
1 2 1
0 2
3 1
0 1 1
1 2


Sample Output
2
-1

分析：
可能会输入重复的路径，要更新为最小的。
建立二维数组，这是一个关于主对角线对称的矩阵，主对角线上的元素都是0。
如果两个点之间没有路径，设置为-1。

Floyd:
三重循环。
主循环：从0到n一一设置中转站。(k)
内部二重循环：以i<->j为例，比较i<->k+j<->k的距离和i<->j。
当中转走法合法而直接走不合法或者中转走法更近时，更新。

最后，当要求的两点之间的距离大于0小于(n-1)*10000时，输出P(i,j)。
否则，说明不能走，输出-1。

Floyd算法的时间复杂度很大，这道题200*200*200还行，可以暴力做。


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int n,m,town[205][205]={{0}};

void Floyd();


int main()
{
    while (scanf("%d%d",&n,&m)!=EOF)
    {

        memset(town,0,sizeof(town));

        for (int i=0;i<m;i++)
        {
            int x,y,dis;
            scanf("%d%d%d",&x,&y,&dis);
            if (town[x][y]==0) town[y][x]=town[x][y]=dis;//坑点
            else town[y][x]=town[x][y]=town[x][y]<dis?town[x][y]:dis;
        }

        for (int i=0;i<n;i++)
        {
            for (int j=0;j<n;j++)
            {
                if (i!=j&&town[i][j]==0) town[i][j]=-1;
            }
        }

        Floyd();

        int st,end;

        scanf("%d%d",&st,&end);

        if (town[st][end]>=0&&town[st][end]<(n-1)*10000) printf("%d\n",town[st][end]);
        else printf("-1\n");
    }




    return 0;
}

void Floyd()
{
    for (int k=0;k<n;k++)
    {
        for (int i=0;i<n;i++)
        {
            for (int j=0;j<n;j++)
            {
                if (town[i][k]!=-1&&town[j][k]!=-1)
                {
                    if (town[i][j]==-1||(town[i][j]!=-1&&town[i][k]+town[j][k]<town[i][j]))
                        town[j][i]=town[i][j]=town[i][k]+town[j][k];
                }
            }
        }
    }
}




Dijkstra：
分析：
Dijkstra的思路是从单源点辐射，找出离该源点的最近点。
然后以该点为下一个起点，循环。

该版本的Dijkstra的时间复杂度为O(n^2)。

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
