/**
 * 长度短的可以多次访问
 * 长的就要限制访问次数
 * 访问次数就是Huffman树的深度
 * 每次选出最小的2个数字加起来再放回去
 * 这是O(n^2)的实现方式
 */
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
typedef long long LL;
using namespace std;
int n, a[20005];
int main() {
    //freopen("F:\\TestCode\\TestCLion\\in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", a + i);
    LL ans = 0;
    while (n > 1) {
        int m1 = 0, m2 = 1;
        if (a[m1] > a[m2])
            swap(m1, m2);
        for (int i = 2; i < n; i++) {
            if (a[i] < a[m1]) {
                m2 = m1;
                m1 = i;
            } else if (a[i] < a[m2])
                m2 = i;
        }
        int add = a[m1] + a[m2];
        ans += add;
        if (m1 == n - 1)
            swap(m1, m2);
        a[m1] = add;
        a[m2] = a[n - 1];
        n--;
    }
    printf("%lld\n", ans);
    return 0;
}