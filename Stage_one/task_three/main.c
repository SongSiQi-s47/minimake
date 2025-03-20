#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<sys/stat.h>
#include<time.h>


void main(int argc,char* argv[])
{
	int i;
	FILE *fp=fopen("Makefile","r");
	if(!fp)
	{
		perror("Makefile文件不存在");
		exit(1);
	}
	char str[256];

	int len;

	char* s;
	i=0;
	int flag_target=0;
	while(fgets(str,sizeof(str),fp))
	{ 
        i++;
		len=strlen(str);

		if((len==0)||len==1)
			continue;
		if(strchr(str,':')!=NULL){
			flag_target=1;
		}
		else
		{
			if(str[0]!='\t'){
				printf("line%d: Missing colon in target definition\n",i);
			    break;
			}
			else{

                   if(flag_target==0){
					   printf("line%d: Command found before rule\n",i);
				       break;
				   }        			
			}
             
		}
	}

	fclose(fp);
}

