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

void Setout(Stack* s)
{
    int i=1;
    while(i<s->top)
    {
        printf("Node %d: %s (degree=%d)\n", i, s->g[i].tar, s->g[i].degree);
        int j=0;
        while (j<s->g[i].degree)
        {
            printf("  -> %s\n", s->g[s->g[i].dep[j]].tar);
            j++;
        }
        i++;
    }
    
}
/*void Setout(Graph g[100],int i)
{
    printf("Node %d: %s (degree=%d)\n", i, g[i].tar, g[i].degree);
        int j=0;
        while (j<g[i].degree)
        {
            printf("  -> %s\n", g[g[i].dep[j]].tar);
            j++;
        }
    
}*/
void DFS(Stack* s,Graph g[100],int i)
{
    if(g[i].flag==1)
    return;
    g[i].flag=1;
    int j;
    for(j=0;g[i].dep[j]!=0;j++)
    {
        DFS(s,g,g[i].dep[j]);
    }
    s->g[s->top]=g[i];
    s->top++; 
    return;
}
void Three_1_2(Rule r[100],Graph g[100])
{
    int i;
    Stack* s;
    s=(Stack*)malloc(sizeof(Stack));
    s->top=0;
    struct stat st;
    for(i=0;r[i].t[0]!='\0';i++)
    {
        strcpy(g[i+1].tar,r[i].t);
    }
    for(i=0;r[i].t[0]!='\0';i++)
    {
		 g[i+1].degree = 0; 
        for(int j=0;r[i].d[j][0]!='\0';j++)
        {
            for(int k=0;r[k].t[0]!='\0';k++)
            {
                if(strcmp(r[k].t,r[i].d[j])==0)
                {
					g[i+1].dep[g[i+1].degree] = k+1;  // 使用 degree 作为索引
                    g[i+1].degree++;;
                    break;
                }
            }
            g[i+1].degree=j+1;
        }
    }//给依赖定位
    i=1;
    while(g[i].tar[0]!='\0')
    {
        if(g[i].flag==1)
        {
            i++;
            continue;
        }
        DFS(s,g,i);
		i++;
    }
    //for(i=1;g[i].tar[0]!='\0';i++)
    //{
        Setout(s);
    //}
}
int main()
{
	Rule r[100];
	Graph *g;
	g=(Graph*)malloc(100*sizeof(Graph));
	strcpy(r[0].t, "app");
    strcpy(r[0].d[0], "dep1");
    strcpy(r[0].d[1], "dep2");
    strcpy(r[3].t, "dep1");
    strcpy(r[2].t, "dep2");
    strcpy(r[1].t, "dep3");
    strcpy(r[1].d[0], "dep5");
    strcpy(r[2].d[0], "dep3");
    strcpy(r[2].d[1], "dep4");
    strcpy(r[4].t, "dep5");
    strcpy(r[5].t, "dep4");
	Three_1_2(r,g);
	return 0;}
