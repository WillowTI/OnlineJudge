#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int sudoku[9][9] = {{0}};//存放数独
bool dfs(int location);//location为当前处理的坐标，从上往下，从左往右递增，从0到80
bool isvalid(int x, int y, int val);//判断val填在(i,j)是否合法
int main() {
    //freopen("in.txt", "r", stdin);
    //freopen("out.txt", "w", stdout);
    bool first = true;
    char s[10];
    while (scanf("%s", s) == 1) {
        if (first)
            first = false;
        else
            printf("\n");
        memset(sudoku, 0, sizeof(sudoku));
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (i != 0 || j != 0)//对(0,0)特判，因为之前已经记录下了
                    scanf("%s", s);
                if (s[0] == '?')//把'?'当成0
                    sudoku[i][j] = 0;
                else
                    sudoku[i][j] = s[0] - '0';
            }
        }
        dfs(0);
        for (int i = 0; i < 9; i++) 
            for (int j = 0; j < 9; j++) 
                printf("%d%c", sudoku[i][j], j == 8 ? '\n' : ' ');
    }
    return 0;
}

bool dfs(int location) {
	if (location == 81)//到达递归终点
		return true;
	int x = location / 9;//获取横纵坐标
	int y = location % 9;
	if (!sudoku[x][y]) {//如果这个点是'?'，那么要把它求出来
		for (int i = 1; i <= 9; i++) {//从1到9尝试
			sudoku[x][y] = i;
			if (isvalid(x, y, sudoku[x][y]))//如果填进去是合法的
                if (dfs(location + 1))//那就遍历下一个位置，如果处理成功
                    return true;//那就返回true
            sudoku[x][y] = 0;//如果处理失败，那就要还原为0。
                             //如果不还原，那这个点就一直是9，后面在处理的时候就跳过这个点了
                             //而且在处理和它同一行或同一列或同一个九宫格的点的时候，9就标记为已使用了
                             //一开始没有意识到，导致输出很多的9
		}
	}
	else//不是的话就处理下一个点
		return dfs(location + 1);
    return false;
}

bool isvalid(int x, int y, int val) {
	for (int i = 0 ;i < 9; i++) {//先判断行列
        if (i != y && sudoku[x][i] == val)//如果这个坐标不与被检查的坐标重合而值相同那就是不合法的
            return false;
        if (i != x && sudoku[i][y] == val)
            return false;
	}
	for (int i = x / 3 * 3; i < x / 3 * 3 + 3; i++) //再判断九宫格
        for (int j = y / 3 * 3; j < y / 3 * 3 + 3; j++)
            if (i != x && j != y && sudoku[i][j] == val)
                return false;
	return true;
}
