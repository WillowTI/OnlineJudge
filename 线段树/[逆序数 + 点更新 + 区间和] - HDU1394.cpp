/**
 * 之前用归并排序求过逆序数，这次试试用线段树做
 * 先离散化处理，由于这道题规定了数字都是从0到n - 1，所以读进来的时候全部加1就可以了
 * 求逆序数的具体做法是对于当前数字k，逆序数加上区间和[k, n]，然后把叶子结点加1，标记为已经出现过
 * 接下来要枚举最小逆序数
 * 对于当前数字k，把它移到数组尾部后，原来比它小的k - 1个数字在它前面了，减去
 * 比它大的n - k个数字在它前面了，加上
 * 也就是在原来逆序数的基础上加上n - k * 2 + 1
 * 一共枚举n个数字，记录最小值，就是答案
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
const int MAXN = 5000 * 4 + 5;
using namespace std;
int n, sum, ans, num[MAXN], a[5005];
void update(int node, int l, int r, int v);
int query(int node, int l, int r, int ql, int qr);
int main() {
    //freopen("in.txt", "r", stdin);
    while (scanf("%d", &n) == 1) {
        memset(num, 0, sizeof(num));
        ans = 0;
        for (int i = 0; i < n; i++) {
            scanf("%d", a + i);
            a[i]++;
        }
        for (int i = 0; i < n; i++) {
            ans += query(1, 1, n, a[i], n);
            update(1, 1, n, a[i]);
        }
        sum = ans;
        for (int i = 0; i < n; i++) {
            sum += (n - a[i] * 2 + 1);
            ans = min(ans, sum);
        }
        printf("%d\n", ans);
    }
    return 0;
}

void update(int node, int l, int r, int v) {
    if (l == r) {
        num[node]++;
        return;
    }
    int mid = (l + r) / 2;
    if (v <= mid)
        update(node * 2, l, mid, v);
    else
        update(node * 2 + 1, mid + 1, r, v);
    num[node] = num[node * 2] + num[node * 2 + 1];
}

int query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return num[node];
    int mid = (l + r) / 2;
    int ret = 0;
    if (ql <= mid)
        ret += query(node * 2, l, mid, ql, qr);
    if (mid < qr)
        ret += query(node * 2 + 1, mid + 1, r, ql, qr);
    return ret;
}
