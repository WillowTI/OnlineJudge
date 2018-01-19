#include <cstdio>
#include <map>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>

using namespace std;
int parent[100005];//存储父节点
map <string, int> mapstring;//将string映射成int(出现的顺序，从0开始计数)

void makeset(int x);//建立节点数组
int findset(int x);//返回某个节点的父节点
int unionset(int x, int y);//把x和y合并在一起，返回公共父节点

int main() {
    //freopen("in.txt", "r", stdin);
    int cas;
    scanf("%d", &cas);
    while (cas--) {
        memset(parent, 0, sizeof(parent));
        mapstring.clear();
        std::map<string, int>::iterator it;
        int n;
        scanf("%d", &n);
        string s;
        for (int i = 0; i < n; i++) {
            string s1, s2;
            cin >> s1 >> s2;
            it = mapstring.find(s1);//如果没有找到这个string，find函数返回迭代器的尾部
            if (it == mapstring.end()) {//如果当前map中不存在输入的string就添加进去
                mapstring[s1] = mapstring.size() - 1;//mapstring的大小总比下标多一，所以要减一
                makeset(mapstring[s1]);
            }
            it = mapstring.find(s2);
            if (it == mapstring.end()) {
                mapstring[s2] = mapstring.size() - 1;
                makeset(mapstring[s2]);
            }
            int index = unionset(mapstring[s1], mapstring[s2]);//把两个int合并
            int ans = 0;
            for (int i = 0; i < mapstring.size(); i++)//答案就是parent数组中值为父节点的元素数量，遍历求得
                if (parent[i] == index)
                    ans++;
            printf("%d\n", ans);
        }

    }
    return 0;
}

void makeset(int x) {
    parent[x] = x;
}

int findset(int x) {
    return parent[x];
}

int unionset(int x, int y) {
    int i = min(findset(x), findset(y));
    int j = max(findset(x), findset(y));
    for (int k = 0; k < mapstring.size(); k++)
        if (parent[k] == j)
            parent[k] = i;
    return i;
}
