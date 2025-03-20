#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<sys/stat.h>
#include<time.h>

typedef struct{
    char t[32];
    char d[10][32];
    char c[256];
}Rule;

typedef struct
{
    char tar[32];
    int dep[10];//依赖的目标的位置
    int degree;
    int flag;/* data */
}Graph; 
typedef struct
{
    Graph g[100];
    int top;/* data */
}Stack;

time_t Gettime(char* tar)
{
    struct stat file_stat;
    if(tar[0]=='\0'||tar==NULL)
    {
        return -1;//文件不存在
    }
    if(stat(tar,&file_stat)==-1)
    {
        return -1;//文件不存在
    }
    return file_stat.st_mtime;
}
/*int Judgetime(char* tar,char** dep)
{
    
    td=Gettime(g[i].dep[])
}*/
int Three_3(Graph g[100],char* tar)
{
    int i,j;
    time_t tt,td;
    if(g==NULL)
    {
        fprintf(stderr,"错误,图结构为空");
        return -1;
    }
    for(i=1;g[i].tar[0]!='\0'&&i<100;i++)
    {
        if(strcmp(g[i].tar,tar)==0)
        {
            break;
        }
    }
        tt=Gettime(g[i].tar);
        if(tt==-1)
        {
            for(j=1;j<=g[i].degree;j++)
            {
            td=Gettime(g[g[i].dep[j]].tar);
            if(td==-1)
            {
                printf("错误，依赖不存在");
                return -1;
            }
            }
            return 1;
        }//目标不存在
        for(j=0;j<g[i].degree;j++)
        {
            td=Gettime(g[g[i].dep[j]].tar);
            if(td>tt)
            {
                return 1;
            }//依赖比目标新，重建
        }
    return 0;
}
