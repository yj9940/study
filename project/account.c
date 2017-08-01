#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include"support.h"
#include"menu.h"
#include"func.h"
#include"account.h"


//管理员登录系统
void login_admin_account()
{
	
	char admin_name[20]={"yj"};
	char admin_passwd[20]={"123"};

	char lgname[20]={"\0"};
//	char lgpasswd[20]={"\0"};
	char *lgpasswd;

	int lg_i=0,j=0;
	while(lg_i!=3)
{
	printf("****请输入管理员账号:");
	my_gets(lgname);
//	printf("****请输入管理员密码:");
//	my_gets(lgpasswd);
	lgpasswd=getpass("****请输入管理员密码:");

	if(strcmp(lgname,admin_name)!=0||strcmp(lgpasswd,admin_passwd)!=0)
	{
		printf("****登录失败，请重新登录\n");
		printf("****按下回车键继续\n");
		while(getchar()!='\n');
		lg_i++;
		continue;
	}
	break;
}
	if(lg_i==3)
	{
		for(j=0;j<10;j++)
		{
			sleep(1);
			printf("\33[1A还剩%ds,冷静一下\33[K\n",10-j);
		}
		printf("****怕是个假管理员，回家种田吧****\n");
		while(getchar()!='\n');
		return;
	}


	int cho4=-1,flag_r=1;
	while(flag_r)
	{	
		teacher_t *head=t_readfile();
		teacher_t *l;
		l=head;

		while(head->next!=NULL)
		{
			if(head->next->t_data.t_flag==1)
			{
			printf("工号为%d的教师想要辞职，是否同意捏?\n1-->同意\n2-->拒绝\n",head->next->t_data.id);
			scanf("%d",&cho4);
			while(getchar()!='\n');
			
			switch(cho4)
			{
				case 1:
					head->next->t_data.t_flag=0;
					head->next->t_data.last_flag=1;
					break;
				case 2:
					head->next->t_data.t_flag=0;
					break;
				default:
					printf("*重新输入哦*\n");
					break;
			}
			}
		head=head->next;
		}
	writefile_teacher(l);
	if(head->next==NULL)
	{
		flag_r=0;	
	}
	}
	//之前判断是否有人辞职 是否同意

	printf("\n");
while(1){

	system("clear");
	admin_menu();
	
	printf("\33[31m");

	printf("****输入选择:");
	char cho='0';
	scanf("%c",&cho);
	while(getchar()!='\n');

	
	switch(cho)
	{
		case '1':
			add_teacher_info();
			break;
		case '2':
			update_teacher_info();
			break;
		case '3':
			show_teacher();
			break;
		case '4':
			del_teacher_info();
			break;
		case '5':
			printf("**注销成功，按回车键继续**\n");
			while(getchar()!='\n');
			return;
		default:
			printf("**输入有误,请重新输入**\n");
			break;
	}
	printf("*******按回车键继续*******\n");
	while(getchar()!='\n');
}

}

