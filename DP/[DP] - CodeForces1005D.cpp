/**
 * 能被3整除的数字每位之和能被3整除
 * 记录前缀和
 * a[i]表示到i的答案
 * 对于a[i]，取a[i - 1]和a[j] + 1（j为上一个前缀和与当前前缀和相等的位置为）之间的较大者
 * 用fin数组表示上一个前缀和为i的位置
 */
#include "bits/stdc++.h"
#define FOR(i, a, b) for (int (i) = (a); (i) < (b); (i)++)
#define FORD(i, a, b) for (int (i) = (a); (i) > (b); (i)--)
using namespace std;
typedef long long LL;
const int MAXN = 2e5+5;
char s[MAXN];
int n;
int a[MAXN], fin[3];

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%s", s);
    n = strlen(s);
    memset(fin, -1, sizeof fin);
    fin[0] = 0;
    int r = 0;
    FOR (i, 1, n + 1) {
        r = (r + s[i - 1] - '0') % 3;
        a[i] = a[i - 1];
        if (fin[r] != -1) a[i] = max(a[i], a[fin[r]] + 1);
        fin[r] = i;
    }
    cout << a[n] << endl;
    return 0;
}


/**
 * 看到的另一个做法
 * 往后读，只要能凑出3的倍数就答案加一，数据归零
 * 前缀和没有什么问题
 * 当长度为3时一定能凑出一个3的倍数，这个规律挺难找的
 * 想法很奇妙
 */

#include "iostream"
#include "string"
using namespace std;
int main()
{
    int c=0,len=0,ans=0;
    string s;
    cin>>s;
    for(int i=0;i<s.size();i++){
        len++;
        c=c+(s[i]-'0');
        if(c%3==0||s[i]%3==0||len>=3){
            c=0;
            len=0;
            ans++;
        }
    }
    cout<<ans<<endl;
}