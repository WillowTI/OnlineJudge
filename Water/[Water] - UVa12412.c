练打字用的，很啰嗦
以下是标准代码，不是我写的

#include<stdio.h>
#include<string.h>
#define maxn 1000
#define maxl 100
#define EPS 1e-5

int n = 0;
char sid[maxn][maxl];
int cid[maxn];
char name[maxn][maxl];
int score[maxn][5];
int removed[maxn];

const char* course_name[] = {"Chinese", "Mathematics", "English", "Programming"};

int valid(int k) {
  for(int i = 0; i < k; i++) if(!removed[i]) {
    if(strcmp(sid[i], sid[k]) == 0) return 0;
  }
  return 1;
}

void add() {
  for(;;) {
    printf("Please enter the SID, CID, name and four scores. Enter 0 to finish.\n");
    scanf("%s", sid[n]);
    if(strcmp(sid[n], "0") == 0) break;
    scanf("%d%s%d%d%d%d", &cid[n], name[n], &score[n][0], &score[n][1], &score[n][2], &score[n][3]);
    if(valid(n)) { score[n][4] = score[n][0]+score[n][1]+score[n][2]+score[n][3]; n++; }
    else printf("Duplicated SID.\n");
  }
}

int rank(int k) {
  int r = 0;
  for(int i = 0; i < n; i++)
    if(!removed[i] && score[i][4] > score[k][4]) r++;
  return r+1;
}

void DQ(int isq) {
  char s[maxl];
  for(;;) {
    printf("Please enter SID or name. Enter 0 to finish.\n");
    scanf("%s", s);
    if(strcmp(s, "0") == 0) break;
    int r = 0;
    for(int i = 0; i < n; i++) if(!removed[i]) {
      if(strcmp(sid[i], s) == 0 || strcmp(name[i], s) == 0) {
        if(isq) printf("%d %s %d %s %d %d %d %d %d %.2f\n", rank(i), sid[i], cid[i], name[i], score[i][0], score[i][1], score[i][2], score[i][3], score[i][4], score[i][4]/4.0+EPS);
        else { removed[i] = 1; r++; }
      }
    }
    if(!isq) printf("%d student(s) removed.\n", r);
  }
}

double get_course_stat(int c, int s, int* passed, int* failed) {
  int tot = 0;
  *passed = *failed = 0;
  for(int i = 0; i < n; i++)
    if(!removed[i] && (c == 0 || cid[i] == c)) {
      tot += score[i][s];
      if(score[i][s] >= 60) (*passed)++; else (*failed)++;
    }
  return (double)tot / (double)(*passed + *failed);
}

void get_overall_stat(int c, int* cnt) {
  cnt[0] = cnt[1] = cnt[2] = cnt[3] = cnt[4] = 0;
  for(int i = 0; i < n; i++)
    if(!removed[i] && (c == 0 || cid[i] == c)) {
      int k = 0;
      for(int j = 0; j < 4; j++) if(score[i][j] >= 60) k++;
      cnt[k]++;
    }
}

void stat() {
  int c;
  printf("Please enter class ID, 0 for the whole statistics.\n");
  scanf("%d", &c);
  for(int i = 0; i < 4; i++) {
    int passed, failed;
    double avg = get_course_stat(c, i, &passed, &failed);
    printf("%s\n", course_name[i]);
    printf("Average Score: %.2f\n", avg+EPS);
    printf("Number of passed students: %d\n", passed);
    printf("Number of failed students: %d\n", failed);
    printf("\n");
  }
  int cnt[5];
  get_overall_stat(c, cnt);

  printf("Overall:\n");
  printf("Number of students who passed all subjects: %d\n", cnt[4]);
  printf("Number of students who passed 3 or more subjects: %d\n", cnt[4]+cnt[3]);
  printf("Number of students who passed 2 or more subjects: %d\n", cnt[4]+cnt[3]+cnt[2]);
  printf("Number of students who passed 1 or more subjects: %d\n", cnt[4]+cnt[3]+cnt[2]+cnt[1]);
  printf("Number of students who failed all subjects: %d\n", cnt[0]);
  printf("\n");
}

int main() {
    //freopen("input.txt","r",stdin);
  for(;;) {
    int choice;
    printf("Welcome to Student Performance Management System (SPMS).\n");
    printf("\n");
    printf("1 - Add\n");
    printf("2 - Remove\n");
    printf("3 - Query\n");
    printf("4 - Show ranking\n");
    printf("5 - Show Statistics\n");
    printf("0 - Exit\n");
    printf("\n");

    scanf("%d", &choice);
    if(choice == 0) break;
    if(choice == 1) add();
    if(choice == 2) DQ(0);
    if(choice == 3) DQ(1);
    if(choice == 4) printf("Showing the ranklist hurts students' self-esteem. Don't do that.\n");
    if(choice == 5) stat();
  }
  return 0;
}


以下是我自己写的，操作5借鉴了标准代码
注意操作4，输出一句话，不要直接复制PDF上的文本，有可能单引号会引起编码错误，保险一点的做法是自己手打一遍

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    int flag;
    char sid[11];
    char name[105];
    int cid;
    int score[5];
}NODE;

