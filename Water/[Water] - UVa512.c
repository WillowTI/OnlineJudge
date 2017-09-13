可以把所有的操作对表格都模拟一遍，然后一一查询。
也可以对单个点进行模拟，这里采用第二种方法，因为比较容易实现。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct
{
    char op[5];
    int r1,r2,c1,c2;
    int num,id[15];
}NODE;

NODE cmd[10000];

int r,c,cmdsize;

int simulate(int * a,int * b);

int main()
{
    int cas=1;
    //freopen("input.txt","r",stdin);
    while (scanf("%d%d",&r,&c)!=-1 && r)
    {
        scanf("%d",&cmdsize);
        for (int i=0 ; i<cmdsize ; i++)
        {
            scanf("%s",cmd[i].op);
            if (cmd[i].op[0]=='E') scanf("%d%d%d%d",&cmd[i].r1,&cmd[i].c1,&cmd[i].r2,&cmd[i].c2);
            else
            {
                scanf("%d",&cmd[i].num);
                for (int j=0 ; j<cmd[i].num ; j++) scanf("%d",&cmd[i].id[j]);
            }
        }
        if (cas>1) printf("\n");
        printf("Spreadsheet #%d\n",cas++);
        int queries;
        scanf("%d",&queries);
        for (int i=0 ; i<queries ; i++)
        {
            int r0,c0;
            scanf("%d%d",&r0,&c0);
            printf("Cell data in (%d,%d) ",r0,c0);
            int flag=simulate(&r0,&c0);
            if (flag==0) printf("GONE\n");
            else printf("moved to (%d,%d)\n",r0,c0);
        }
    }
    return 0;
}

int simulate(int * a,int * b)
{
    for (int i=0 ; i<cmdsize ; i++)
    {
        if (cmd[i].op[0]=='E')
        {
            if (cmd[i].r1==*(a) && cmd[i].c1==*(b)) {*a=cmd[i].r2;*b=cmd[i].c2;}
            else if (cmd[i].r2==*(a) && cmd[i].c2==*(b)) {*a=cmd[i].r1;*b=cmd[i].c1;}
        }
        else
        {
            int deltax=0,deltay=0;
            for (int j=0 ; j<cmd[i].num ; j++)
            {
                if (cmd[i].op[0]=='I')
                {
                    if (cmd[i].op[1]=='R' && cmd[i].id[j]<=*a) deltax++;
                    else if (cmd[i].op[1]=='C' && cmd[i].id[j]<=*b) deltay++;
                }
                else if (cmd[i].op[0]=='D')
                {
                    if (cmd[i].op[1]=='R' && cmd[i].id[j]==*a) return 0;
                    else if (cmd[i].op[1]=='C' && cmd[i].id[j]==*b) return 0;
                    if (cmd[i].op[1]=='R' && cmd[i].id[j]<*a) deltax--;
                    else if (cmd[i].op[1]=='C' && cmd[i].id[j]<*b) deltay--;
                }
            }
            (*a)+=deltax;
            (*b)+=deltay;
        }
    }
    return 1;
}
