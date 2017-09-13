The ministers of the cabinet were quite upset by the message from the Chief of Security stating that they would all have to change the four-digit room numbers on their offices.
— It is a matter of security to change such things every now and then, to keep the enemy in the dark.
— But look, I have chosen my number 1033 for good reasons. I am the Prime minister, you know!
— I know, so therefore your new number 8179 is also a prime. You will just have to paste four new digits over the four old ones on your office door.
— No, it’s not that simple. Suppose that I change the first digit to an 8, then the number will read 8033 which is not a prime!
— I see, being the prime minister you cannot stand having a non-prime number on your door even for a few seconds.
— Correct! So I must invent a scheme for going from 1033 to 8179 by a path of prime numbers where only one digit is changed from one prime to the next prime.

Now, the minister of finance, who had been eavesdropping, intervened.
— No unnecessary expenditure, please! I happen to know that the price of a digit is one pound.
— Hmm, in that case I need a computer program to minimize the cost. You don't know some very cheap software gurus, do you?
— In fact, I do. You see, there is this programming contest going on... Help the prime minister to find the cheapest prime path between any two given four-digit primes! The first digit must be nonzero, of course. Here is a solution in the case above.
1033
1733
3733
3739
3779
8779
8179
The cost of this solution is 6 pounds. Note that the digit 1 which got pasted over in step 2 can not be reused in the last step – a new 1 must be purchased.
Input
One line with a positive number: the number of test cases (at most 100). Then for each test case, one line with two numbers separated by a blank. Both numbers are four-digit primes (without leading zeros).
Output
One line for each case, either with a number stating the minimal cost or containing the word Impossible.
Sample Input
3
1033 8179
1373 8017
1033 1033
Sample Output
6
7
0

翻译：给定两个素数n和m，要求把n变成m，每次变换时只能变一个数字，即变换后的数与变换前的数只有一个数字不同，并且要保证变换后的四位数也是素数。求最小的变换次数；如果不能完成变换，输出Impossible。
对每一位枚举，个位从1开始到9枚举每一个奇数，十位和百位都是从0到9的每一个数字，千位从1到9，然后依旧是BFS



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

int n,m;
int head=0,tail=1;
int vis[10100];//对四位数的枚举，数组得开到1e4级别的
typedef struct
{
    int x;
    int step;
}NODE;

NODE Q[10100];



int isprime(int n);
void BFS();

int main()
{
    int cas;
    scanf("%d",&cas);
    for (int t=0;t<cas;t++)
    {
        scanf("%d%d",&n,&m);
        memset(vis,0,sizeof(vis));
        head=0;
        tail=1;
        vis[n]=1;
        NODE tmp;
        tmp.x=n;
        tmp.step=0;
        Q[0]=tmp;
        BFS();
    }



    return 0;
}

int isprime(int n)
{
    if (n==0||n==1)
    {
        return 0;
    }
    if (n==2)
    {
        return 1;
    }
    if (n%2==0)
    {
        return 0;
    }
    for (int i=3;i*i<=n;i+=2)
    {
        if (n%i==0)
        {
            return 0;
        }
    }
    return 1;
}

void BFS()
{
   int curx;
   int curstep;
   while (head<tail)
   {
       NODE cur=Q[head];
       head++;
       curx=cur.x;
       curstep=cur.step;
       if (curx==m)
       {
           printf("%d\n",curstep);
           return ;
       }
       for (int i=1;i<=9;i+=2)
       {
           int s=curx/10*10+i;
           if (s!=curx&&!vis[s]&&isprime(s))
           {
               vis[s]=1;//访问标记更新！访问标记更新！访问标记更新！
               NODE temp;
               temp.x=s;
               temp.step=curstep+1;
               Q[tail++]=temp;
           }
       }
       for (int i=0;i<=9;i++)
       {
           int s=curx/100*100+curx%10+i*10;
           if (s!=curx&&!vis[s]&&isprime(s))
           {
               vis[s]=1;//访问标记更新！访问标记更新！访问标记更新！
               NODE temp;
               temp.x=s;
               temp.step=curstep+1;
               Q[tail++]=temp;
           }
       }
       for (int i=0;i<=9;i++)
       {
           int s=curx/1000*1000+curx%100+i*100;
           if (s!=curx&&!vis[s]&&isprime(s))
           {
               vis[s]=1;//访问标记更新！访问标记更新！访问标记更新！
               NODE temp;
               temp.x=s;
               temp.step=curstep+1;
               Q[tail++]=temp;
           }
       }
       for (int i=1;i<=9;i++)
       {
           int s=i*1000+curx%1000;
           if (s!=curx&&!vis[s]&&isprime(s))
           {
               vis[s]=1;//访问标记更新！访问标记更新！访问标记更新！
               NODE temp;
               temp.x=s;
               temp.step=curstep+1;
               Q[tail++]=temp;
           }
       }
   }
   printf("Impossible\n");
   return ;
}
