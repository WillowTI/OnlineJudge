Description

Farmer John has been informed of the location of a fugitive cow and wants to catch her immediately. He starts at a point N (0 ≤ N ≤ 100,000) on a number line and the cow is at a point K (0 ≤ K ≤ 100,000) on the same number line. Farmer John has two modes of transportation: walking and teleporting.

* Walking: FJ can move from any point X to the points X - 1 or X + 1 in a single minute
* Teleporting: FJ can move from any point X to the point 2 × X in a single minute.

If the cow, unaware of its pursuit, does not move at all, how long does it take for Farmer John to retrieve it?

Input

Line 1: Two space-separated integers: N and K
Output

Line 1: The least amount of time, in minutes, it takes for Farmer John to catch the fugitive cow.
Sample Input

5 17
Sample Output

4
Hint

The fastest way for Farmer John to reach the fugitive cow is to move along the following path: 5-10-9-18-17, which takes 4 minutes.






#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

const int N = 100100;
int n,k;
typedef struct
{
    int x;
    int step;
}node;

node Q[200100];//数组开到20w是为了防止RunTimeError，因为head和tail递增访问的时候可能会越界
int vis[200100]={0};
int head=0;
int tail=1;


void BFS()//整体思路和迷宫问题一样，用队列实现BFS搜索，只要能理解上一题的做法，这一题也一样
{
    int curx;//当前的位置的步数
    int curstep;
    while (head<tail)
    {
        node cur=Q[head];
        head++;//检查完一个就头指针加一
        curx=cur.x;
        curstep=cur.step;
        if (curx==k)//如果当前的x等于k，就说明找到了，输出步数
        {
            printf("%d\n",curstep);
            return ;
        }
        if (curx>=1&&!vis[curx-1])//一定要保证当前的位置是>=1的，因为这一步搜索是往后一步
        {
            node tmp;
            vis[curx-1]=1;//如果未被搜索过那就标记为已经搜索了，并且添加到队列里
            tmp.x=curx-1;
            tmp.step=curstep+1;
            Q[tail++]=tmp;//尾指针加一
        }
        if (curx<=k&&!vis[curx+1])//走回头路肯定是浪费时间的，而且有可能访问已经访问过的地址，往前一步
        {
            node tmp;
            vis[curx+1]=1;
            tmp.x=curx+1;
            tmp.step=curstep+1;
            Q[tail++]=tmp;
        }
        if (curx<=k&&curx*2<N&&!vis[curx*2])//往前2倍
        {
            node tmp;
            vis[curx*2]=1;
            tmp.x=curx*2;
            tmp.step=curstep+1;
            Q[tail++]=tmp;
        }
    }


}


int main()
{

    while (scanf("%d%d",&n,&k)!=EOF)
    {
        head=0;//读入新数据的时候所有指针，数组复原。队列就不管了，反正是由指针控制的
        tail=1;
        memset(vis,0,sizeof(vis));
        vis[n]=1;
        node t;
        t.x = n, t.step = 0;
        Q[head]=t;
        BFS();
    }


    return 0;
}
