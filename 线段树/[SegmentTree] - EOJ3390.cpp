/**
 *题意：
 *先输入一些数字
 *然后有2种命令
 *1 a b：把第a个数字改为b
 *2 a b：查询[a,b]的区间和，区间最大值，区间最小值
 *一开始sum, mx, mn都是LL类型的，但是在build的时候就不行了
 *max(), min()2个函数也不能准确识别类型，所以还是改回int类型了，反正数据范围不会爆int
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define LL long long
using namespace std;
typedef struct {
    LL sum;
    int mn, mx;
}T;
T tree[5 * 100000 * 4 + 5];
int n, q;
void build(int node, int l, int r);
void update(int node, int l, int r, int pos, int val);
LL query_sum(int node, int l, int r, int ql, int qr);
int query_max(int node, int l, int r, int ql, int qr);
int query_min(int node, int l, int r, int ql, int qr);
int main() {
    //freopen("in.txt", "r", stdin);
    memset(tree, 0, sizeof(tree));
    scanf("%d", &n);
    build(1, 1, n);
    scanf("%d", &q);
    while (q--) {
        int op, ql, qr;
        scanf("%d%d%d", &op, &ql, &qr);
        if (op == 1)
            update(1, 1, n, ql, qr);
        else {
            printf("%lld %d %d\n", query_sum(1, 1, n, ql, qr),
                                    query_max(1, 1, n, ql, qr),
                                    query_min(1, 1, n, ql, qr));
        }
    }
    return 0;
}

void build(int node, int l, int r) {
    if (l == r) {
        scanf("%d", &tree[node].mn);
        tree[node].mx = tree[node].sum = tree[node].mn;
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    tree[node].sum = tree[node * 2].sum + tree[node * 2 + 1].sum;
    tree[node].mx = max(tree[node * 2].mx, tree[node * 2 + 1].mx);
    tree[node].mn = min(tree[node * 2].mn, tree[node * 2 + 1].mn);
}

void update(int node, int l, int r, int pos, int val) {
    if (l == pos && pos == r) {
        tree[node].mn = tree[node].mx = tree[node].sum = val;
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid)
        update(node * 2, l, mid, pos, val);
    else
        update(node * 2 + 1, mid + 1, r, pos, val);
    tree[node].sum = tree[node * 2].sum + tree[node * 2 + 1].sum;
    tree[node].mx = max(tree[node * 2].mx, tree[node * 2 + 1].mx);
    tree[node].mn = min(tree[node * 2].mn, tree[node * 2 + 1].mn);
}

LL query_sum(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return tree[node].sum;
    int mid = (l + r) / 2;
    LL ret = 0;
    if (ql <= mid)
        ret += query_sum(node * 2, l, mid, ql, qr);
    if (mid < qr)
        ret += query_sum(node * 2 + 1, mid + 1, r, ql, qr);
    return ret;
}

int query_max(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return tree[node].mx;
    int mid = (l + r) / 2;
    int ret = -10000001;
    if (ql <= mid)
        ret = max(ret, query_max(node * 2, l, mid, ql, qr));
    if (mid < qr)
        ret = max(ret, query_max(node * 2 + 1, mid + 1, r, ql, qr));
    return ret;
}

int query_min(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return tree[node].mn;
    int mid = (l + r) / 2;
    int ret = 10000001;
    if (ql <= mid)
        ret = min(ret, query_min(node * 2, l, mid, ql, qr));
    if (mid < qr)
        ret = min(ret, query_min(node * 2 + 1, mid + 1, r, ql, qr));
    return ret;
}
