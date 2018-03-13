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
    int value, group;
    Node(int v, int g) {
        value = v;
        group = g;
    }
    bool operator < (const Node n) const {
        return value > n.value;
    }
};
void MergeSort(int l, int r, int k);
void Merge(int l, int r, int k);
int main() {
    freopen("in.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", a + i);
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    MergeSort(0, n - 1, 2);
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
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
    int st[100], pos[100];
    int tk = k;
    int tl = l;
    int n = r - l;
    for (int i = 0; i < k; i++) {
        if (tl > r) break;
        pos[i] = st[i] = tl;
        int next = n / tk;
        tl += next + 1;
        n -= next + 1;
        tk--;
    }
    st[k] = r + 1;
    tl = l;
    priority_queue<Node> pq;
    for (int i = 0; i < k - tk; i++)
        pq.push(Node(a[pos[i]++], i));
    for (int i = 0; i <= r - l; i++) {
        Node cur = pq.top();
        pq.pop();
        tmp[tl++] = cur.value;
        int index = cur.group;
        if (pos[index] < st[index + 1])
            pq.push(Node(a[pos[index]++], index));
    }
    for (int i = l; i <= r; i++)
        a[i] = tmp[i];
}
