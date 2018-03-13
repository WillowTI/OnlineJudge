#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
typedef long long LL;
using namespace std;
int a[100], tmp[100];

struct Node {
    int pos, value;
    Node(int p, int v) {
        pos= p;
        value = v;
    }
    bool operator < (const Node n) const {
        return value < n.value;
    }
};
void MergeSort(int l, int r, int k);
void Merge(int l, int r, int k);
int main() {
    freopen("F:\\TestCode\\TestCLion\\in.txt", "r", stdin);
    int n, k;
    scanf("%d%d", &n, &k);
    int st = 0, tk = k, tn = n - 1;
//    for (int i = 0; i < k; i++) {
//        int next = tn / tk;
//        printf("%d\n", tn);
//        printf("%d %d\n", st, st + next);
//        st += next + 1;
//        tn -= next + 1;
//        tk--;
//    }

    for (int i = 0; i < n; i++)
        scanf("%d", a + i);
    MergeSort(0, n - 1, 4);
    return 0;
}

void MergeSort(int l, int r, int k) {
    if (l < r) {
        int n = r - l;
        int tl = l;
        int tk = k;
        for (int i = 0; i < k; i++) {
            int next = n / tk;
            MergeSort(tl, tl + next, k);
            tl += next + 1;
            n -= next + 1;
            tk--;
        }
        Merge(l, r, k);
    }
}

void Merge(int l, int r, int k) {
    int st[k + 1], pos[k];
    int tk = k;
    int tl = l;
    int n = r - l;
    for (int i = 0; i < k; i++) {
        pos[i] = st[i] = tl;
        int next = n / tk;
        tl += next + 1;
        n -= next + 1;
        tk--;
    }
    st[k] = r + 1;
    priority_queue<Node> pq;
    for (int i = 0; i < k; i++)
        pq.push(Node(a[pos[i]], pos[i]));
    for (int i = 0; i <= r - l; i++) {

    }
}