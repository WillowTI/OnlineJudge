题意：
输入n(2 <= n <= 9)，代表有n*n个点
输入m，代表有m条线段
接下来的m行每行一个字母c('H'或者'V') 和两个数字i,j
当字母为'H'时，说明(i , j)到(i , j + 1)有一条线段
当字母为'V'时，说明(j,  i)到(j + 1 , i)有一条线段
计算共有大大小小多少个正方形

分析：
遍历n - 1阶的所有点
对于每个点，以该点为正方形的左上角，避免重复
计算从1到最大理论长度能组成多少个正方形

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    int horizonal , vertical;
}NODE;

NODE square[15][15];
int area , num , ans[15];

int calculate(int x , int y , int maxsize);

int main()
{
    //freopen("input.txt" , "r" , stdin);
    //freopen("output.txt","w",stdout);
    int first = 1;
    while (scanf("%d\n" , &area) == 1)
    {
        memset(square , 0 , sizeof(square));
        memset(ans , 0 , sizeof(ans));
        scanf("%d\n" , &num);
        for (int i = 0 ; i < num ; i++)
        {
            char ch;
            int x,y;
            scanf("%c %d %d\n" , &ch , &x , &y);//V和H的i和j代表的坐标含义是不同的，所以要分开保存
            if (ch == 'V') square[y][x].vertical = 1;
            else square[x][y].horizonal = 1;
        }
        int flag = 0;
        for (int i = 1 ; i < area ; i++)
        {
            for (int j = 1 ; j< area ; j++)
            {
                int maxsize=(area - i) < (area - j) ? (area - i) : (area - j);//计算最大理论长度
                int squarenumbers=calculate(i , j , maxsize);
                if (squarenumbers) flag = 1;
            }
        }
        if (first > 1) printf("\n**********************************\n\n");
        printf("Problem #%d\n\n",first++);
        if (flag)
        {
            for (int i = 1 ; i <= area ; i++)
                if (ans[i]) printf("%d square (s) of size %d\n",ans[i],i);
        }
        else puts("No completed squares can be found.");//没有一个正方形时输出这句话
    }
    return 0;
}

int calculate(int x , int y , int maxsize)
{
    int ret = 0;
    for (int i = 1 ; i <= maxsize ; i++)
    {
        for (int j =0 ; j < i ; j++)
            if (square[x+j][y].vertical == 0 || square[x][y+j].horizonal == 0)
                return ret;
        int flag1 = 1 , flag2 = 1;
        for (int j = 0 ; j < i ; j++)
        {
            if (square[x+i][y+j].horizonal == 0)
            {
                flag1=0;
                break;
            }
        }
        if (flag1)
        {
            for (int j = 0 ; j < i ; j++)
                if (square[x+j][y+i].vertical == 0)
                {
                    flag2=0;
                    break;
                }
        }
        if (flag1 && flag2)
        {
            ans[i]++;
            ret=1;
        }
    }
    return ret;
}
