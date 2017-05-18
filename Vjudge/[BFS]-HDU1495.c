Problem Description
大家一定觉的运动以后喝可乐是一件很惬意的事情，但是seeyou却不这么认为。因为每次当seeyou买了可乐以后，阿牛就要求和seeyou一起分享这一瓶可乐，而且一定要喝的和seeyou一样多。但seeyou的手中只有两个杯子，它们的容量分别是N 毫升和M 毫升 可乐的体积为S （S<101）毫升　(正好装满一瓶) ，它们三个之间可以相互倒可乐 (都是没有刻度的，且 S==N+M，101＞S＞0，N＞0，M＞0) 。聪明的ACMER你们说他们能平分吗？如果能请输出倒可乐的最少的次数，如果不能输出"NO"。


Input
三个整数 : S 可乐的体积 , N 和 M是两个杯子的容量，以"0 0 0"结束。


Output
如果能平分的话请输出最少要倒的次数，否则输出"NO"。


Sample Input
7 4 3
4 1 3
0 0 0


Sample Output
NO
3


当s是奇数的时候一定不能平分，直接输出NO。
否则BFS搜索，对每一种状态有6种情况：
1.S->N
2.S->M
3.N->S
4.N->M
5.M->S
6.M->N
注意不能溢出
判定平分：只要当有两个杯子的可乐体积一样时即为平分

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int s,a,b;
int vis[102][102][102]={{{0}}};//(s,a,b)记录每一种情况
int head=0;
int tail=1;
int cnt=0;

typedef struct {

    int bot,left,right,step;

}NODE;

NODE q[102*102*102];

int BFS();

int main(){

    while (scanf("%d%d%d",&s,&a,&b)){
        if ( s==0 && a==0 && b==0 ){
            break;
        }
        head=0;
        tail=1;
        memset(vis,0,sizeof(vis));
        if ( s%2 == 1 ){
            printf("NO\n");
        } else {
            int flag=BFS();
            if (flag){
                printf("%d\n",cnt);
            } else {
                printf("NO\n");
            }
        }

    }






    return 0;
}

int BFS(){

    NODE cur;
    cur.bot=s;
    cur.left=0;
    cur.right=0;
    cur.step=0;
    q[head]=cur;
    vis[s][0][0]=1;
    while ( head < tail ){
        cur=q[head];
        NODE tmp;
        for ( int i = 0 ; i < 6 ; i++ ){
            if ( i == 0){
                if ( cur.left+cur.bot <= a ){
                    tmp.bot=0;
                    tmp.left=cur.left+cur.bot;
                } else {
                    tmp.bot=cur.bot-(a-cur.left);
                    tmp.left=a;
                }
                tmp.right=cur.right;
            } else if ( i == 1 ){
                if ( cur.right+cur.bot <= b ){
                    tmp.bot=0;
                    tmp.right=cur.right+cur.bot;
                } else {
                    tmp.bot=cur.bot-(b-cur.right);
                    tmp.right=b;
                }
                tmp.left=cur.left;
            }else if ( i == 2 ){
                tmp.bot=cur.bot+cur.left;
                tmp.left=0;
                tmp.right=cur.right;
            }else if ( i == 3 ){
                if ( cur.left+cur.right <= b ){
                    tmp.left=0;
                    tmp.right=cur.left+cur.right;
                } else {
                    tmp.left=cur.left-(b-cur.right);
                    tmp.right=b;
                }
                tmp.bot=cur.bot;
            }else if ( i == 4 ){
                tmp.bot=cur.bot+cur.right;
                tmp.left=cur.left;
                tmp.right=0;
            }else if ( i == 5 ){
                if ( cur.left+cur.right <= a ){
                    tmp.left=cur.left+cur.right;
                    tmp.right=0;
                } else {
                    tmp.left=a;
                    tmp.right=cur.right-(a-cur.left);
                }
                tmp.bot=cur.bot;
            }
            if ( !vis[tmp.bot][tmp.left][tmp.right] ){
                vis[tmp.bot][tmp.left][tmp.right]=1;
                tmp.step=cur.step+1;
                q[tail++]=tmp;
                if ( tmp.bot==0 && tmp.left == tmp.right ){

                    cnt=tmp.step;
                    return 1;
                } else if ( tmp.left ==0 && tmp.bot == tmp.right ){

                    cnt=tmp.step;
                    return 1;
                } else if ( tmp.right == 0 && tmp.bot == tmp.left ) {

                    cnt=tmp.step;
                    return 1;
                }
            }
        }
        head++;
    }

    return 0;
}
