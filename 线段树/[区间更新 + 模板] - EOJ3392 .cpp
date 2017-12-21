/**
 * 区间覆盖为一个数
 * 区间加一个数字在有标记的时候就push_down
 * 这道题有可能覆盖为0，那按照之前的方法就不会push_down
 * 所以还要一个bool数组记录是不是真的被覆盖了
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define maxn 500000 * 4 + 5
#define LL long long
using namespace std;
LL flag[maxn], sum[maxn];
bool is_cover[maxn];
int n;
void build(int node, int l, int r);
void update(int node, int l, int r, int ql, int qr, LL cover);
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
            LL cover;
            scanf("%d%d%lld", &ql, &qr, &cover);
            update(1, 1, n, ql, qr, cover);
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

void update(int node, int l, int r, int ql, int qr, LL cover) {
    if (ql <= l && r <= qr) {
        flag[node] = cover;
        is_cover[node] = 1;
        sum[node] = cover * (r - l + 1);
        return;
    }
    push_down(node, l, r);
    int mid = (l + r) / 2;
    if (ql <= mid)
        update(node * 2, l, mid, ql, qr, cover);
    if (mid < qr)
        update(node * 2 + 1, mid + 1, r, ql, qr, cover);
    push_up(node);
}

void push_down(int node, int l, int r) {
    if (is_cover[node]) {
        int mid = (l + r) / 2;
        flag[node * 2 + 1] = flag[node * 2] = flag[node];
        is_cover[node * 2 + 1] = is_cover[node * 2] = 1;
        sum[node * 2] = (mid - l + 1) * flag[node];
        sum[node * 2 + 1] = (r - mid) * flag[node];
        is_cover[node] = 0;
    }
}

void push_up(int node) {
    sum[node] = sum[node * 2] + sum[node * 2 + 1];
}

LL query(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return sum[node];
    int mid = (l + r) / 2;
    LL ret = 0;
    push_down(node, l, r);
    if (ql <= mid)
        ret += query(node * 2, l, mid, ql, qr);
    if (mid < qr)
        ret += query(node * 2 + 1, mid + 1, r, ql, qr);
    return ret;
}
