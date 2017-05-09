输入包含多组数据。每组数据占一行，包含不超过100000个字母、下划线、字符'['或者']'。其中字符'['表示HOME键，']'表示END键。
输入结束标志为文件结束符（EOF）。输入文件不超过5MB。
对于每组数据，输出一行，即屏幕上的悲剧文本。
样例输入：
This_is_a_[Beiju]___text
[[]][][]Happy_Birthday_to_Tsinghua_University
样例输出：
BeijuThis_is_a__text
Happy_Birthday_to_Tsinghua_University




#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

const int maxn=100000+5;
int last;
int cur;
int next[100005]={0};
char s[100005]={0};



int main()
{
    while (scanf("%s",s+1)==1)
    {
        int n=strlen(s+1);
        last=cur=0;
        next[0]=0;
        for (int i=1;i<=n;i++)
        {
            char ch=s[i];
            if (ch=='[')
            {
                cur=0;
            }
            else if (ch==']')
            {
                cur=last;
            }
            else
            {
                next[i]=next[cur];
                next[cur]=i;
                if (cur==last)
                {
                    last=i;
                }
                cur=i;
            }
        }
        for (int i=next[0];i!=0;i=next[i])
        {
            printf("%c",s[i]);
        }
        printf("\n");
    }


    return 0;
}
