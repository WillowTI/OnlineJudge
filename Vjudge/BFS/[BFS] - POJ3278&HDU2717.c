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

node Q[200100];
int vis[200100]={0};
int head=0;
int tail=1;


void BFS()
{
    int curx;
    int curstep;
    while (head<tail)
		{
        node cur=Q[head];
        head++;
        curx=cur.x;
        curstep=cur.step;
        if (curx==k)
        {
            printf("%d\n",curstep);
            return ;
        }
        if (curx-1<N&&curx-1>=0&&!vis[curx-1])
        {
            node tmp;
            vis[curx-1]=1;
            tmp.x=curx-1;
            tmp.step=curstep+1;
            Q[tail++]=tmp;
        }
        if (curx+1<N&&!vis[curx+1])
        {
            node tmp;
            vis[curx+1]=1;
            tmp.x=curx+1;
            tmp.step=curstep+1;
            Q[tail++]=tmp;
        }
        if (curx*2<N&&!vis[curx*2])
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
        head=0;
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