//教师登录系统
void login_teacher_account()
{

	//验证教师账号密码
	int t_id=-1,flag=0;
	char *lgpasswd;

//	teacher_t *head=t_readfile();
	teacher_t *l_t=t_readfile();
	teacher_t *head=l_t;

	if(head->next==NULL)
	{
		printf("******教师信息为空******\n");
		return;
	}

	int lg_i=0,j=0;
	while(lg_i!=3)
	{
		head=l_t;
		flag=0;
		printf("***请输入账号:");
		scanf("%d",&t_id);
		while(getchar()!='\n');
//		printf("***请输入密码:");
//		my_gets(lgpasswd);
		lgpasswd=getpass("***请输入密码:");

		while(head->next!=NULL)
		{
			if(head->next->t_data.id==t_id)
			{
				flag=1;
				break;
			}
			head=head->next;
		}
	
		if(flag==0)
		{
			printf("*账号密码错误*\n");
			lg_i++;
			continue;
		}

		if(strcmp(head->next->t_data.passwd,lgpasswd)!=0)
		{
		printf("*账号密码错误哦\n");
		lg_i++;
		continue;
		}
		break;
	}
	if(lg_i==3)
	{
		for(j=0;j<10;j++)
		{
			sleep(1);
			printf("\33[1A还剩%ds,冷静一下\33[K\n",10-j);
		}
		printf("**怕是假老师,回家种田吧**\n");
		while(getchar()!='\n');
		return;
	}


//验证班主任还是任课教师
	int choi=-1,ch2=-1;
	char t_rank[10]={"main"};

	if(strcmp(head->next->t_data.rank,t_rank)==0)
	{
		printf("**欢迎您，班主任**\n");
		
		if(head->next->t_data.last_flag==1)
		{
			printf("*****您的辞职申请已被同意，按回车键进行账户封号*****\n");
			while(getchar()!='\n');
			//删除本账号
			del_teacher_resign(t_id);
			return ;
		}
		else if(head->next->t_data.t_flag==1)
		{
			printf("***您的辞职正在等待审核,按回车键继续***\n");
			while(getchar()!='\n');
			return ;
		}

	

while(1)
{
		system("clear");

		main_teacher_menu();

		printf("\33[35m");
		printf("\n******请输入您的选择******\n");
		scanf("%d",&choi);
		while(getchar()!='\n');

		switch(choi)
		{
		case 1:
			add_student_info();
			break;
		case 2:
			show_student();
			break;
		case 3:
			update_student_info();
			break;
		case 4:
			del_student_info();
			break;
		case 5:		
			printf("***1->按总分排名\n***2->按学号排名\n***请选择:");
			scanf("%d",&ch2);
			while(getchar()!='\n');
			if(ch2==1)
			{
				student_score_sort();	
				break;
			}
			else if(ch2==2)
			{
				student_id_sort();
				break;
			}
			else
			{
				printf("**输入错误**\n");
				return;
			}

		case 6:
			update_teacher_passwd(t_id);
			break;
		case 7:
			show_leave_word(t_id);
			break;
		case 8:
			resign_work(t_id);
			break;
		case 9:
			printf("**您选择了注销**\n");
			return;
			break;
		dafault:
			printf("怕是按错了\n");
			break;
		}

	printf("*******按回车键继续哦*******\n");
	while(getchar()!='\n');
}
	}
	else
	{
		printf("**欢迎您，任课老师**\n");
		
		if(head->next->t_data.last_flag==1)
		{
			printf("*****您的辞职申请已被同意，按回车键进行账户封号*****\n");
			while(getchar()!='\n');
			//删除本账号
			del_teacher_resign(t_id);
			return ;
		}
		else if(head->next->t_data.t_flag==1)
		{
			printf("***您的辞职正在等待审核,按回车键继续***\n");
			while(getchar()!='\n');
			return ;
		}
while(1)
{
		system("clear");

		subject_teacher_menu();
		
		printf("\33[37m");
		int cho=-1;
		printf("***输入您的选择哟***\n");
		scanf("%d",&cho);
		while(getchar()!='\n');


		char subject1[15]={"math"};
		char subject2[15]={"chinese"};
		switch(cho)
		{
		case 1:
			if(strcmp(head->next->t_data.subject,subject1)==0)
			{
				show_student_math();	
				break;
			}
			else if(strcmp(head->next->t_data.subject,subject2)==0)
			{
				show_student_chinese();
				break;
			}
			else
			{
				printf("怕是个假老师哦\n");
				break;
			
			}
		case 2:
			if(strcmp(head->next->t_data.subject,subject1)==0)
			{
				update_student_math();	
				break;
			}
			else if(strcmp(head->next->t_data.subject,subject2)==0)
			{
				update_student_chinese();
				break;
			}
			else
			{
				printf("怕是个假老师哦\n");
				break;
			
			}
			

		case 3:
			if(strcmp(head->next->t_data.subject,subject1)==0)
			{
				student_math_sort();	
				break;
			}
			else if(strcmp(head->next->t_data.subject,subject2)==0)
			{
				student_chinese_sort();
				break;
			}
			else
			{
				printf("***怕是个假老师哦\n");
				break;
			
			}
			break;
		case 4:
			update_teacher_passwd(t_id);
			break;

		case 5:
			show_leave_word(t_id);
			break;
		case 6:
			printf("**您确定要辞职??\n");
			resign_work(t_id);
			break;
		case 7:
			printf("**您选择注销,按回车键继续**\n");
			while(getchar()!='\n');
			return;
			break;
		default:
			printf("**输入有误，请重新输入**\n");
			break;
		}
	printf("*******按回车键继续*******\n");
	while(getchar()!='\n');
}
	}

	return;
}



//学生登录系统
void login_student_account()
{
	printf("\33[32m");
	//验证学生账号密码
	int s_id=-1,flag=0;
	char *lgpasswd;

	student_t *l_s=s_readfile();
	student_t *head=l_s;

	if(head->next==NULL)
	{
		printf("******学生信息为空******\n");
		return;
	}

	int lg_i=0,j=0;;
	while(lg_i!=3)
	{
		flag=0;
		head=l_s;

		printf("***请输入账号:");
		scanf("%d",&s_id);
		while(getchar()!='\n');
//		printf("***请输入密码:");
//		my_gets(lgpasswd);
		lgpasswd=getpass("***请输入密码***");

		while(head->next!=NULL)
		{
			if(head->next->s_data.id==s_id)
			{
				flag=1;
				break;
			}
			head=head->next;
		}
	
		if(flag==0)
		{
			printf("*账号密码错误亲1*\n");
			lg_i++;
			continue;
		}

		if(strcmp(head->next->s_data.passwd,lgpasswd)!=0)
		{
		printf("*账号密码错误哦2\n");
		lg_i++;
		continue;
		}
		break;
	}
	if(lg_i==3)
	{
		for(j=0;j<10;j++)
		{
			sleep(1);
			printf("\33[1A还剩%ds,冷静一下\33[K\n",10-j);
		}
		printf("**怕是个假学生,回家种田吧**\n");
		while(getchar()!='\n');
	}


	while(1)
	{
		system("clear");
	
		student_menu();
		int cho=-1;
		printf("\33[32m请输入您的选择哇:");
		scanf("%d",&cho);
		while(getchar()!='\n');
	
		switch(cho)
		{
		case 1:
			show_my_info(s_id);
			break;
		case 2:
			update_student_passwd(s_id);
			break;
		case 3:
			leave_word();	
			break;
		case 4:
			printf("**您选择注销,按回车键继续**\n");
			while(getchar()!='\n');
			return;
			break;
		default:
			printf("**输入有误，重新输入哦\n");
			break;	
		}
		printf("*******按回车键继续*******\n");
		while(getchar()!='\n');
	}	

	}






