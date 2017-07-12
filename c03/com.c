#include <stdio.h>
int main()
{
	float num1,num2;
	char ch;
	printf("请输入一个算数式");
	scanf("%f%c%f",&num1,&ch,&num2);
	if('+' == ch)
	{
		printf("结果是:%f\n",num1+num2);
	}else if('-' == ch)
	{	
		printf("结果是:%f\n",num1-num2);
	}else if('*' == ch)
	{
		printf("结果是:%f\n",num1*num2);
	}else if('/' == ch)
	{
		printf("结果是:%f\n",num1/num2);
	}else {printf("没有结果\n");}

		return 0;
}
