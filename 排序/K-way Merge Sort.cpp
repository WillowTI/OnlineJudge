/**
 * 实际运行效率并不高
 * 据说用堆保存vector的指针效果会好点
 */
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <ctime>
#include <algorithm>
#include <queue>
typedef long long LL;
using namespace std;
int a[1000005], tmp[1000005];

struct Node {
    int value, group;//值，来自子数组的下标
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
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", a + i);
    MergeSort(0, n - 1, 2);
    for (int i = 2; i <= 100; i++) {
        time_t start = clock();
        MergeSort(0, n - 1, i);
        cout << i << " " << (double)(clock() - start) / CLOCKS_PER_SEC << endl;
    }
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
    int st[k + 1], pos[k];//pos记录每个数组指到第几个元素
    int tk = k;
    int tl = l;
    int n = r - l;
    for (int i = 0; i < k; i++) {//划分数组
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
        Node cur = pq.top();//每次取出最小的值
        pq.pop();
        tmp[tl++] = cur.value;
        int index = cur.group;
        if (pos[index] < st[index + 1])//如果还没有取完数组内的元素就继续取
            pq.push(Node(a[pos[index]++], index));
    }
    for (int i = l; i <= r; i++)
        a[i] = tmp[i];
}