[SegmentTree] - EOJ2525
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



[SegmentTree] - HDU1698
/*
题意：
给定n个节点，初始值都是1
m个操作：把区间的值都设为k
最后输出整个区间的和

这道题最后输出的相当于query(1, n)
如果要查询部分区间
每一步query都要push_down
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



[SegmentTree] - POJ3468
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
