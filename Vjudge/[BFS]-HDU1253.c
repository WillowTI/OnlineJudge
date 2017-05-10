Problem Description
Ignatius被魔王抓走了,有一天魔王出差去了,这可是Ignatius逃亡的好机会.

魔王住在一个城堡里,城堡是一个A*B*C的立方体,可以被表示成A个B*C的矩阵,刚开始Ignatius被关在(0,0,0)的位置,离开城堡的门在(A-1,B-1,C-1)的位置,现在知道魔王将在T分钟后回到城堡,Ignatius每分钟能从一个坐标走到相邻的六个坐标中的其中一个.现在给你城堡的地图,请你计算出Ignatius能否在魔王回来前离开城堡(只要走到出口就算离开城堡,如果走到出口的时候魔王刚好回来也算逃亡成功),如果可以请输出需要多少分钟才能离开,如果不能则输出-1.



 

Input
输入数据的第一行是一个正整数K,表明测试数据的数量.每组测试数据的第一行是四个正整数A,B,C和T(1<=A,B,C<=50,1<=T<=1000),它们分别代表城堡的大小和魔王回来的时间.然后是A块输入数据(先是第0块,然后是第1块,第2块......),每块输入数据有B行,每行有C个正整数,代表迷宫的布局,其中0代表路,1代表墙.(如果对输入描述不清楚,可以参考Sample Input中的迷宫描述,它表示的就是上图中的迷宫)

特别注意:本题的测试数据非常大,请使用scanf输入,我不能保证使用cin能不超时.在本OJ上请使用Visual C++提交.
 

Output
对于每组测试数据,如果Ignatius能够在魔王回来前离开城堡,那么请输出他最少需要多少分钟,否则输出-1.
 

Sample Input
1
3 3 4 20
0 1 1 1
0 0 1 1
0 1 1 1
1 1 1 1
1 0 0 1
0 1 1 1
0 0 0 0
0 1 1 0
0 1 1 0
 

Sample Output
11




#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

typedef struct
{
    int x,y,z,step;
}NODE;


int migong[55][55][55]={{{0}}};
int a,b,c,t;
int head=0;
int tail=1;
int vis[55][55][55]={{{0}}};
const int dirx[6]={0,0,1,-1,0,0};
const int diry[6]={0,0,0,0,-1,1};
const int dirz[6]={-1,1,0,0,0,0};
NODE Q[22500];

void BFS();
int isvalid(int x,int y,int z);

int main()
{
    int cas;
    scanf("%d",&cas);
    for (int m=0;m<cas;m++)
    {
        memset(vis,0,sizeof(vis));
        head=0;
        tail=1;
        scanf("%d%d%d%d",&a,&b,&c,&t);
        for (int i=0;i<a;i++)
        {
            for (int j=0;j<b;j++)
            {
                for (int k=0;k<c;k++)
                {
                    scanf("%d",&migong[i][j][k]);
                }
            }
        }
        NODE tmp;
        tmp.x=0;
        tmp.y=0;
        tmp.z=0;
        tmp.step=0;
        Q[0]=tmp;
        BFS();
    }



    return 0;
}

void BFS()
{
    int curx,cury,curz;
    int curstep;
    while (head<tail)
    {
        NODE cur=Q[head];
        head++;
        curx=cur.x;
        cury=cur.y;
        curz=cur.z;
        curstep=cur.step;
        if (curx==a-1&&cury==b-1&&curz==c-1)
        {
            if (curstep<=t)
            {
                printf("%d\n",curstep);
            }
            else
            {
                printf("-1\n");
            }
            return ;
        }
        for (int i=0;i<6;i++)
        {
            int sx=curx+dirx[i];
            int sy=cury+diry[i];
            int sz=curz+dirz[i];
            int st=curstep+1;
            if (isvalid(sx,sy,sz))
            {
                Q[tail].x=sx;
                Q[tail].y=sy;
                Q[tail].z=sz;
                Q[tail].step=st;
                vis[sx][sy][sz]=1;
                tail++;
            }
        }
    }
    printf("-1\n");
    return ;
}


int isvalid(int x,int y,int z)
{
    if (x>=0&&x<a&&y>=0&&y<b&&z>=0&&z<c&&!vis[x][y][z]&&migong[x][y][z]==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
