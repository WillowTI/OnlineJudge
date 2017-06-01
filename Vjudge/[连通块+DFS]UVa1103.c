题目太长了，而且有图片，就不放了。
简要描述一下：
一个十六进制的二维数组，转化为二进制，0代表空，1代表黑点。
再找有几个连通块，分别对应字符'W','A','K','J','S','D'。
最后输出字典序排序后的字符串。
注意：一幅图里可能有多个字符。

分析：
十六进制转二进制还行。不过要增加一条由0组成的边框，便于“染色”。
把外层的0染成2，黑点染成3，内部的0染成4，数连通块的个数。
不同字符之间是由0分隔的，所以在染一个字符的同时不会影响到相邻的字符。

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int h,w,cnt,bin[205][55*8]={{0}};//h代表高度，w代表宽度，cnt记录有几个连通块，bin为二维数组
int length=0;//字符的个数
const int dirx[4]={-1,0,0,1};
const int diry[4]={0,1,-1,0};
char hex[205][55]={{0}};//读进来的十六进制串
char ans[100000]={0};//存放字符
const char seq[10]="WAKJSD";
const char hexnum[16][6]={"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
void hex2bin();
void dfs1(int x,int y,int val);
void dfs2(int x,int y,int val);
int valid(int x,int y);
int cmp(const void * a,const void * b);

int main()
{
		int cas=1;
		while (1)
		{
			scanf("%d%d",&h,&w);

			if (h==0&&w==0) break;

            memset(bin,0,sizeof(bin));//初始化
            memset(ans,0,sizeof(ans));
            length=0;

			for (int i=0;i<h;i++)
			{
				scanf("%s",hex[i]);
			}

			hex2bin();

			h+=2;
			w*=4;
			w+=2;

			dfs1(0,0,2);//把外层0染成2

			for (int i=0;i<h;i++)
                for (int j=0;j<w;j++)
                    if (bin[i][j]==1)//当遇到一个字符
                    {
                        cnt=0;
                        dfs2(i,j,3);//把1染成3
                        ans[length++]=seq[cnt];
                    }

            printf("Case %d: ",cas);
            cas++;
            qsort(ans,length,sizeof(char),cmp);
            puts(ans);

		}

    return 0;
}

void hex2bin()
{
	int binx=1;
	int biny=1;
	for (int i=0;i<h;i++,binx++)
	{
		biny=1;
		for (int j=0;j<w;j++)
		{
			int num;
			if (isdigit(hex[i][j])) num=hex[i][j]-'0';
			else num=hex[i][j]-'a'+10;
			for (int k=0;k<4;k++)
				bin[binx][biny++]=hexnum[num][k]-'0';
		}
	}
}

void dfs1(int x, int y, int val)
{
	int ori=bin[x][y];
	bin[x][y]=val;
	for (int i=0;i<4;i++)
	{
		int nx=x+dirx[i];
		int ny=y+diry[i];
		if (valid(nx,ny)&&bin[nx][ny]==ori) dfs1(nx,ny,val);
	}
}

int valid(int x, int y)
{
	return (x>=0&&x<h&&y>=0&&y<w);
}

void dfs2(int x,int y,int val)
{
    int ori=bin[x][y];
    bin[x][y]=val;
    for (int i=0;i<4;i++)
    {
        int nx=x+dirx[i];
        int ny=y+diry[i];
        if (valid(nx,ny))
        {
            if (bin[nx][ny]==ori) dfs2(nx,ny,val);
            else if (bin[nx][ny]==0)//遇到内层0把0染成4，计数器+1
            {
                cnt++;
                dfs1(nx,ny,4);
            }
        }
    }
}

int cmp(const void * a,const void * b)
{
    return (int)(*(char*)a-*(char*)b);
}

附上测试数据，题目给的数据太泛了。
Input:
5 3
fff
f0f
fff
f0f
fff
5 5
0fff0
0f0f0
fffff
00f00
00f00
5 5
0f0f0
0f0f0
fffff
00f00
00f00
2 6
1fe07c
3fe07c
2 20
03fffffffffffffffff0
03fffffffffffffffff0 
0 0
	
Output:
Case 1: K
Case 2: A
Case 3: W
Case 4: WW
Case 5: W
