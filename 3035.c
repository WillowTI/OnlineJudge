Description 

二值图像是由黑白两种像素组成的矩形点阵，图像识别的一个操作是求出图像中次大(第二大)黑区域的面积。请设计一个程序完成二值图像的这个操作。黑区域由若干黑像素组成，一个黑区域中的每个黑像素至少与该区域中的另一个黑像素相邻，规定一个像素仅与其上、下、左、右的像素相邻。两个不同的黑区域没有相邻的像素。一个黑区域的面积是其所包含的黑像素的个数。

Input 

第1行：一个整数T（1≤T≤10）为问题数。

接下来共T组测试数据，每组测试数据的第一行含两个整数n和m （1 ≤n，m≤100）， 分别表示二值图像的行数与列数，后面紧跟着n行，每行含m个整数0或1，其中第i行表示图像的第i行的m个像素，0表示白像素，1表示黑像素。同一行的相邻两个整数之间用一个空格隔开。

Output 

对于每个问题，输出一行问题的编号（0开始编号，格式：case #0: 等）。

然后对应每组测试数据，在一行中输出一个整数，表示相应的图像中次大（第二大）黑区域的面积。如果第二大面积的黑区域不存在时，则输出0。
Sample Input 

3
2 3
1 1 0
0 1 1
4 5
0 1 1 0 1
0 0 0 1 0
0 1 1 1 0
0 1 0 0 0
5 6
1 1 0 0 1 1
1 1 0 1 1 0
0 0 1 0 0 1
1 1 0 1 0 1
0 1 0 1 1 0
Sample Output 

case #0:
0
case #1:
2
case #2:
3
 
Hints
1、第一组测试数据，在图像中只能找到1个黑区域，面积为4，因此次大（第二大）黑区域的面积为0。

2、第三组测试数据，在图像中能找到6个黑区域，它们的面积分别为4,4,3,3,2，1，次大（第二大）黑区域的面积为3。





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define M 110

int n,m,sum;
int a[M][M];
int ans[10005]={0};
int cur=0;

int dir[4][2]={{0,1},{0,-1},{1,0},{-1,0}};

void dfs(int x,int y)
{
    a[x][y]=0;//每遇到一次1,结果加1,然后赋值为0,避免被再次搜索 
    for (int t=0;t<4;t++)//四个方向搜索 
    {
        int nx=x+dir[t][0];
        int ny=y+dir[t][1];
        if(nx>=0&&nx<n&&ny>=0&&ny<m&&a[nx][ny]==1)
        {
            sum++;
            dfs(nx,ny);
        }
    }
    return;
}

int cmp(const void * a,const void * b);

int main()
{
    int cas;
    scanf("%d",&cas);
    for (int t=0;t<cas;t++)
    {
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                scanf("%d",&a[i][j]);
            }
        }
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<m;j++)
            {
                if(a[i][j]==1)//每次遇到黑点就开始向四个方向开始搜索
                {
                    sum=1;
                    dfs(i,j);
                    ans[cur++]=sum;//把这一次搜索的结果保存在数组中
                }
            }
        }
        qsort(ans,cur,sizeof(int),cmp);//按照从大到小的顺序排序
        int result=ans[0];
        int tmp=0;
        for (;tmp<cur;tmp++)
        {
            if (ans[tmp]!=result)//从左往右寻找，找到不同于第一个（最大）的数字
            {
                result=ans[tmp];
                break;
            }
        }
        if (tmp==cur)//如果找不到就赋为0
        {
            result=0;
        }
        printf("case #%d:\n",t);
        printf("%d\n",result);
        cur=0;//数组坐标复原
    }

    return 0;
}

int cmp(const void * a,const void * b)
{
    return *(int*)b-*(int*)a;
}


DFS深度优先搜索
这道题是仿造最大黑区域的，本质上还是找到黑区域的面积，区别是一个是输出最大的，这道题要求的是次大的。
附：原最大黑区域题目解析：http://blog.csdn.net/bao_libra/article/details/45154387
