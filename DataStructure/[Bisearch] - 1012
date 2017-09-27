#include <stdio.h>
#include <stdlib.h>
int n;
typedef struct {//用结构体保存数值和下标
    int n, index;
}NODE;
NODE num[2005];
int cmp(const void * a, const void * b);
int bisearch(int target);
int main() {
    //freopen("in.txt", "r", stdin);
    while (scanf("%d", &n) == 1) {
        for (int i = 0; i < n; i++) {
            scanf("%d", &num[i].n);
            num[i].index = i;
        }
        qsort(num, n, sizeof(NODE), cmp);//按数值从小到大排序
        int t;
        scanf("%d", &t);
        printf("%d\n", bisearch(t));
    }
}

int cmp(const void * a, const void * b) {
    if ((*(NODE*)a).n > (*(NODE*)b).n)
        return 1;
    return -1;
}

int bisearch(int target) {
    int l = 0;
    int r = n - 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (target == num[mid].n)//如果找到了返回下标
            return num[mid].index;
        if (target < num[mid].n)//如果目标较小，右端点左移。
            r = mid - 1;//注意必须减一或加一，否则一直满足l <= r，进入死循环
        else//如果目标较大，左端点右移
            l = mid + 1;
    }
    return -1;
}
