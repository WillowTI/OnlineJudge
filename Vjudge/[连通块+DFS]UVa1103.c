#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int h,w,cnt,bin[205][55*8]={{0}};
const int dirx[1][4]={-1,0,0,1};
const int diry[1][4]={0,1,-1,0};
char hex[205][55]={{0}};
char ans[100000]={0};
const char seq[10]="WAKJSD";
const char hexnum[16][6]={"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
void hex2bin();
void dfs(int x,int y,int val);
void dfs1(int x,int y,int val);
int valid(int x,int y);




int main()
{
		int cas=1;
		while (1)
		{
			scanf("%d%d",&h,&w);

			if (h==0&&w==0) break;

			for (int i=0;i<h;i++)
			{
				scanf("%s",hex[i]);
			}
			hex2bin();

			h+=2;
			w*=4;
			w+=2;

			for (int i=0;i<h;i++)
			{
				for (int j=0;j<w;j++)
				{
					printf("%d ",bin[i][j]);
				}
				printf("\n");
			}
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
