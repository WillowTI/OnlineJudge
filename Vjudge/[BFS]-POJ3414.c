//今天张羽戈大佬吐槽我的代码风格太丑陋了，我决定痛改前非。
//还是要学习一个，努力提高自己的姿势水平。

Description

You are given two pots, having the volume of A and B liters respectively. The following operations can be performed:

FILL(i)        fill the pot i (1 ≤ i ≤ 2) from the tap;
DROP(i)      empty the pot i to the drain;
POUR(i,j)    pour from pot i to pot j; after this operation either the pot j is full (and there may be some water left in the pot i), or the pot i is empty (and all its contents have been moved to the pot j).
Write a program to find the shortest possible sequence of these operations that will yield exactly C liters of water in one of the pots.

Input

On the first and only line are the numbers A, B, and C. These are all integers in the range from 1 to 100 and C≤max(A,B).

Output

The first line of the output must contain the length of the sequence of operations K. The following K lines must each describe one operation. If there are several sequences of minimal length, output any one of them. If the desired result can’t be achieved, the first and only line of the file must contain the word ‘impossible’.

Sample Input

3 5 4
Sample Output

6
FILL(2)
POUR(2,1)
DROP(1)
POUR(2,1)
FILL(2)
POUR(2,1)

翻译：你有2个锅子，现在给你3个操作：
1.FILL，把一个锅子倒满
2.DROP，把一个锅子倒掉
3.FILL，把一个锅子里的水倒到另一个果子里，注意不能溢出
如果最终能使其中一个锅子里的水达到给定容量，先输出最小步骤，再输出每一步的具体操作，任意的一种
否则输出impossible





#include<stdio.h>
#include<string.h>

int a=0,b=0,c=0;//输入的A锅，B锅最大容量，想要达到的C锅容量
int vis[110][110]={{0}};//记录(A,B)状态有没有达到过
int head=0,tail=1;
int flag=0;//记录有没有解
int finalstep=0;//记录最终的步长
int lastindex=0;//记录最后一个操作的位置
int recoed[110]={0};//在输出每一步时记录每一步的位置
typedef struct{
    int step;
    int op;
    int left;
    int right;
    int prev;
}NODE;
NODE q[110*110];

void BFS();

int main(){

    scanf("%d%d%d",&a,&b,&c);
    BFS();
    if (flag){
        printf("%d\n",finalstep);
        int cur=lastindex;
        recoed[finalstep-1]=cur;
        for ( int i = finalstep - 2 ; i >= 0; i-- ){
            cur=q[cur].prev;
            recoed[i]=cur;
        }
        for ( int i = 0 ; i < finalstep ; i++ ){
            if ( q[recoed[i]].op == 0 ){
                printf("FILL(1)\n");
            } else if ( q[recoed[i]].op == 1 ){
                printf("FILL(2)\n");
            } else if ( q[recoed[i]].op == 2 ){
                printf("DROP(1)\n");
            } else if ( q[recoed[i]].op == 3 ){
                printf("DROP(2)\n");
            } else if ( q[recoed[i]].op == 4 ){
                printf("POUR(1,2)\n");
            } else if ( q[recoed[i]].op == 5 ){
                printf("POUR(2,1)\n");
            }
        }
    } else {
        printf("impossible\n");
    }




    return 0;
}

void BFS(){

    NODE cur;
    cur.left=0;
    cur.right=0;
    cur.op=-1;
    cur.prev=-1;
    cur.step=0;
    q[head]=cur;
    vis[0][0]=1;
    while ( head < tail ){
        cur=q[head];
        if ( cur.left == c || cur.right == c){
            flag=1;
            lastindex=0;
            finalstep=0;
            return ;
        }
        for ( int i = 0 ; i < 6 ; i++ ){
            NODE tmp;
            if ( i == 0 ){//FILL(1)
                tmp.left=a;
                tmp.right=cur.right;
            } else if ( i== 1 ){//FILL(2)
                tmp.left=cur.left;
                tmp.right=b;
            } else if ( i== 2 ){//DROP(1)
                tmp.left=0;
                tmp.right=cur.right;
            } else if ( i== 3 ){//DROP(2)
                tmp.left=cur.left;
                tmp.right=0;
            } else if ( i== 4 ){//FILL(1,2)
                if ( cur.left+cur.right <= b ){//如果2不溢出
                    tmp.left=0;
                    tmp.right=cur.left+cur.right;
                } else {//如果2溢出
                    tmp.left=cur.left-(b-cur.right);
                    tmp.right=b;
                }
            } else if ( i== 5 ){//FILL(2,1)
                if ( cur.left+cur.right <= a ){//如果1不溢出
                    tmp.left=cur.left+cur.right;
                    tmp.right=0;
                } else {//如果1溢出
                    tmp.left=a;
                    tmp.right=cur.right-(a-cur.left);
                }
            }
            if ( !vis[tmp.left][tmp.right] ){//如果当前状态没有达到过
                vis[tmp.left][tmp.right]=1;
                tmp.op=i;
                tmp.prev=head;
                tmp.step=cur.step+1;
                q[tail++]=tmp;
                if ( tmp.left== c || tmp.right == c){
                    finalstep=tmp.step;
                    lastindex=tail-1;
                    flag=1;
                    return ;
                }
            }
        }
        head++;
    }
    return ;
}
