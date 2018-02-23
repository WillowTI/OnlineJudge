/**
 * 用数组实现的Trie树
 * 当str[i][j]不为0时，说明有字符重复
 * 下一个字符放在第str[i][j]行，也就是行坐标更新
 * 注意横坐标i不代表前i个字符相同，只是一个计数器功能
 * dic记录一个字符串读进来后root对应一个字符串下标
 * 至于大小1e5是随便开的
 */
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
int str[100005][10], dic[100005], cas, sign, root, n;
char in[15];
void add(char* s, int i);
int main() {
    //freopen("in.txt", "r", stdin);
    scanf("%d", &cas);
    while (cas--) {
        memset(str, 0, sizeof(str));
        memset(dic, 0, sizeof(dic));
        root = 1;
        sign = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%s", in);
            if (sign)
                continue;
            add(in, i);
        }
        if (sign)
            puts("NO");
        else
            puts("YES");
    }
    return 0;
}

void add(char* s, int i) {
    int u = 0, ans = 0;
    while (*s) {
        if (!str[u][*s - '0']) {
            str[u][*s - '0'] = root++;
            ans++;
        }
        else if (dic[str[u][*s - '0']])
            sign = 1;
        u = str[u][*s - '0'];
        s++;
    }
    if (!ans)
        sign = 1;
    dic[u] = i;
}
