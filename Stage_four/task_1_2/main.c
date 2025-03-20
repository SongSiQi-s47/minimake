#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<sys/stat.h>
#include<time.h>
#include<unistd.h>
#include<sys/wait.h>

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

void Four1_2(Rule r[100])
{
    int i,j;
    char* com[100];
    if(r==NULL)
    {
        fprintf(stderr,"错误,规则为空");
        return;
    }
    for(i=0;r[i].c[0]!='\0';i++)
    {
        j=0;
        com[0]=strtok(strdup(r[i].c)," ");
        if(com[0]==NULL)
        {
            fprintf(stderr,"错误,命令为空");
            return;
        }
        while(j<99&&com[j]!=NULL)
        {
            com[j]=strtok(NULL," ");
            j++;
        }
        com[j]=NULL;
        pid_t pid=fork();//windows系统没有fork函数
        if (pid==-1)
        {
            perror("fork");
            exit(EXIT_FAILURE);/* code */
        }
        else if(pid==0)//子进程
        {
            execvp(com[0],com);
            perror("execvp");
            _exit(EXIT_FAILURE);
        }
        else//父进程
        {
            int status;
            if(waitpid(pid,&status,0)==-1)
            {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }
            if(WIFEXITED(status))//子进程正常退出
            {
                if(WEXITSTATUS(status)!=0)
                {
                    fprintf(stderr,"%s命令失败,停止构建",r[i].c);
                    exit(EXIT_FAILURE);
                }
                
            }
            else if(WIFSIGNALED(status))//子进程未正常退出
            {
                fprintf(stderr,"%s信号错误,任务终止",r[i].c);
                exit(EXIT_FAILURE);
            }
        }
    }
}
