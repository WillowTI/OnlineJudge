给定6个矩形的长w和宽h（1<=w,h<=1000），判断它们能否构成长方体的6个面

分析：
1.每一个面用NODE表示，输入数据后交换某些数据，确保x<y.
2.优先按照x的递增排序，当x相同时，按照y的递增排序.
3.先比较一对数据的x和y是否全部相等，再判断是否是组成3个不同的面。
设a<b<c，那么排序后应该是
a b
a b
a c
a c
b c
b c
也就是a[0].x=a[2].x，a[0].y=a[4].x，a[2].y=a[4].y。
当以上条件全部满足时才能构成长方体。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct
{
    int x,y;
}NODE;

NODE a[6];

int cmp(const void * a,const void * b);
int check();

int main()
{
    //freopen("input.txt","r",stdin);
    while (scanf("%d%d",&a[0].x,&a[0].y)!=EOF)
    {
        for (int i=1 ; i<6 ; i++) scanf("%d%d",&a[i].x,&a[i].y);
        for (int i=0 ; i<6 ; i++)
        {
            int minx=a[i].x<a[i].y?a[i].x:a[i].y;
            int manx=a[i].x>a[i].y?a[i].x:a[i].y;
            a[i].x=minx;
            a[i].y=manx;
        }
        qsort(a,6,sizeof(NODE),cmp);
        int flag=check();
        if (flag) puts("POSSIBLE");
        else puts("IMPOSSIBLE");
    }
    return 0;
}

int cmp(const void * a,const void * b)
{
    NODE a1=*(NODE*)a;
    NODE b1=*(NODE*)b;
    if (a1.x!=b1.x) return a1.x-b1.x;
    else return a1.y-b1.y;
}

int check()
{
    for (int i=0 ; i<6 ; i+=2)
    {
        if (a[i].x!=a[i+1].x) return 0;
        if (a[i].y!=a[i+1].y) return 0;
    }
    if (a[0].x!=a[2].x || a[2].y!=a[4].y || a[0].y!=a[4].x) return 0;
    return 1;
}
