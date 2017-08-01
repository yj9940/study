#include<stdio.h>
#include<stdlib.h>
#include"menu.h"
#include"account.h"
#include"func.h"

int main()
{
	char ch='0';
	while(1)
	{	
		system("clear");

		main_menu();
		printf("******input your choice:");
		scanf("%c",&ch);
		while(getchar()!='\n');
		switch(ch)
		{
			case '1':
				login_admin_account();
				break;
			case '2':
				login_teacher_account();
				break;	
			case '3':
				login_student_account();
				break;
			case '4':
				printf("退出成功，按回车键继续\n");
				while(getchar()!='\n');
				return 0;
			default:
				printf("输入有误，按回车键返回\n");
				while(getchar()!='\n');
				break;
		}
	printf("*******按回车键继续*******\n");
	while(getchar()!='\n');

	}
	
}
