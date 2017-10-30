#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
typedef struct {
    int l, r,//左端点，右端点
    lvalue, rvalue,//左端点的值，右端点的值
    ltimes, rtimes,//左端点值出现的次数，右端点值出现的次数
    maxtimes;//当前区间出现次数最多的次数
}T;
int n;//数据规模
T tree[100005 * 4];
void build(int node, int l, int r);//建树
void push_up(int node);//区间合并
int query(int node, int l, int r, int ql, int qr);//查询
int main() {
    //freopen("in.txt", "r", stdin);
    while (scanf("%d", &n) && n) {
        int q;
        memset(tree, 0, sizeof(tree));
        scanf("%d", &q);
        build(1, 1, n);
        for (int i = 0; i < q; i++) {
            int ql, qr;
            scanf("%d%d", &ql, &qr);
            printf("%d\n", query(1, 1, n, ql, qr));
        }
    }
    return 0;
}

void build(int node, int l, int r) {
    tree[node].l = l;
    tree[node].r = r;
    if (l == r) {//当左右区间值相同时说明访问到叶子节点了，输入数据
        int v;
        scanf("%d", &v);
        tree[node].lvalue = tree[node].rvalue = v;
        tree[node].ltimes = tree[node].rtimes = tree[node].maxtimes = 1;
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);//建立左子树
    build(node * 2 + 1, mid + 1, r);//建立右子树
    push_up(node);
}

void push_up(int node) {
    tree[node].lvalue = tree[node * 2].lvalue;//先把当前区间的值更新为默认
    tree[node].rvalue = tree[node * 2 + 1].rvalue;
    tree[node].ltimes = tree[node * 2].ltimes;
    tree[node].rtimes = tree[node * 2 + 1].rtimes;
    tree[node].maxtimes = max(tree[node * 2].maxtimes, tree[node * 2 + 1].maxtimes);
    if (tree[node * 2].rvalue == tree[node * 2 + 1].lvalue) {//当左子区间和右子区间是连通的时候
        if (tree[node * 2].ltimes == tree[node * 2].r - tree[node * 2].l + 1) {//如果左子区间全是一个值
            tree[node].ltimes += tree[node * 2 + 1].ltimes;//那么大区间的左端点的次数加上右子区间左端点的次数
        }
        if (tree[node * 2 + 1].rtimes == tree[node * 2 + 1].r - tree[node * 2 + 1].l + 1) {//同上
            tree[node].rtimes += tree[node * 2].rtimes;
        }
        tree[node].maxtimes = max(tree[node].maxtimes, tree[node * 2].rtimes + tree[node * 2 + 1].ltimes);
        //当前区间出现次数最多的次数和连通的区域长度相比较
    }
}

int query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)//如果当前被完全包含就返回当前区间
        return tree[node].maxtimes;
    int mid = (l + r) / 2;
    if (qr <= mid)//如果中点大于等于右端点，查询左子区间
        return query(node * 2, l, mid, ql, qr);
    if (mid < ql)//如果中点小于左端点，查询右子区间。注意必须严格小于，因为右子区间是从mid + 1开始查询的
        return query(node * 2 + 1, mid + 1, r, ql, qr);
    int ret = max(query(node * 2, l, mid, ql, mid), query(node * 2 + 1, mid + 1, r, mid + 1, qr));//如果中点处于被查询区间范围内就查询左右子区间的值
    if (tree[node * 2].rvalue == tree[node * 2 + 1].lvalue)//如果左右子区间是连通的就再查询连通区间的长度。这里和push_up的思路一样
        //注意必须要有min的比较，因为times只返回和端点值相同的个数，可能会比被查询子区间的长度还长，所以要有min限制长度
        ret = max(ret, min(tree[node * 2].rtimes, mid - ql + 1) + min(tree[node * 2 + 1].ltimes, qr - mid));
    return ret;
}
