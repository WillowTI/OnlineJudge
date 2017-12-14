/**
 * 普通的并查集还不够
 * 并查集保证2个元素的关系能确定
 * mark数组表示两个元素的具体关系是朋友还是敌对
 * 在合并的时候可能会破坏mark数组，所以在路径压缩时要再做一遍异或
 */
#include <stdio.h>
#include <stdlib.h>

int father[100000+1000];
int mark[100000+1000];
int n;

void init(int n){
    int i;
    for(i = 0; i <= n; i++){
        father[i] = i;
        mark[i] = 0;
    }
}

int found(int x){
    if(father[x] == x){
        return x;
    }
    int ret = found(father[x]);
    mark[x] = mark[x]^mark[father[x]];//mark[fx]调整过了，所以整条路径上也要调整
    father[x] = ret;
    return ret;
}

void unite(int x, int y){//fx<->x, x<->y，所以要调整mark[fx]
    int fx = found(x);
    int fy = found(y);
    if(fx == fy) return;
    father[fx] = fy;
    mark[fx] = !(mark[x]^mark[y]);
}

int main()
{
    //freopen("in.txt", "r", stdin);
    int kase;
    scanf("%d", &kase);
    while(kase--){
        int q;
        scanf("%d%d", &n, &q);
        init(n);
        int i;
        for(i = 0; i < q; i++){
            char operation;
            int x, y;
            getchar();
            scanf("%c%d%d", &operation, &x, &y);
            if(operation == 'Q'){
                int fx = found(x);
                int fy = found(y);
                if(fx != fy)
                    printf("Not sure yet.\n");
                else{
                    if(mark[x] == mark[y]) printf("In the same gang.\n");
                    else printf("In different gangs.\n");
                }
            }
            else unite(x, y);
        }
    }
    return 0;
}
