#include <stdio.h>
int main()
{
	int num1,num2,rs;
	char ch;
	printf("请输入一个算数式");
	scanf("%d%c%d",&num1,&ch,&num2);
	if('+' == ch)
	{
		printf("结果是:%d\n",num1+num2);
	}else if('-' == ch)
	{	
		printf("结果是:%d\n",num1-num2);
	}else if('*' == ch)
	{
		printf("结果是:%d\n",num1*num2);
	}else if('/' == ch)
	{
		printf("结果是:%d\n",num1/num2);
	}else {printf("没有结果\n");}

		return 0;
}
