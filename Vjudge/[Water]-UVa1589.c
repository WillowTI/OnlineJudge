题意：输入三个整数n,x,y
n表示对方有几个棋子，x和y对应己方“將”的坐标
接下来n行每行一个字母（'G'为帥，'R'为車，'H'为馬，'C'为炮）
现在轮到“將”走，请问是否存在一种走法是的“將”能活下去

稍有常识的人都知道象棋的规则
算了，还是详细说明一遍吧
1.帥/將：如果双方将领位于一直线上而且中间没有棋子，那么谁先手，谁就获胜
2.車：可在直线上移动任意距离
3.馬：8种移动方法，但是注意”拌马脚“
4.炮：当炮和地方棋子间存在另外一个棋子（不管是哪方的）那么炮可以进攻

分析：
穷举四种走法，先判断其合理性，再判断这样走能不能活下去

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct
{
    char c;
    int life,x,y;//因为“將”可以把棋子吃掉，所以用life记录这个棋子是不是还活着
}NODE;

NODE chess[10];
int num,gx,gy;
const int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};//对应上、下、左、右
const int dirh[8][2]={{-2,-1},{-2,1},{2,-1},{2,1},{-1,-2},{1,-2},{-1,2},{1,2}};//dirh[i]的马脚对应dir[i/2]
int isvalid(int x,int y);//“將”的位置是否合法
int isvacant(int x,int y);//“將”的位置是不是有人了
int exam(int x,int y);//检测(x,y)能不能让“將”活下去
int intervalx(int minx,int maxx);//沿x方向，在gy直线上的(minx,maxx)上有多少棋子
int intervaly(int miny, int maxy);//沿y方向，在gx直线上的(miny,maxy)上有多少棋子

int main()
{
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    while (scanf("%d%d%d\n",&num,&gx,&gy) && num)
    {
        for (int i=0 ; i<num ; i++)
        {
            scanf("%c %d %d\n",&chess[i].c,&chess[i].x,&chess[i].y);
            chess[i].life=1;
        }
        int flag=0;
        for (int i=0 ; i<4 ; i++)
        {
            gx+=dir[i][0];
            gy+=dir[i][1];
            if (isvalid(gx , gy))
            {
                if (!isvacant(gx , gy))
                {
                    for (int j=0 ; j<num ; j++)
                        if (chess[j].x==gx && chess[j].y==gy)
                        {
                            chess[j].life=0;
                            break;
                        }
                }
                flag=exam(gx , gy);
            }
            gx-=dir[i][0];
            gy-=dir[i][1];
            if (flag) break;
        }
        if (flag) puts("NO");
        else puts("YES");
    }
    return 0;
}

int isvalid(int x,int y)
{
    if (y>=4 && y<=6 && x>=1 && x<=3) return 1;
    else return 0;
}

int isvacant(int x, int y)
{
    for (int i=0 ; i<num ; i++)
        if(chess[i].x==x && chess[i].y==y) return 0;
    return 1;
}

int exam(int x, int y)
{
    for (int i=0 ; i<num ; i++)
    {
        if (chess[i].life)
        {
            char ch=chess[i].c;
            if (ch=='G')
            {
                if (gy == chess[i].y && intervalx(gx < chess[i].x ? gx : chess[i].x , gx > chess[i].x ? gx : chess[i].x)==0) return 0;
            }
            else if (ch=='R')
            {
                if (gy == chess[i].y && intervalx(gx < chess[i].x ? gx : chess[i].x , gx > chess[i].x ? gx : chess[i].x)==0) return 0;
                if (gx == chess[i].x && intervaly(gy < chess[i].y ? gy : chess[i].y , gy > chess[i].y ? gy : chess[i].y)==0) return 0;
            }
            else if (ch=='H')
            {
                for (int j=0 ; j<8 ; j++)
                    if (gx == chess[i].x + dirh[j][0] && gy == chess[i].y + dirh[j][1] && isvacant(chess[i].x + dir[j / 2][0] , chess[i].y + dir[j / 2][1])) return 0;
            }
            else
            {
                if (gy == chess[i].y && intervalx(gx < chess[i].x ? gx : chess[i].x , gx > chess[i].x ? gx : chess[i].x)==1) return 0;
                if (gx == chess[i].x && intervaly(gy < chess[i].y ? gy : chess[i].y , gy > chess[i].y ? gy : chess[i].y)==1) return 0;
            }
        }
    }
    return 1;
}

int intervalx(int minx, int maxx)
{
    int ret=0;
    for (int i=0 ; i<num ; i++)
        if (chess[i].life && chess[i].y==gy && (chess[i].x>minx && chess[i].x<maxx)) ret++;
    return ret;
}

int intervaly(int miny, int maxy)
{
    int ret=0;
    for (int i=0 ; i<num ; i++)
        if (chess[i].life && chess[i].x==gx && (chess[i].y>miny && chess[i].y<maxy)) ret++;
    return ret;
}
