/*
题意：
给定n个节点，初始值都是1
m个操作：把区间的值都设为k
最后输出整个区间的和

这道题最后输出的相当于query(1, n)
如果要查询部分区间的话那么每一步query都要push_down
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxn 100000
typedef struct {
    int l, r, mark, val;//左端点，右端点，延迟标记，和
}T;
T tree[maxn * 4 + 5];
int n, m;
void push_down(int node, int l, int r);
void push_up(int node);
void build(int node, int l, int r);
void update(int node, int l, int r, int ql, int qr, int val);
int main() {
    //freopen("in.txt", "r", stdin);
    int cas;
    scanf("%d", &cas);
    for (int t = 0; t < cas; t++) {
        memset(tree, 0, sizeof(tree));
        scanf("%d%d", &n, &m);
        build(1, 1, n);
        while (m--) {
            int ql, qr, val;
            scanf("%d%d%d", &ql, &qr, &val);
            update(1, 1, n, ql, qr, val);
        }
        printf("Case %d: The total value of the hook is %d.\n", t + 1, tree[1].val);
    }
    return 0;
}

void build(int node, int l, int r) {
    tree[node].l = l;
    tree[node].r = r;
    if (l == r) {
        tree[node].val = 1;//初始化设为1
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    push_up(node);
}

void push_up(int node) {//区间更新
    tree[node].val = tree[node * 2].val + tree[node * 2 + 1].val;
}

void push_down(int node, int l, int r) {
    if (tree[node].mark) {//标记往下压
        int mid = (l + r) / 2;
        tree[node * 2 + 1].mark = tree[node * 2].mark = tree[node].mark;//左右区间标记更新
        tree[node * 2].val = (mid - l + 1) * tree[node * 2].mark;//左子区间的和更新
        tree[node * 2 + 1].val = (r - mid) * tree[node * 2 + 1].mark;//右子区间的和更新
        tree[node].mark = 0;//标记归零
    }
}

void update(int node, int l, int r, int ql, int qr, int val) {
    int mid = (l + r) / 2;
    if (ql <= l && r <= qr) {
        tree[node].mark = val;
        tree[node].val = (r - l + 1) * val;
        return;
    }
    push_down(node, l, r);
    if (ql <= mid) {
        update(node * 2, l, mid, ql, qr, val);
    }
    if (mid < qr) {
        update(node * 2 + 1, mid + 1, r, ql, qr, val);
    }
    push_up(node);
}