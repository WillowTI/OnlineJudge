/*
题意：
给定n个数和m个操作
Q代表查询区间最大值
N代表更新数据
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#define maxn 200005

using namespace std;

struct N
{
    int l, r, m;
} tree[maxn * 4];

int num[maxn];

int query(int node, int ql, int qr);
void build(int node, int l, int r);
void update_tree(int node, int l, int r, int pos, int v);

int main()
{
    //freopen("input.txt", "r", stdin);
    int n, m;
    int ql, qr;
    while (scanf("%d%d", &n, &m) == 2)
    {
        memset(tree, 0, sizeof(tree));
        build(1, 1, n);
        for(int i = 0; i < m; i++)
        {
            char s[10];
            scanf("%s", s);
            scanf("%d%d", &ql, &qr);
            if (s[0] == 'Q')
                printf("%d\n", query(1, ql, qr));
            else
                update_tree(1, 1, n, ql, qr);
        }
    }
}

int query(int node, int ql, int qr)
{
    int l = tree[node].l;
    int r = tree[node].r;
    if(l == ql && r == qr)
        return tree[node].m;
    int mid = (l + r) / 2;
    if(qr <= mid)
        return query(node * 2, ql, qr);
    else if(ql > mid)
        return query(node * 2 + 1, ql, qr);
    else
        return max(query(node * 2, ql, mid), query(node * 2 + 1, mid + 1, qr));
}

void build(int node, int l, int r)
{
    tree[node].l = l;
    tree[node].r = r;
    if(l == r)
    {
        scanf("%d", &tree[node].m);
        return ;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    tree[node].m = max(tree[node * 2].m, tree[node * 2 + 1].m);
    return ;
}

void update_tree(int node, int l, int r, int pos, int v)
{
    if (l == r)
        tree[node].m = v;
    else {
        int mid = (l + r) / 2;
        if (pos <= mid)
            update_tree(node * 2, l, mid, pos, v);
        else
            update_tree(node * 2 + 1, mid + 1, r, pos, v);
        tree[node].m = max(tree[node * 2].m, tree[node * 2 + 1].m);
    }
}