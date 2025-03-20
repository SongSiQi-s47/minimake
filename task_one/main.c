#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
    char t[32];//target
    char d[10][32];   //dependency
    char c[256];      

}Rule;

int  main(){

	int ti=-1,ci=0;
	char* s;
	char str[256];
	int i,j,m,n;

	FILE *fp;	
	
        int flag=1; //测试过程似乎没有输入-v过程。
	if(flag==1){
		fp=fopen("Makefile_claered","r");
	}
	else{
		fp=fopen("Makefile","r");
	}
	if(!fp)
	{
		perror("Makefile文件不存在");
		exit(1);
	}
	while(fgets(str,sizeof(str),fp))
	{
		s=strchr(str,':');
		if(s!=NULL){ //如果有冒号，则ti++
			ti++;			
		}
		else{
			continue;
		}
		for(i=0;(str+i)!=s;i++)
		{
			r[ti].t[i]=str[i];
		}
		r[ti].t[i]='\0';
		for(j=0;j<ti;j++)
		{
			if(strcmp(r[j].t,r[ti].t)==0)
				printf("Duplicate target definition '%s'\n",r[ti].t);
		}
		//下面处理依赖
		if(*(s+1)==' ') s=s+2;  //第一个依赖前面可能有个空格
		else s=s+1;
		i=0;m=0;n=0;
		while(*(s+i)!='\0')
		{		
			if(*(s+i)==' '|| ( *(s+i)=='\n'&& *(s+i-1)!=' '))
			{
				r[ti].d[m][n]='\0';//依赖的起始位置
                            if(access(r[ti].d[m],F_OK)==-1){
                                            printf("Invalid dependency '%s'\n",r[ti].d[m]);}
				n=0;
				i++;
				m++;
				continue;
			}
			else {r[ti].d[m][n++]=*(s+i);i++;}
		}//把依赖分成各个目标和文件            
	        count[ti]=m;  //记录每行有多少个依赖
		for(j=0;j<m;j++){
			printf("%s  ",r[ti].d[j]);
			if(strchr(r[ti].d[j],'.')==NULL)
			{
				printf("Invalid dependency '%s'\n",r[ti].d[j]);
			    break;
			}
		}
	}
	fclose(fp);


return 0;



}
