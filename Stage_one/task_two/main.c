#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<sys/stat.h>
#include<time.h>


void main(int argc,char* argv[])
{
	int i,flag=0,flag1=0;//flag1用于检测语法
	for(i=1;i<argc;i++)
	{
		if(strcmp(argv[i],"-v")||strcmp(argv[i],"--verbose"))
		{
			flag=1;
		//	printf("读取参数，检测是否有-v或者--verbos\n");
			break;
		}
	}
	FILE *fp=fopen("Makefile","r");
	if(!fp)
	{
		perror("Makefile文件不存在");
		exit(1);
	}
//	else{
	//	printf("文件打开了\n");
//	}
	char str[256];
	FILE *fp1=fopen("Makefile_claered","w+");

	int len;

	char* s;
	i=0;
    int flag_blank;
	while(fgets(str,sizeof(str),fp))
	{ 
	
        i=0;
		len=strlen(str);
	/*	while(i<len){
		
            printf("%d ",str[i++]);

		}
		printf("\n");
*/
		if((strlen(str)==0)||strlen(str)==1)
			continue;
		s=strchr(str,'#');
		if(s!=NULL){
			*s='\n';  
			*(s+1)='\0';
		}
		len=strlen(str);
		flag_blank=0;
	    while(len>1 && isspace(str[len-2]))
		{
			len--;
			flag_blank=1;
		}

		if(len==0||len==1)
			continue;
         if(flag_blank){
		str[len++]='\n';
		str[len]='\0';}
		//  printf("%s\n",str);
//		printf("写了%d次\n",i++);
//		printf("%s",str);
		fputs(str, fp1); 

	}

	fclose(fp);
  //  if(flag==1) 	fclose(fp1);
    	fclose(fp1);





}


