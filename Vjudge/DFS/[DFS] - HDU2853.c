Problem Description
在N*N的方格棋盘放置了N个皇后，使得它们不相互攻击（即任意2个皇后不允许处在同一排，同一列，也不允许处在与棋盘边框成45角的斜线上。
你的任务是，对于给定的N，求出有多少种合法的放置方法。



Input
共有若干行，每行一个正整数N≤10，表示棋盘和皇后的数量；如果N=0，表示结束。


Output
共有若干行，每行一个正整数，表示对应输入行的皇后的不同放置数量。


Sample Input
1
8
5
0


Sample Output
1
92
10

把1到10的所有答案求出来，保存在数组里。
输入n，输出答案的时候直接输出下标为n的元素。
从第一行开始遍历，如果此点合法，那就遍历下一行，直到把所有的皇后放进去或者不存在这样的做法，停止搜索。




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int n;
int vis[11][11]={{0}};
int ans[11]={0};
int size=1;
int num=0;
const int dir[8][2]={{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};//方向，用于检车此点合不合法

void DFS(int row);
int check(int m,int n);

int main(){

    for ( size = 1 ; size <= 10 ; size++ ){

        memset(vis,0,sizeof(vis));
        DFS(0);

    }

    while (scanf("%d",&n)){

        if ( n == 0 ){
            break;
        }

        printf("%d\n",ans[n]);

    }

    return 0;
}

void DFS(int row){

    if ( num == size ){
        ans[size]++;
        return ;
    }

    //这里加一句
    //if ( row > size ){
    //     return;
    //}
    //可以增加可读性

    for ( int col = 0 ; col < size ; col++ ){

        if ( check(row,col) ){//如果此点合法，就保存进访问数组，并搜索下一行

            vis[row][col]=1;
            num++;
            DFS(row+1);
            num--;//搜索完毕后，计数器还原
            vis[row][col]=0;//访问数组还原

        }

    }

}

int check(int m,int n){

    for ( int i=0 ; i < 8 ; i++ ){//对于8个方向

        int tmpm=m+dir[i][0];
        int tmpn=n+dir[i][1];

        while ( 0 <= tmpm && tmpm < size && 0<= tmpn && tmpn < size ){//一直搜索到边界再停止

            if ( vis[tmpm][tmpn] ){//一旦在路径上有访问过的点就不合法
                return 0;
            }

            tmpm+=dir[i][0];
            tmpn+=dir[i][1];

        }
    }

    return 1;
}
