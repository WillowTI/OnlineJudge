/**
 *题意：
 *2种操作
 *1为查询第一次满足长度为n的线段，并且更新为占有状态
 *输出起点，没有则输出0
 *2为把起点为a，长度为n的线段清空
 */


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
typedef struct {
    int lsum, rsum, sum, mark;//mark-1时代表区间有0有1，0为全空，1为全满
    //lsum，rsum分别代表左、右端连续空余的房间
    //sum代表区间最大连续空余房间
}T;
T tree[50000 * 4 + 5];
int n, m;
void build(int node, int l, int r);
void update(int node, int l, int r, int ql, int qr, int val);
int query(int node, int l, int r, int len);
void push_up(int node, int l, int r);
void push_down(int node, int l, int r);
int main() {
    //freopen("in.txt", "r", stdin);
    memset(tree, 0, sizeof(tree));
    scanf("%d%d", &n, &m);
    build(1, 1, n);
    for (int i = 0; i < m; i++) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int a;
            scanf("%d", &a);
            if (tree[1].sum < a)//如果连最大区间的空余量都无法满足，那一定不行
                puts("0");
            else {
                int pos = query(1, 1, n, a);//否则查找第一个长度为a的出现地方
                printf("%d\n", pos);
                update(1, 1, n, pos, pos + a - 1, 1);//把这段区间覆盖为1
            }
        } else {
            int a, b;
            scanf("%d%d", &a, &b);
            update(1, 1, n, a, a + b - 1, 0);//把这段区间覆盖为0
        }
    }
    return 0;
}

void build(int node, int l, int r) {
    tree[node].mark = -1;//一开始标记初始化为-1，表示不用push_down
    tree[node].lsum = tree[node].rsum = tree[node].sum = r - l + 1;
    if (l == r)
        return;
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
}

void push_down(int node, int l, int r) {
    if (tree[node].mark != -1) {//当标记不为-1操作，区间信息更新和EOJ2458很像
        int mid = (l + r) / 2;
        tree[node * 2].mark = tree[node * 2 + 1].mark = tree[node].mark;
        tree[node * 2].lsum = tree[node * 2].rsum = tree[node * 2].sum = tree[node].mark ? 0 : mid - l + 1;
        tree[node * 2 + 1].lsum = tree[node * 2 + 1].rsum = tree[node * 2 + 1].sum = tree[node].mark ? 0 : r - mid;
        tree[node].mark = -1;
    }
}

void update(int node, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) {
        tree[node].mark = val;
        tree[node].lsum = tree[node].rsum = tree[node].sum = val ? 0 : r - l + 1;//0为清空，那么sum值就是区间长度，1为住满，更新为0
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    if (ql <= mid)
        update(node * 2, l, mid, ql, qr, val);
    if (mid < qr)
        update(node * 2 + 1, mid + 1, r, ql, qr, val);
    push_up(node, l, r);
}

void push_up(int node, int l, int r) {
    tree[node].lsum = tree[node * 2].lsum;
    tree[node].rsum = tree[node * 2 + 1].rsum;
    int mid = (l + r) / 2;
    if (tree[node].lsum == mid - l + 1)
        tree[node].lsum += tree[node * 2 + 1].lsum;
    if (tree[node].rsum == r - mid)
        tree[node].rsum += tree[node * 2].rsum;
    tree[node].sum = max(tree[node * 2].sum, tree[node * 2 + 1].sum);
    tree[node].sum = max(tree[node].sum, tree[node * 2].rsum + tree[node * 2 + 1].lsum);
}

int query(int node, int l, int r, int len) {
    push_down(node, l, r);
    int mid = (l + r) / 2;
    //查询区间的顺序很重要，确保是第一次出现满足要求长度的起点，所以要从左往右检查
    if (tree[node * 2].sum >= len)//先检查左子区间
        return query(node * 2, l, mid, len);
    else if (tree[node * 2].rsum + tree[node * 2 + 1].lsum >= len)//再检查区间交界处
        return mid - tree[node * 2].rsum + 1;//事实上这里就是递归终点，所以开头没有return的语句也不会死循环
    else//最后检查右子区间
        return query(node * 2 + 1, mid + 1, r, len);
}
