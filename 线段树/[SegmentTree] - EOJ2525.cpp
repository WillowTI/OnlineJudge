/*
题意：
给定n盏关闭的灯和m次操作
每个操作分为1和0两种
0代表把区间里灯的状态全部反转
1代表询问区间里打开的灯的数目
区间从1开始计数
*/

#include <stdio.h>
#include <string.h>
#define maxn 100000
typedef struct {
    int l, r, m, mark;//分别代表左端点，右端点，打开的灯的数量，延迟标记（1代表有，0代表没有）
}T;
T tree[maxn * 4 + 5];
int n, m;
void build(int node, int l, int r);//建树
void update(int node, int l, int r, int ql, int qr);//把区间的灯全部反转
void push_down(int node, int l, int r);//把延迟标记往下压
void push_up(int node);//区间合并
int query(int node, int l, int r, int ql, int qr);
int main() {
    //freopen("in.txt", "r", stdin);
    memset(tree, 0, sizeof(tree));
    scanf("%d%d", &n, &m);
    build(1, 1, n);
    while (m--) {
        int op, ql, qr;
        scanf("%d%d%d", &op, &ql, &qr);
        if (!op)
            update(1, 1, n, ql, qr);
        else
            printf("%d\n", query(1, 1, n, ql, qr));

    }
    return 0;
}

void build(int node, int l, int r) {
    tree[node].l = l;
    tree[node].r = r;
    if (l != r) {
        int mid = (l + r) / 2;
        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);
    }
}

void update(int node, int l, int r, int ql, int qr) {
    int mid = (l + r) / 2;
    if (ql <= l && r <= qr) {//如果当前区间被完全包含
        tree[node].m = r - l + 1 - tree[node].m;//打开的灯的数目更新
        tree[node].mark++;//标记更新
        tree[node].mark %= 2;
        return;
    }
    push_down(node, l, r);//如果当前区间不是完全包含说明部分内容会被改变，先把标记往下压
    if (ql <= mid) {//更新左子区间
        update(node * 2, l, mid, ql, qr);
    }
    if (mid < qr) {//更新右子区间
        update(node * 2 + 1, mid + 1, r, ql, qr);
    }
    push_up(node);//区间合并
}

int query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return tree[node].m;
    int lans = 0;//左子区间打开的灯的数目
    int rans = 0;//右子区间打开的灯的数目
    int mid = (l + r) / 2;
    push_down(node, l, r);//如果当前区间不是完全包含说明可能会查到没有完全更新的节点，把标记往下压
    if (ql <= mid) {
        lans = query(node * 2, l, mid, ql, qr);
    }
    if (mid < qr) {
        rans = query(node * 2 + 1, mid + 1, r, ql, qr);
    }
    return lans + rans;//返回二者的和
}

void push_down(int node, int l, int r) {
    if (tree[node].mark) {//当有标记时才操作
        int mid = (l + r) / 2;
        tree[node * 2].mark++;//左子节点的信息更新
        tree[node * 2].mark %= 2;
        tree[node * 2].m = mid - l + 1 - tree[node * 2].m;
        tree[node * 2 + 1].mark++;//右子节点的信息更新
        tree[node * 2 + 1].mark %= 2;
        tree[node * 2 + 1].m = r - mid - tree[node * 2 + 1].m;
        tree[node].mark = 0;//标记归零
    }
}

void push_up(int node) {//区间合并就是当前结点打开的灯的数目等于2个子区间的数目之和
    tree[node].m = tree[node * 2].m + tree[node * 2 + 1].m;
}