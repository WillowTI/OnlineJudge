/*
题意：
给定n个数和m个操作
每个操作有2种：
Q代表查询区间和
C代表区间所有的值加一个数字

与HDU1698不同，那道题是把区间所有的数字全部修改为某个数字
而这道题是区间所有值加一个变量
对应的mark操作前者是直接赋值(+=)
后者是叠加(+=)
val操作也要有所改变

其余的各种函数和之前的2道题大同小异，就简要注释了
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxn 100000
#define LL long long
typedef struct {
    int l, r;
    LL mark, val;//由于可能会超过int的范围，所以值用long long保存
}T;
T tree[maxn * 4 + 5];
int n, q;
void push_down(int node, int l, int r);
void push_up(int node);
void build(int node, int l, int r);
void update(int node, int l, int r, int ql, int qr, LL add);
LL query(int node, int l, int r, int ql, int qr);
int main() {
    //freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &q);
    memset(tree, 0, sizeof(tree));
    build(1, 1, n);
    while (q--) {
        char op[10];
        scanf("%s", op);
        if (op[0] == 'Q') {
            int ql, qr;
            scanf("%d%d", &ql, &qr);
            printf("%lld\n", query(1, 1, n, ql, qr));
        } else {
            int ql, qr;
            LL add;
            scanf("%d%d%lld", &ql, &qr, &add);
            update(1, 1, n, ql, qr, add);
        }
    }
    return 0;
}

void build(int node, int l, int r) {
    tree[node].l = l;
    tree[node].r = r;
    if (l == r) {
        scanf("%lld", &tree[node].val);
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    push_up(node);
}

void push_up(int node) {
    tree[node].val = tree[node * 2].val + tree[node * 2 + 1].val;
}

void push_down(int node, int l, int r) {
    if (tree[node].mark) {
        int mid = (l + r) / 2;
        tree[node * 2].mark += tree[node].mark;//mark是叠加的，不是直接赋值
        tree[node * 2 + 1].mark += tree[node].mark;
        tree[node * 2].val += (LL)(mid - l + 1) * tree[node].mark;
        tree[node * 2 + 1].val += (LL)(r - mid) * tree[node].mark;
        tree[node].mark = 0;
    }
}

void update(int node, int l, int r, int ql, int qr, LL add) {
    int mid = (l + r) / 2;
    if (ql <= l && r <= qr) {
        tree[node].mark += add;//同样，mark值叠加
        tree[node].val += (LL)(r - l + 1) * add;
        return;
    }
    push_down(node, l, r);
    if (ql <= mid) {
        update(node * 2, l, mid, ql, qr, add);
    }
    if (mid < qr) {
        update(node * 2 + 1, mid + 1, r, ql, qr, add);
    }
    push_up(node);
}

LL query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {//如果当前区间被完全包含就直接返回
        return tree[node].val;
    }
    int mid = (l + r) / 2;
    LL lans = 0, rans = 0;//否则就是左子区间 + 右子区间。和EOJ2525的写法类似
    push_down(node, l, r);
    if (ql <= mid)
        lans = query(node * 2, l, mid, ql, qr);
    if (qr > mid)
        rans = query(node * 2 + 1, mid + 1, r, ql, qr);
    return lans + rans;
}