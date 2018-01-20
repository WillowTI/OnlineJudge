/**
 * 排序不是以往的字典序，而是AaBaCa...这样的顺序
 * 如何处理重复的情况挺重要的
 * 一开始是弄一个set，把所有产生的字符串往里加，结果TLE了
 * 就想了一个dfs的方法
 */
#include <bits/stdc++.h>
using namespace std;

char data[200], save[200], last[200];
//last是上一个产生的字符串，save是当前产生的字符串
//到达递归终点会把save复制到last
bool used[200];
int mark[200], len;
bool cmp(char c1, char c2);
void dfs(int cur);
int main() {
    //freopen("in.txt", "r", stdin);
	int t;
	scanf("%d", &t);
	for (int i = 'A', j = 'a', k = 0; i <= 'Z'; i++, j++) {
        mark[i] = k++;
        mark[j] = k++;
	}
	while (t --) {
		memset(used, 0, sizeof(used));
		memset(save, 0, sizeof(save));
		memset(last, 0, sizeof(last));
		scanf("%s", data);
		len = strlen(data);
		sort(data, data + len, cmp);
		dfs(0);
	}
	return 0;
}

bool cmp(char c1, char c2) {
    return mark[c1] < mark[c2];
}

void dfs(int cur) {//cur代表当前处理的位数
    if (cur && !strncmp(last, save, cur))//前cur位相同则视作重复
        return;
	if (cur == len) {
        strcpy(last, save);
		puts(save);
		return;
	}
	for (int i = 0; i < len; i++)
		if (!used[i]) {//回溯
			used[i] = 1;
			save[cur] = data[i];//data是排好序的，所以从前往后遍历没有用过的元素
								//这样产生的字符串一定是递增的
			dfs(cur + 1);
			used[i] = 0;
		}
}
