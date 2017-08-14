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

int main()
{
    char s[100005]={0};
    while (scanf("%s",s+1)!=EOF)
    {
        int next[100005]={0};
        int last=0;
        int cur=0;//cur更像是prev的感觉
        int length=strlen(s+1);
        for (int i=1;i<=length;i++)
        {
            char ch=s[i];
            if (ch=='[') cur=0;
            else if (ch==']') cur=last;
            else
            {
                next[i]=next[cur];//把cur元素往后移
                next[cur]=i;//让上一个节点指向i
                if (last==cur) last=i;
                cur=i;//移动光标
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
//紫书上的例题，看代码看了半天觉得好神奇，我大概自己是写不出来了，背模板吧
//用Java的LinkedList做了一遍，超时，很遗憾。看不起Java咯（微笑脸
//要是C++有自带链表之类的高级数据结构我还是很乐意学C++的
