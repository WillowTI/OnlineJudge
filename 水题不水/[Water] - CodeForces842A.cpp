���⣺
����5����l, r, x, y, k
����l, r֮���x, y֮���Ƿ����һ������a, b
ʹ��a/b����k
k������

������
������Χ���ﵽ��10 ^ 7
����ѭ��һ���ᳬʱ
�Ǿ���b��x��ʼ��y����
a��Ӧ�أ���x * k��ʼ��y * k
���Ƿ����һ��a����l, r֮��
�����ͽ��͵�10 ^ 7


#include <cstdio>
#include <algorithm>
#define ll long long

using namespace std;

ll l, r, x, y, k;

int exam();

int main()
{
    //freopen("in.txt", "r", stdin);
    scanf("%lld%lld%lld%lld%lld", &l, &r, &x, &y, &k);
    double MIN = (double)l / y;
    double MAX = (double)r / x;
    if (k < MIN || k > MAX)
        puts("NO");
    else
    {
        if (exam())
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}

int exam()
{
    ll st = x * k;
    for (ll i = x; i <= y; i++, st += k)
    {
        if (st >= l && st <= r)
            return 1;
    }
    return 0;
}
