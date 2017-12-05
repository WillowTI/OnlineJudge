题意：
给定n个数和q个查询
查找这个数字是否出现在n个数字中
出现了输出其从小到大排序后的位置
否则输出没找到
分析：
sort排序
lower_bound查找
lower_bound返回大于等于val的一个值的迭代器
如果要返回下标的话需要减去数组的起始位置
没找到的话返回0或数组大小
使用lower_bound必须重写小于运算符

#include <cstdio>
#include <algorithm>

using namespace std;

int a[10005];
int n, q;

int main()
{
    //freopen("in.txt", "r", stdin);
    int cas = 1;
    while (scanf("%d%d", &n, &q) && n)
    {
        for (int i = 0; i < n; i++)
            scanf("%d", &a[i]);
        sort(a, a + n);
        printf("CASE# %d:\n", cas++);
        for (int i = 0; i < q; i++)
        {
            int x;
            scanf("%d", &x);
            int ans = lower_bound(a, a + n, x) - a;
            if (ans == n || a[ans] != x)
                printf("%d not found\n", x);
            else
                printf("%d found at %d\n", x, ans + 1);
        }
    }
    return 0;
}
