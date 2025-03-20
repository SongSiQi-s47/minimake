#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<sys/stat.h>
#include<time.h>


int main(int argc,char* argv[])
{
    int i;
	for(i=1;i<argc;i++)
	{
		if(strcmp(argv[i],"--help")==0)
		{
			printf("%s   ",argv[i]);
			printf("《这是帮助》\n");
			break;     
		}
		if(strncmp(argv[i],"--",2)==0)
		{
			printf("%s   ",argv[i]);
			printf("格式错误\n");
			return 0;
		} 
	}
    return 1;
}

