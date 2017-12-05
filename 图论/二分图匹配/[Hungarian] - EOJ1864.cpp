/**
  * 构造二分图有点不太好想
  * 输入的单词为一边，正方体为另一边
  * 当单词的第i个字符出现在第j个正方体时，connect[i][j]=1
  * 如果最大匹配数=单词长度则视为成功
  */
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;
int n, m, pos, word_len;
int ans[55], match[55];//ans记录成功匹配单词的下标，match记录哪个字符与cube[i]相连，-1为空
bool connect[55][55], vis[55];
char cube[51][10], word[55];
void init_connect();//初始化connect
int has_word(int word_index, int cube_index);//查询正方体中是否包含了某个字符
bool path(int x);
int main() {
    //freopen("in.txt", "r", stdin);
    while (scanf("%d%d", &n, &m) == 2) {
        pos = 0;
        memset(ans, 0, sizeof(ans));
        for (int i = 0; i < n; i++)
            scanf("%s", cube[i]);
        for (int i = 0; i < m; i++) {
            scanf("%s", word);
            word_len = strlen(word);
            if (word_len > n)//如果单词长度比正方体个数还多，那一定无法满足
                continue;
            memset(connect, 0, sizeof(connect));
            memset(match, -1, sizeof(match));//由于word字符串是从0开始的，所以-1记为空
            init_connect();
            int match_num = 0;
            for (int j = 0; j < word_len; j++) {
                memset(vis, 0, sizeof(vis));
                if (path(j))//如果path成功那么匹配数加一
                    match_num++;
            }
            if (match_num == word_len)//匹配成功就添加到答案数组中
                ans[pos++] = i;
        }
        if (!pos)//没有一个答案
            printf("-1\n");
        else {
            for (int i = 0; i < pos; i++)
                printf("%d%c", ans[i], i == pos - 1 ? '\n' : ' ');
        }
    }
    return 0;
}

void init_connect() {
    for (int i = 0; i < word_len; i++)
        for (int j = 0; j < n; j++)
            connect[i][j] = has_word(i, j);
}

int has_word(int word_index, int cube_index) {
    for (int i = 0; i < 6; i++)
        if (word[word_index] == cube[cube_index][i])
            return 1;
    return 0;
}

bool path(int x) {
    for (int i = 0; i < n; i++) {
        if (connect[x][i] && !vis[i]) {//如果第x个字符和第i个正方体有连接
                                       //而且正方体还没有在这一次path中被访问过
            vis[i] = 1;
            if (match[i] == -1 || path(match[i])) {//这里match=-1表示空，另一道题match=0表示空
                match[i] = x;//更新match值
                return 1;
            }
        }
    }
    return 0;
}
