#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    char c;
    struct node * next;
}NODE;
NODE * top = 0;
void push();//进栈
void pop();//出栈
int n;
int main()
{
    //freopen("in.txt", "r", stdin);
    while (scanf("%d\n", &n) == 1) {
        push();
        pop();
        top = 0;//每次执行完操作把栈顶指针复原
    }
}

void push() {
    NODE * cur;
    for (int i = 0; i < n; i++) {
        cur = (NODE*)malloc(sizeof(NODE));
        scanf("%c", &(cur -> c));
        getchar();//读取空格或换行符
        cur -> next = top;//把当前的节点的下一个指向栈顶指针
        top = cur;//更新栈顶指针
    }
}

void pop() {
    NODE * cur = top;
    while (cur) {//遍历出栈
        printf("%c%c", cur -> c, cur -> next == 0 ? '\n' : ' ');
        cur = cur -> next;
    }
}
