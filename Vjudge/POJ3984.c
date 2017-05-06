POJ-3984 迷宫问题
Description

定义一个二维数组：

int maze[5][5] = {

	0, 1, 0, 0, 0,

	0, 1, 0, 1, 0,

	0, 0, 0, 0, 0,

	0, 1, 1, 1, 0,

	0, 0, 0, 1, 0,

};

它表示一个迷宫，其中的1表示墙壁，0表示可以走的路，只能横着走或竖着走，不能斜着走，要求编程序找出从左上角到右下角的最短路线。
Input

一个5 × 5的二维数组，表示一个迷宫。数据保证有唯一解。
Output

左上角到右下角的最短路径，格式如样例所示。
Sample Input

0 1 0 0 0
0 1 0 1 0
0 0 0 0 0
0 1 1 1 0
0 0 0 1 0
Sample Output

(0, 0)
(1, 0)
(2, 0)
(2, 1)
(2, 2)
(2, 3)
(2, 4)
(3, 4)
(4, 4)


BFS求最短路径。
BFS的思想就是对每一个点搜索，直到找到终点或者无路可走。到达每一个点的路径都能保证是最短路径，所以和也是最短路径。
DFS的思想是递归，一条路走到底。



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct//保存点对
{
    int x,y;
}NODE;

NODE list[100];//存放每一步走过的点，这是一个队列
int pre[100]={0};//用于保存这个点的上一个点
int map[5][5]={{0}};//读入的数据存放在map数组中
int visit[5][5]={{0}};//用于记录这个点是否被访问过，这能保证如果这一条路径要访问另外一条路径已经访问过的点，就说明那一条路径更短
const int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};//四个方向，上、下、左、右
int go(int x,int y);//判断这个点是否能走
void print(int x);//递归输出路径
void bfs();//BFS搜索

int main()
{
    for (int i=0;i<5;i++)
    {
        for (int j=0;j<5;j++)
        {
            scanf("%d",&map[i][j]);
        }
    }
    bfs();

    return 0;
}

void bfs()
{
    int head,tail;
    int curx,cury;
    int tmpx,tmpy;
    head=0;
    tail=1;
    list[0].x=0;
    list[0].y=0;
    pre[0]=-1;//初始化队列
    while (head<tail)//队列的规则是FIFO(First In First Out)
    {
        curx=list[head].x;
        cury=list[head].y;
        if (curx==4&&cury==4)//如果走到终点了就输出。由于题目保证一定有唯一解，所以不需要判断能不能走到终点
        {
            print(head);
            return;
        }
        for (int i=0;i<4;i++)//四个方向逐一搜索
        {
            tmpx=curx+dir[i][0];
            tmpy=cury+dir[i][1];
            if (go(tmpx,tmpy)&&!visit[tmpx][tmpy])//如果这个点可以走而且未被访问过，那就添加到队列尾部
            {
                visit[tmpx][tmpy]=1;//添加的时候就标记为已经访问过了
                list[tail].x=tmpx;
                list[tail].y=tmpy;
                pre[tail]=head;
                tail++;//尾部+1
            }
        }
        head++;
    }
    return;
}

int go(int x,int y)
{
    if (x>=0&&x<5&&y>=0&&y<5&&map[x][y]==0)//如果这个点不越界而且是路的话
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

void print(int x)
{
    int prev=pre[x];
    if (prev==0)
    {
        printf("(0, 0)\n");
        printf("(%d, %d)\n",list[x].x,list[x].y);
        return;
    }
    else
    {
        print(prev);
    }
    printf("(%d, %d)\n",list[x].x,list[x].y);
}
