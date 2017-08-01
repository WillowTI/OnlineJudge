题意：
类似于翻转棋
两个白棋之间的黑棋被转换为白棋
这两个白棋可以是水平的、垂直的、斜45°的
但是这两个白棋之间必须是连续的黑棋，不能有空闲的位置，否则就不能吃掉黑棋
指令分为一以下4种：
W/B：出现在棋盘的下一行，代表由白棋/黑棋先手
L：列出当前玩家能下的所有位置
按照行坐标递增、列坐标递增的顺序
如果没有可选位置，输出No legal move.
Mxy：当前玩家下棋于(x , y)，并吃掉能吃的棋子
输出操作后棋盘上的白棋和黑棋数量
如果当前玩家不能下在该点，则由对方玩家下在该点

（“这个点是合法”的判断标准就是至少能吃掉对方的棋子）
Q：输出经历以上操作后的棋盘
退出这个棋盘
开始下一局

分析：模拟所有的操作，很繁琐
用一个数标记当前玩家是谁
L：遍历二维数组
检验每一个点
M：先检验这个点，看是否合法
再决定是否交换玩家
最后改变棋盘
Q：
输出
退出循环


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

char chess[15][15];
int flag[15][15];//记录(x , y)能否下棋子
const int dir[8][2]={{-1 , 0} , {1 , 0} , {0 , -1} , {0 , 1} , {-1 , -1} , {-1 , 1} , {1 , -1} , {1 , 1}};//上、下、左、右、左上、右上、左下、右下
int dirrecord[8];//记录哪一个方向是可行的，行为1，不行为0
const char player[3]="WB";
int op;//0代表当前玩家是W，1代表当前玩家是B

int exam(int x , int y);//检验(x , y)是否合法，合法返回1，不合法返回0
int isvalid(int x , int y);//辅助函数，检验(x , y)是否在棋盘上
int isvacant(int x , int y);//辅助函数，检验(x , y)是否有棋子
void solve(int x , int y);//下棋于(x , y)后吃掉对方的棋子

int main()
{
    //freopen("input.txt" , "r" , stdin);
    //freopen("output.txt" , "w" , stdout);
    int first=1;
    int cas;
    scanf("%d" , &cas);
    for (int t = 0 ; t < cas ; t++)
    {
        if (first) first = 0;
        else printf("\n");
        memset(chess , 0 , sizeof(chess));
        for (int i = 1 ; i <= 8 ; i++)
            scanf("%s" , chess[i]+1);
        while (1)
        {
            char tmp[10]={0};
            scanf("%s" , tmp);
            if (tmp[0] == 'Q')
            {
                for (int i = 1 ; i <= 8 ; i++)
                    puts(chess[i]+1);
                break;
            }
            else if (tmp[0] == 'W') op = 0;
            else if (tmp[0] == 'B') op = 1;
            else if (tmp[0] == 'L')
            {
                int ans=0;//记录共有多少能下的点。输出要求两个点之间用空格分隔，行末回车，所以必须要有总数
                memset(flag , 0 , sizeof(flag));
                for (int i = 1 ; i <= 8 ; i++)
                {
                    for (int j = 1 ; j <=8 ; j++)
                    {
                        memset(dirrecord , 0 , sizeof(dirrecord));
                        int a = exam(i , j);
                        if (a)
                        {
                            flag[i][j] = 1;
                            ans++;
                        }
                    }
                }
                if (ans == 0) puts("No legal move.");
                for (int i = 1 ; i <= 8 ; i++)
                {
                    for (int j = 1 ; j <= 8 ; j++)
                    {
                        if (flag[i][j])
                        {
                            ans--;
                            printf("(%d,%d)%c" , i , j , ans == 0 ? '\n' : ' ');
                        }
                    }
                }
            }
            else if (tmp[0] == 'M')
            {
                int x = tmp[1] - '0';
                int y = tmp[2] - '0';
                memset(dirrecord , 0 , sizeof(dirrecord));
                if (!exam(x , y))//判断是否交换玩家
                {
                    op = !op;
                    memset(dirrecord , 0 , sizeof(dirrecord));
                    exam(x , y);//为了保证方向记录数组被修改过，便于改变棋盘布局，检验(x , y)点
                }
                solve(x , y);
                op = !op;//交换玩家
                int black = 0 , white = 0;
                for (int i = 1 ; i <= 8 ; i++)
                {
                    for (int j = 1 ; j <=8 ; j++)
                    {
                        if (chess[i][j] == 'W') white++;
                        else if (chess[i][j] == 'B') black++;
                    }
                }
                printf("Black - %2d White - %2d\n" , black , white);//这里是一个坑点，要以%2d的格式输出
            }
        }
    }
    return 0;
}

int exam(int x, int y)
{
    if (!isvacant(x , y)) return 0;
    int ret = 0;
    for (int i =0 ; i < 8 ; i++)
    {
        int xx = x + dir[i][0];
        int yy = y + dir[i][1];
        if (isvalid(xx , yy) && chess[xx][yy] == player[!op])
        {
            xx += dir[i][0];
            yy += dir[i][1];
            for ( ; isvalid(xx , yy) ; xx += dir[i][0] , yy += dir[i][1])
            {
                if (chess[xx][yy] == player[op])//遇到自己的棋子，说明这个方向是可行的
                {
                    dirrecord[i]++;
                    ret = 1;
                    break;
                }
                else if (chess[xx][yy] == player[!op]) continue;//遇到对方的棋子，继续往前走
                else break;//遇到空格，这个方向不可行
            }
        }
    }
    return ret;
}

int isvalid(int x, int y)
{
    if (x >= 1 && x <= 8 && y >= 1 && y <= 8) return 1;
    else return 0;
}

int isvacant(int x, int y)
{
    if (chess[x][y] == '-') return 1;
    else return 0;
}

void solve(int x, int y)
{
    chess[x][y] = player[op];
    for (int i = 0 ; i < 8 ; i++)
    {
        if (dirrecord[i])
        {
            int xx = x + dir[i][0];
            int yy = y + dir[i][1];
            for ( ; chess[xx][yy] == player[!op] ; xx += dir[i][0] , yy += dir[i][1])
                chess[xx][yy] = player[op];
        }
    }
}
