题意：
给定2 * n个数
分成两组
每组n个数
问是否存在一种分组情况
使得一组里的数字全部严格大于另一组的数字

分析：
排序
比大小


#include <cstdio>
#include <algorithm>

using namespace std;

int n;
int num[205];

int main()
{
    //freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < 2 * n; i++)
        scanf("%d", &num[i]);
    sort(num, num + 2 * n);
    if (num[n] > num[n - 1])
        puts("YES");
    else
        puts("NO");
    return 0;
}
