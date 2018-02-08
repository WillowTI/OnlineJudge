#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
int n, k, a[105];
int main() {
    //freopen("in.txt", "r", stdin);
    while (scanf("%d%d", &n, &k) == 2) {
        for (int i = 0; i < k; i++)
            scanf("%d", a + i);
        int sum1 = n, sum2 = n * 2;
        for (int i = 0; i < k; i++) {//先把4连坐的占掉
            int t = min(sum1, a[i] / 4);
            sum1 -= t;
            a[i] -= 4 * t;
        }
        //这时剩下的a[i]都是小于4的
        //把空余的4连坐用于2连坐
        //由于不同组的2个人不能坐在一个4连坐上，所以1个4连坐只能贡献1个2连坐
        sum2 += sum1;
        for (int i = 0; i < k; i++) {//把2连坐的占掉
            int t = min(sum2, a[i] / 2);
            sum2 -= t;
            a[i] -= 2 * t;
        }
        //这时剩下的a[i]都是小于2的
        //把1处理掉
        //由于刚才已经把4连坐加在2连坐上了，所以4连坐不是贡献2倍的，而是1倍的
        //tmp相当于最后还剩余几个单座的
        //小于0就说明是不合法的
        int tmp = sum1 + sum2;
        for (int i = 0; i < k; i++)
            tmp -= a[i];
        if (tmp >= 0)
            puts("YES");
        else
            puts("NO");
    }
    return 0;
}

