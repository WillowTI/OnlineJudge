���⣺
����n������q����ѯ
������������Ƿ������n��������
������������С����������λ��
�������û�ҵ�
������
sort����
lower_bound����
lower_bound���ش��ڵ���val��һ��ֵ�ĵ�����
���Ҫ�����±�Ļ���Ҫ��ȥ�������ʼλ��
û�ҵ��Ļ�����0����������±�
ʹ��lower_bound������дС�������

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
