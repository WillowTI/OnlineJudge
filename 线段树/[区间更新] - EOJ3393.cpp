/**
 * 涉及到2种区间修改的操作
 * 区间赋值会把区间增加给覆盖掉
 * 所以要把flag_add数组清零
 * 在update是如此
 * 在push_down中也是如此（我就是忘记了在push_down中修改所以一直WA）
 * long long的最大值是LLONG_MAX，最小值是LLONG_MIN
 * typedef long long LL比
 * #define LL long long快
 */
#include <bits/stdc++.h>
#define maxn (500000 * 4 + 5)
typedef long long LL;
using namespace std;
LL sum[maxn], mn[maxn], mx[maxn], flag_add[maxn], flag_cover[maxn];
bool is_cover[maxn];
void build(int node, int l, int r);
void push_up(int node);
void update_add(int node, int l, int r, int ql, int qr, LL add);
void update_cover(int node, int l, int r, int ql, int qr, LL cover);
void push_down(int node, int l, int r);
LL query(int node, int l, int r, int ql, int qr, LL &qmx, LL &qmn);
int main() {
    //freopen("in.txt", "r", stdin);
    int n, q;
    scanf("%d", &n);
    build(1, 1, n);
    scanf("%d", &q);
    while (q--) {
        int op;
        scanf("%d", &op);
        if (op == 1) {
            int l, r;
            LL add;
            scanf("%d%d%lld", &l, &r, &add);
            update_add(1, 1, n, l, r, add);
        } else if (op == 2) {
            int l, r;
            LL cover;
            scanf("%d%d%lld", &l, &r, &cover);
            update_cover(1, 1, n, l, r, cover);
        } else {
            int ql, qr;
            scanf("%d%d", &ql, &qr);
            LL qmx = LLONG_MIN;
            LL qmn = LLONG_MAX;
            LL sum = query(1, 1, n, ql, qr, qmx, qmn);
            printf("%lld %lld %lld\n", sum, qmx, qmn);
        }
    }
    return 0;
}

void build(int node, int l, int r) {
    if (l == r) {
        scanf("%lld", &sum[node]);
        mn[node] = mx[node] = sum[node];
        return;
    }
    int m = (l + r) / 2;
    build(node * 2, l, m);
    build(node * 2 + 1, m + 1, r);
    push_up(node);
}

void push_up(int node) {
    sum[node] = sum[node * 2] + sum[node * 2 + 1];
    mx[node] = max(mx[node * 2], mx[node * 2 + 1]);
    mn[node] = min(mn[node * 2], mn[node * 2 + 1]);
}

void update_add(int node, int l, int r, int ql, int qr, LL add) {
    if (ql <= l && r <= qr) {
        flag_add[node] += add;
        sum[node] += (r - l + 1) * add;
        mn[node] += add;
        mx[node] += add;
        return;
    }
    int m = (l + r) / 2;
    push_down(node, l, r);
    if (ql <= m)
        update_add(node * 2, l, m, ql, qr, add);
    if (m < qr)
        update_add(node * 2 + 1, m + 1, r, ql, qr, add);
    push_up(node);
}

void update_cover(int node, int l, int r, int ql, int qr, LL cover) {
    if (ql <= l && r <= qr) {
        flag_add[node] = 0;//add清零
        flag_cover[node] = cover;
        is_cover[node] = 1;
        mn[node] = mx[node] = cover;
        sum[node] = (r - l + 1) * cover;
        return;
    }
    int m = (l + r) / 2;
    push_down(node, l, r);
    if (ql <= m)
        update_cover(node * 2, l, m, ql, qr, cover);
    if (m < qr)
        update_cover(node * 2 + 1, m + 1, r, ql, qr, cover);
    push_up(node);
}

LL query(int node, int l, int r, int ql, int qr, LL& qmx, LL& qmn) {
    if (ql <= l && r <= qr) {
        qmx = max(qmx, mx[node]);
        qmn = min(qmn, mn[node]);
        return sum[node];
    }
    int m = (l + r) / 2;
    push_down(node, l, r);
    LL ret = 0;
    if (ql <= m)
        ret += query(node * 2, l, m, ql, qr, qmx, qmn);
    if (m < qr)
        ret += query(node * 2 + 1, m + 1, r, ql, qr, qmx, qmn);
    return ret;
}

void push_down(int node, int l, int r) {
    int m = (l + r) / 2;
    if (is_cover[node]) {
        flag_cover[node * 2] = flag_cover[node * 2 + 1] = flag_cover[node];
        is_cover[node * 2] = is_cover[node * 2 + 1] = is_cover[node];
        flag_add[node * 2] = flag_add[node * 2 + 1] = 0;//同样add清零
        sum[node * 2] = (m - l + 1) * flag_cover[node];
        sum[node * 2 + 1] = (r - m) * flag_cover[node];
        mn[node * 2] = mn[node * 2 + 1] = mx[node * 2] = mx[node * 2 + 1] = flag_cover[node];
        is_cover[node] = 0;
    }
    if (flag_add[node]) {
        flag_add[node * 2] += flag_add[node];
        flag_add[node * 2 + 1] += flag_add[node];
        sum[node * 2] += (m - l + 1) * flag_add[node];
        sum[node * 2 + 1] += (r - m) * flag_add[node];
        mn[node * 2] += flag_add[node];
        mx[node * 2] += flag_add[node];
        mn[node * 2 + 1] += flag_add[node];
        mx[node * 2 + 1] += flag_add[node];
        flag_add[node] = 0;
    }
}
