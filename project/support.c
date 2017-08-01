#include "support.h"
void my_gets(char *str)
{
	int i=0;
	for(i=0;i<19;i++)
	{
		str[i]=getchar();
		if(str[i]=='\n')
		{
			break;
		}
	}
	str[i]='\0';
	if(i==19)
	{
		while(getchar()!='\n');
	}

}
