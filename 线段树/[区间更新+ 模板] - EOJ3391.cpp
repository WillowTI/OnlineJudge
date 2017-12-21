/**
 * 复习一遍线段树的区间更新
 * 主要还是要清楚什么时候push_down
 * update的时候一定要push_down + push_up，这个就不谈了
 * 为什么query的时候要呢？
 * 考虑这样一组数据:
 * 1 2 3 4 5
 * [1, 3]加2
 * 查询[1, 2]
 * 如果不push_down的话为输出3，显然有问题
 * 这是因为lazy的标记在[1, 3]的节点上
 * [1, 2]是[1, 3]的左孩子
 * 查询[1, 2]的时候没有把lazy标记传递下来，所以[1, 2]是不知道它的父节点有标记的
 * [1, 2]保存的sum并不是真正的sum
 * 当被查询区间与当前区间有重合而不是完全属于的时候要传递标记
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define maxn 500000 * 4 + 5
#define LL long long
using namespace std;
LL flag[maxn], sum[maxn];
int n;
void build(int node, int l, int r);
void update(int node, int l, int r, int ql, int qr, LL add);
LL query(int node, int l, int r, int ql, int qr);
void push_down(int node, int l, int r);
void push_up(int node);
int main() {
    //freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    build(1, 1, n);
    int q;
    scanf("%d", &q);
    while (q--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int ql, qr;
            LL add;
            scanf("%d%d%lld", &ql, &qr, &add);
            update(1, 1, n, ql, qr, add);
        } else {
            int ql, qr;
            scanf("%d%d", &ql, &qr);
            printf("%lld\n", query(1, 1, n, ql, qr));
        }
    }
    return 0;
}

void build(int node, int l, int r) {
    if (l == r) {
        scanf("%lld", &sum[node]);
        return;
    }
    int m = (l + r) / 2;
    build(node * 2, l, m);
    build(node * 2 + 1, m + 1, r);
    sum[node] = sum[node * 2 ] + sum[node * 2 + 1];
}

void update(int node, int l, int r, int ql, int qr, LL add) {
    if (ql <= l && r <= qr) {
        flag[node] += add;
        sum[node] += add * (r - l + 1);
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    if (ql <= mid) {
        update(node * 2, l, mid, ql, qr, add);
    }
    if (mid < qr) {
        update(node * 2 + 1, mid + 1, r, ql, qr, add);
    }
    push_up(node);
}

void push_down(int node, int l, int r) {
    if (flag[node]) {
        int mid = (l + r) / 2;
        flag[node * 2] += flag[node];
        flag[node * 2 + 1] += flag[node];
        sum[node * 2] += (mid - l + 1) * flag[node];
        sum[node * 2 + 1] += (r - mid) * flag[node];
        flag[node] = 0;
    }
}

void push_up(int node) {
    sum[node] = sum[node * 2] + sum[node * 2 + 1];
}

LL query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return sum[node];
    }
    int mid = (l + r) / 2;
    LL ret = 0;
    push_down(node, l, r);
    if (ql <= mid)
        ret += query(node * 2, l, mid, ql, qr);
    if (mid < qr)
        ret += query(node * 2 + 1, mid + 1, r, ql, qr);
    return ret;
}
