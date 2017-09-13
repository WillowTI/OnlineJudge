BFS模板题
6个操作：
灌满A
灌满B
倒空A
倒空B
A倒到B
B倒到A

最后输出每一步的操作

这道题是special judge
只要最后能成功就行
张臻炜同学只用了其中3种操作
连样例都不一样也能过

要点就是套模板

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int a , b , n;
int vis[1005][1005]={{0}};
int prev[1005]={0};
int head = 0;
int tail = 1;

typedef struct
{
    int vola , volb , op;
}NODE;

NODE q[1000 * 1000 + 5];

void BFS();
void print(int x);

int main()
{
    //freopen("input.txt" , "r" , stdin);
    while (scanf("%d%d%d" , &a , &b , &n) == 3)
    {
        memset(vis , 0 , sizeof(vis));
        head = 0;
        tail = 1;
        BFS();
        puts("success");
    }
    return 0;
}

void BFS()
{
    NODE tmp;
    tmp.vola = 0;
    tmp.volb = 0;
    tmp.op = -1;
    prev[0] = -1;
    q[0] = tmp;
    int curvola = 0 , curvolb = 0;
    int tmpa , tmpb;
    while (head < tail)
    {
        curvola = q[head].vola;
        curvolb = q[head].volb;
        if (curvolb == n)
        {
            print(head);
            return ;
        }
        for (int i = 1 ; i <= 6 ; i++)
        {
            if (i == 1)
            {
                tmpa = a;
                tmpb = curvolb;
            }
            else if (i == 2)
            {
                tmpa = curvola;
                tmpb = b;
            }
            else if (i == 3)
            {
                tmpa = 0;
                tmpb = curvolb;
            }
            else if (i == 4)
            {
                tmpa = curvola;
                tmpb = 0;
            }
            else if (i == 5)
            {
                int dis = b - curvolb;
                if (curvola > dis)
                {
                    tmpa = curvola - dis;
                    tmpb = b;
                }
                else
                {
                    tmpa = 0;
                    tmpb = curvolb + curvola;
                }
            }
            else
            {
                int dis = a - curvola;
                if (curvolb > dis)
                {
                    tmpa = a;
                    tmpb = curvolb - dis;
                }
                else
                {
                    tmpa = curvola + curvolb;
                    tmpb = 0;
                }
            }
            if (!vis[tmpa][tmpb])
            {
                vis[tmpa][tmpb] = 1;
                q[tail].vola = tmpa;
                q[tail].volb = tmpb;
                q[tail].op = i;
                prev[tail] = head;
                tail++;
            }
        }
        head++;
    }
    return ;
}

void print(int x)
{
    int pre = prev[x];
    if (pre)
        print(pre);
    if (q[x].op == 1)
        puts("fill A");
    else if (q[x].op == 2)
        puts("fill B");
    else if (q[x].op == 3)
        puts("empty A");
    else if (q[x].op == 4)
        puts("empty B");
    else if (q[x].op == 5)
        puts("pour A B");
    else if (q[x].op == 6)
        puts("pour B A");
}