NODE stud[1005];

int sz=0;
const double EPS=1e-5;
const char coarsename[4][15]={"Chinese", "Mathematics", "English", "Programming"};

void PrintDefault();
void add();
void query();
void dlt();
void showsts();
void getoverall(int op,int sco[]);
int valid(int num);
int Rank(int num);
double getavg(int op,int i,int * pass,int * fail);

int main()
{
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    while (1)
    {
        PrintDefault();
        int op;
        scanf("%d",&op);
        if (op==1) add();
        else if (op==2) dlt();
        else if (op==3) query();
        else if (op==4) puts("Showing the ranklist hurts students' self-esteem. Don't do that.");
        else if (op==5) showsts();
        else break;
    }
}

void PrintDefault()
{
    printf("Welcome to Student Performance Management System (SPMS).\n\n");
    printf("1 - Add\n2 - Remove\n3 - Query\n4 - Show ranking\n5 - Show Statistics\n0 - Exit\n\n");
}

void add()
{
    while (1)
    {
        puts("Please enter the SID, CID, name and four scores. Enter 0 to finish.");
        scanf("%s",stud[sz].sid);
        if (stud[sz].sid[0]=='0' && strlen(stud[sz].sid)==1) break;
        stud[sz].flag=0;
        scanf("%d%s%d%d%d%d",&stud[sz].cid,stud[sz].name,&stud[sz].score[0],&stud[sz].score[1],&stud[sz].score[2],&stud[sz].score[3]);
        if(valid(sz))
        {
            stud[sz].flag=1;
            stud[sz].score[4]=stud[sz].score[0]+stud[sz].score[1]+stud[sz].score[2]+stud[sz].score[3];
            sz++;
        }
        else puts("Duplicated SID.");
    }
}

int valid(int num)
{
    for (int i=0 ; i<sz ; i++) if (stud[i].flag && strcmp(stud[i].sid,stud[num].sid)==0) return 0;
    return 1;
}

void query()
{
    while (1)
    {
        puts("Please enter SID or name. Enter 0 to finish.");
        char s[105];
        scanf("%s",s);
        if (s[0]=='0' && strlen(s)==1) break;
        for (int i=0 ; i<sz ; i++)  if (stud[i].flag && (strcmp(stud[i].sid,s)==0 || strcmp(stud[i].name,s)==0)) printf("%d %s %d %s %d %d %d %d %d %.2f\n",Rank(i),stud[i].sid,stud[i].cid,stud[i].name,stud[i].score[0],stud[i].score[1],stud[i].score[2],stud[i].score[3],stud[i].score[4],stud[i].score[4]/4.0+EPS);
    }
}

int Rank(int num)
{
    int r=1;
    for (int i=0 ; i<sz ; i++) if (stud[i].flag && stud[i].score[4]>stud[num].score[4]) r++;
    return r;
}

void dlt()
{
    while (1)
    {
        puts("Please enter SID or name. Enter 0 to finish.");
        char s[105];
        scanf("%s",s);
        if (s[0]=='0' && strlen(s)==1) break;
        int r=0;
        for (int i=0 ; i<sz ; i++)
            if (stud[i].flag && (strcmp(stud[i].sid,s)==0 || strcmp(stud[i].name,s)==0))
            {
                stud[i].flag=0;
                r++;
            }
        printf("%d student(s) removed.\n",r);
    }
}

void showsts()
{
    puts("Please enter class ID, 0 for the whole statistics.");
    int op;
    scanf("%d",&op);
    for (int i=0 ; i<4 ; i++)
    {
        int pass=0,fail=0;
        puts(coarsename[i]);
        double average=getavg(op,i,&pass,&fail);
        printf("Average Score: %.2f\n",average+EPS);
        printf("Number of passed students: %d\n",pass);
        printf("Number of failed students: %d\n\n",fail);
    }
    int cnt[5]={0};
    getoverall(op,cnt);
    puts("Overall:");
    printf("Number of students who passed all subjects: %d\n",cnt[4]);
    printf("Number of students who passed 3 or more subjects: %d\n",cnt[4]+cnt[3]);
    printf("Number of students who passed 2 or more subjects: %d\n",cnt[4]+cnt[3]+cnt[2]);
    printf("Number of students who passed 1 or more subjects: %d\n",cnt[4]+cnt[3]+cnt[2]+cnt[1]);
    printf("Number of students who failed all subjects: %d\n\n",cnt[0]);
}

double getavg(int op, int i, int* pass, int* fail)
{
    int tot=0;
    for (int t=0 ; t<sz ; t++)
    {
        if (stud[t].flag && (op==0 || op==stud[t].cid))
        {
            tot+=stud[t].score[i];
            if (stud[t].score[i]>=60) (*pass)++;
            else (*fail)++;
        }
    }
    return (double)tot/(*fail+*pass);
}

void getoverall(int op, int sco[])
{
    for (int i=0 ; i<sz ; i++)
    {
        if (stud[i].flag && (stud[i].cid==op || op==0))
        {
            int cn=0;
            for (int j=0 ; j<4 ; j++) if (stud[i].score[j]>=60) cn++;
            sco[cn]++;
        }
    }
}
