/**
 *题意：
 *先输入一些数字
 *然后有2种命令：
 *1 a b：把第a个数字+=b
 *2 a b：查询从l到r的和
 *分析：
 *点修改，比区间修改简单多了
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#define LL long long
LL sum[5 * 100000 * 4 + 5] = {0};
int n, q;
void build(int node, int l, int r);
void update(int node, int l, int r, int pos, int val);
LL query(int node, int l, int r,int ql,int qr);
int main()
{
    //freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    build(1, 1, n);
    scanf("%d", &q);
    while (q--) {
        int op, ql, qr;
        scanf("%d%d%d", &op, &ql, &qr);
        if (op == 1)
            update(1, 1, n, ql, qr);
        else {
            LL ans = query(1, 1, n, ql, qr);
            printf("%lld\n", ans);
        }
    }
    return 0;
}

void build(int node, int l, int r) {
    if (l == r) {
        scanf("%lld", &sum[node]);
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    sum[node] = sum[node * 2] + sum[node * 2 + 1];
}

void update(int node, int l, int r, int pos, int val) {
    if (l == pos && pos == r) {
        sum[node] += val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid)
        update(node * 2, l, mid, pos, val);
    else
        update(node * 2 + 1, mid + 1, r, pos, val);
    sum[node] = sum[node * 2] + sum[node * 2 + 1];
}

LL query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return sum[node];
    int mid = (l + r) / 2;
    LL ret = 0;
    if (ql <= mid)
        ret += query(node * 2, l, mid, ql, qr);
    if (mid < qr)
        ret += query(node * 2 + 1, mid + 1, r, ql, qr);
    return ret;
}
