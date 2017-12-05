#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int n,m,town[205][205]={{0}};

void Floyd();


int main()
{
    while (scanf("%d%d",&n,&m)!=EOF)
    {

        memset(town,0,sizeof(town));

        for (int i=0;i<m;i++)
        {
            int x,y,dis;
            scanf("%d%d%d",&x,&y,&dis);
            if (town[x][y]==0) town[y][x]=town[x][y]=dis;//坑点
            else town[y][x]=town[x][y]=town[x][y]<dis?town[x][y]:dis;
        }

        for (int i=0;i<n;i++)
        {
            for (int j=0;j<n;j++)
            {
                if (i!=j&&town[i][j]==0) town[i][j]=-1;
            }
        }

        Floyd();

        int st,end;

        scanf("%d%d",&st,&end);

        if (town[st][end]>=0&&town[st][end]<(n-1)*10000) printf("%d\n",town[st][end]);
        else printf("-1\n");
    }




    return 0;
}

void Floyd()
{
    for (int k=0;k<n;k++)
    {
        for (int i=0;i<n;i++)
        {
            for (int j=0;j<n;j++)
            {
                if (town[i][k]!=-1&&town[j][k]!=-1)
                {
                    if (town[i][j]==-1||(town[i][j]!=-1&&town[i][k]+town[j][k]<town[i][j]))
                        town[j][i]=town[i][j]=town[i][k]+town[j][k];
                }
            }
        }
    }
}