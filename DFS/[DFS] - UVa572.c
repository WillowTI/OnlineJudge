Input
The input file contains one or more grids. Each grid begins with a line containing m and n, the number
of rows and columns in the grid, separated by a single space. If m = 0 it signals the end of the input;
otherwise 1 ≤ m ≤ 100 and 1 ≤ n ≤ 100. Following this are m lines of n characters each (not counting
the end-of-line characters). Each character corresponds to one plot, and is either ‘*’, representing the
absence of oil, or ‘@’, representing an oil pocket.
Output
For each grid, output the number of distinct oil deposits. Two different pockets are part of the same
oil deposit if they are adjacent horizontally, vertically, or diagonally. An oil deposit will not contain
more than 100 pockets.
Sample Input
1 1
*
3 5
*@*@*
**@**
*@*@*
1 8
@@****@*
5 5
****@
*@@*@
*@**@
@@@*@
@@**@
0 0
Sample Output
0
1
2
2

翻译：油田开采，对于m*n的矩阵，'*'代表没有，'@'代表有，水平的，垂直的，斜向的视作连续的一整块。现在要求出有多少快油田。输入m=0代表终止。

典型的DFS搜索，一条路走到底，向8个方向搜索，走过的路就标记为'*'，直接在输入的矩阵里修改。DFS最明显的特征就是递归。

#include<stdio.h>
#include<string.h>
#define N 111

char str[N][N];
int a,b;
const int dir[8][2]={{1,1},{1,-1},{-1,1},{-1,-1},{0,1},{0,-1},{1,0},{-1,0}};

void bfs(int x,int y)
{
    int i=0;
     for(i=0;i<8;i++)
     {
         int n=x+dir[i][0];
         int m=y+dir[i][1];
         if(n<0||m<0||n>a-1||m>b-1||str[n][m]=='*')
             continue;
         str[n][m]='*';
         bfs(n,m);
     }
}
int main()
{
    int cnt=0;
    while(1)
    {
        scanf("%d%d",&a,&b);
        if (a==0)
        {
            break;
        }
        int cnt=0;
        int i=0;
        int j=0;
        for(i=0;i<a;i++)
           scanf("%s",str[i]);
        for(i=0;i<a;i++)
        {
           for(j=0;j<b;j++)
           {
              if(str[i][j]=='@')
              {
                 str[i][j]='*';
                 bfs(i,j);
                 cnt++;
              }
           }
        }
        printf("%d\n",cnt);
    }
    return 0;
}
