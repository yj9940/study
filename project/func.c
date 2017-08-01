#include<stdio.h>
#include"func.h"
#include<stdlib.h>
#include<string.h>
#include"support.h"

//教师信息的录入
void add_teacher_info()
{
	teacher_t *head=t_readfile();
	teacher_t *temp=(teacher_t *)malloc(sizeof(teacher_t));
	teacher_t *l=head;

	if(temp==NULL)
	{
		printf("******录入失败******");
		return;
	}

	temp->next=NULL;
	printf("***输入教师id:");
	scanf("%d",&temp->t_data.id);
	while(getchar()!='\n');

	//判断id是否重复
	while(l->next!=NULL)
	{
		if(l->next->t_data.id==temp->t_data.id)
		{
			printf("id已经重复,按回车键退出\n");
			while(getchar()!='\n');
			return;
		}
		l=l->next;
	}

	printf("***输入教师姓名:");
	scanf("%s",temp->t_data.name);
	while(getchar()!='\n');
	
	printf("***输入教师密码:");
	scanf("%s",temp->t_data.passwd);
	while(getchar()!='\n');

	printf("***请输入教师职位:");
	scanf("%s",temp->t_data.rank);
	while(getchar()!='\n');

	printf("***请输入教师科目:");
	scanf("%s",temp->t_data.subject);
	while(getchar()!='\n');

	temp->t_data.t_flag=0;
	temp->t_data.last_flag=0;

	if(head->next!=NULL)
	{
		temp->next=head->next;
		head->next=temp;
	}
	else{
		head->next=temp;
	}
	
	save_teacher(head);

	free(temp),temp=NULL;
}

//修改教师信息
void update_teacher_info()
{
	teacher_t *head=t_readfile();
	teacher_t *l;
	teacher_t *temp=(teacher_t *)malloc(sizeof(teacher_t));
	l=head;

	if(head->next==NULL)
	{
		printf("***教师信息为空\n");
		return;
	}

	printf("****输入您要修改的教师id:");
	int t_id=0,flag=0;
	scanf("%d",&t_id);
	while(getchar()!='\n');


	while(head->next!=NULL)
	{
		
		if(head->next->t_data.id == t_id)
		{
			flag=1;
			break;
		}
		head=head->next;
	}

	if(flag)
	{
		printf("**请输入新的新名字:");
		my_gets(temp->t_data.name);

		printf("**请输入新的密码:");
		my_gets(temp->t_data.passwd);

		printf("**请输入新的职阶:");
		my_gets(temp->t_data.rank);

		printf("**请输入新的任课科目:");
		my_gets(temp->t_data.subject);
	

	}else
	{
		printf("***没有找的匹配的id!***\n");
		return;
	}
	
	strcpy(head->next->t_data.name,temp->t_data.name);
	strcpy(head->next->t_data.passwd,temp->t_data.passwd);
	strcpy(head->next->t_data.rank,temp->t_data.rank);
	strcpy(head->next->t_data.subject,temp->t_data.subject);

	save_teacher(l);

	free(temp),temp=NULL;
	return;
}

//删除教师信息
void del_teacher_info()
{
	teacher_t *head=t_readfile();
	teacher_t *l;
	teacher_t *temp=(teacher_t *)malloc(sizeof(teacher_t));
	l=head;
	teacher_t *l2;
	l2=head;

	int t_id=-1,flag=0;
	printf("***请输入您想删除的教师id:");
	scanf("%d",&t_id);
	while(getchar()!='\n');

	if(head->next==NULL)
	{
		printf("******不存在教师信息******\n");
		printf("**按回车键返回**\n");
		while(getchar()!='\n');
		return;
	}

	while(l2->next!=NULL)
	{
		if(l2->next->t_data.id==t_id)
		{
			flag=1;
		}
		l2=l2->next;
	}
	if(flag==0)
	{
		printf("**没有这样的教师,按回车键返回**\n");
		while(getchar()!='\n');
		return;
	}


	while(head->next->t_data.id!=t_id)
	{
		head=head->next;
	}
		temp=head->next;
		head->next=head->next->next;

	save_teacher(l);

	free(temp),temp=NULL;
	
	return;
}




//将教师结构体链表写进教师文件
void writefile_teacher(teacher_t *head)
{
	if(NULL==head)
	{
		printf("******没有信息需要保存******\n");
		return;
	}
	FILE *fp;
	fp=fopen("teacher.txt","w");
	while(head->next!=NULL)
	{
		fwrite(head->next,sizeof(teacher_t),1,fp);
		head=head->next;
	}
	fclose(fp);
	return;
}


//从文件将教师信息读到内存，即链表
teacher_t *t_readfile()
{
	FILE *fp=fopen("teacher.txt","r");
	teacher_t *temp=(teacher_t *)malloc(sizeof(teacher_t));
	teacher_t *head=(teacher_t *)malloc(sizeof(teacher_t));

	head->next=NULL;

	while(fread(temp,sizeof(teacher_t),1,fp))
	{
		temp->next = head->next;
		head->next = temp;

		temp=NULL;
		temp=(teacher_t *)malloc(sizeof(teacher_t));
	}
	free(temp);
	temp=NULL;
	fclose(fp);
	return head;
}

//查看并打印教师信息
void show_teacher()
{
	teacher_t *head=t_readfile();
	
	if(head==NULL)
	{
		printf("***没有信息\n");
		return ;
	}

	while(head->next!=NULL)
	{
		printf("id:%d\tname:%s\tpasswd:%s\trank:%s\tsubject:%s\n",
				head->next->t_data.id,
				head->next->t_data.name,
				head->next->t_data.passwd,
				head->next->t_data.rank,
				head->next->t_data.subject);
		head=head->next;
	}
	printf("\n");
	return ;
}


//教师对学生可以进行的操作

//教师的密码修改
void update_teacher_passwd(int id)
{
	teacher_t *head=t_readfile();
	teacher_t *l;
	l=head;

	char newpasswd[20],newpasswd2[20];
	while(head->next->t_data.id!=id)
	{
		head=head->next;
	}

	while(1)
	{
		printf("**请输入您的新密码:\n");
		my_gets(newpasswd);

		printf("**请确认您的新密码:\n");
		my_gets(newpasswd2);

		if(strcmp(newpasswd,newpasswd2)!=0)
		{
			printf("****两次密码不一致，请重新输入****\n");
		}
		else
		{
			break;
		}
	}
	strcpy(head->next->t_data.passwd,newpasswd);
	
	printf("**修改完成\n");

	save_teacher(l);

	return;
}


//学生信息的录入
void add_student_info()
{
	student_t *head=s_readfile();
	student_t *temp=(student_t *)malloc(sizeof(student_t));
	student_t *l=head;

	if(temp==NULL)
	{
		printf("******录入失败******");
		return;
	}

	temp->next=NULL;
	printf("***输入学生id:");
	scanf("%d",&temp->s_data.id);
	while(getchar()!='\n');

	//判断id是否重复
	while(l->next!=NULL)
	{
		if(l->next->s_data.id==temp->s_data.id)
		{
			printf("id已经重复,按回车键退出\n");
			while(getchar()!='\n');
			return;
		}
		l=l->next;
	}


	printf("***输入学生密码:");
	scanf("%s",temp->s_data.passwd);
	while(getchar()!='\n');

	printf("***输入学生姓名:");
	scanf("%s",temp->s_data.name);
	while(getchar()!='\n');

	printf("***请输入数学成绩:");
	scanf("%f",&temp->s_data.math);
	while(getchar()!='\n');

	printf("***请输入语文成绩:");
	scanf("%f",&temp->s_data.chinese);
	while(getchar()!='\n');

	temp->s_data.sum=temp->s_data.math+temp->s_data.chinese;

	if(head->next!=NULL)
	{
		temp->next=head->next;
		head->next=temp;
	}
	else{
		head->next=temp;
	}

	save_student(head);
	return;
}


//将学生结构体链表写进学生文件
void writefile_student(student_t *head)
{
	if(NULL==head)
	{
		printf("******没有信息需要保存******\n");
		return;
	}
	FILE *fp;
	fp=fopen("student.txt","w");
	while(head->next!=NULL)
	{
		fwrite(head->next,sizeof(student_t),1,fp);
		head=head->next;
	}
	fclose(fp);
	return;
}

//从文件将学生信息读到内存，即链表
student_t *s_readfile()
{
	FILE *fp=fopen("student.txt","r");
	student_t *temp=(student_t *)malloc(sizeof(student_t));
	student_t *head=(student_t *)malloc(sizeof(student_t));

	head->next=NULL;

	while(fread(temp,sizeof(student_t),1,fp))
	{
		temp->next = head->next;
		head->next = temp;

		temp=NULL;
		temp=(student_t *)malloc(sizeof(student_t));
	}
	free(temp);
	temp=NULL;
	fclose(fp);
	return head;
}

//查看并打印学生信息
void show_student()
{
	student_t *head=s_readfile();
	
	if(head==NULL)
	{
		printf("***没有信息\n");
		return ;
	}

	while(head->next!=NULL)
	{
		printf("id:%d\tname:%s\tpwd:%s\tmath:%.2f\tchinese:%.2f\tsum:%.2f\n",
				head->next->s_data.id,
				head->next->s_data.name,
				head->next->s_data.passwd,
				head->next->s_data.math,
				head->next->s_data.chinese,
				head->next->s_data.sum);
		head=head->next;
	}
	printf("\n");
	return ;
}

//查看学生数学信息
//查看并打印学生数学信息
void show_student_math()
{
	student_t *head=s_readfile();
	
	if(head==NULL)
	{
		printf("***没有信息\n");
		return ;
	}

	while(head->next!=NULL)
	{
		printf("id:%d\tname:%s\tmath score:%.2f\n",
				head->next->s_data.id,
				head->next->s_data.name,
				head->next->s_data.math);
		head=head->next;
	}
	return ;
}


//查看并打印学生语文信息
void show_student_chinese()
{
	student_t *head=s_readfile();
	
	if(head==NULL)
	{
		printf("***没有信息\n");
		return ;
	}

	while(head->next!=NULL)
	{
		printf("id:%d\tname:%s\tchinese score:%.2f\n",
				head->next->s_data.id,
				head->next->s_data.name,
				head->next->s_data.chinese);
		head=head->next;
	}
	return ;
}



//修改学生信息
void update_student_info()
{
	student_t *head=s_readfile();
	student_t *l;
	student_t *temp=(student_t *)malloc(sizeof(student_t));
	l=head;

	if(head->next==NULL)
	{
		printf("***学生信息为空\n");
		return;
	}

	printf("****输入您要修改的学生id:");
	int s_id=0,flag=0;
	scanf("%d",&s_id);
	while(getchar()!='\n');


	while(head->next!=NULL)
	{
		
		if(head->next->s_data.id == s_id)
		{
			flag=1;
			break;
		}
		head=head->next;
	}

	if(flag)
	{
		printf("**请输入新的新名字:");
		my_gets(temp->s_data.name);

		printf("**请输入新的密码:");
		my_gets(temp->s_data.passwd);

		printf("**请输入新的数学成绩:");
		scanf("%f",&temp->s_data.math);
		while(getchar()!='\n');

		printf("**请输入新的语文成绩:");
		scanf("%f",&temp->s_data.chinese);
		while(getchar()!='\n');
	
		temp->s_data.sum=temp->s_data.math+temp->s_data.chinese;

	}else
	{
		printf("***没有找的匹配的id!***\n");
		return;
	}
	
	strcpy(head->next->s_data.name,temp->s_data.name);
	strcpy(head->next->s_data.passwd,temp->s_data.passwd);
	head->next->s_data.math=temp->s_data.math;
	head->next->s_data.chinese=temp->s_data.chinese;
	head->next->s_data.sum=temp->s_data.sum;

	save_student(l);
	
	free(temp),temp=NULL;
	return;
}


//修改学生信息__数学
void update_student_math()
{
	student_t *head=s_readfile();
	student_t *l;
	student_t *temp=(student_t *)malloc(sizeof(student_t));
	l=head;

	if(head->next==NULL)
	{
		printf("***学生信息为空\n");
		return;
	}

	printf("****输入您要修改的学生id:");
	int s_id=0,flag=0;
	scanf("%d",&s_id);
	while(getchar()!='\n');


	while(head->next!=NULL)
	{
		
		if(head->next->s_data.id == s_id)
		{
			flag=1;
			break;
		}
		head=head->next;
	}

	if(flag)
	{

		printf("**请输入新的数学成绩:");
		scanf("%f",&temp->s_data.math);
		while(getchar()!='\n');

		temp->s_data.sum=temp->s_data.math+temp->s_data.chinese;

	}else
	{
		printf("***没有找的匹配的id!***\n");
		return;
	}
	
	head->next->s_data.math=temp->s_data.math;
	head->next->s_data.sum=temp->s_data.sum;

	save_student(l);
	
	free(temp),temp=NULL;
	return;
}

//修改学生信息__语文
void update_student_chinese()
{
	student_t *head=s_readfile();
	student_t *l;
	student_t *temp=(student_t *)malloc(sizeof(student_t));
	l=head;

	if(head->next==NULL)
	{
		printf("***学生信息为空\n");
		return;
	}

	printf("****输入您要修改的学生id:");
	int s_id=0,flag=0;
	scanf("%d",&s_id);
	while(getchar()!='\n');


	while(head->next!=NULL)
	{
		
		if(head->next->s_data.id == s_id)
		{
			flag=1;
			break;
		}
		head=head->next;
	}

	if(flag)
	{

		printf("**请输入新的语文成绩:");
		scanf("%f",&temp->s_data.chinese);
		while(getchar()!='\n');

		temp->s_data.sum=temp->s_data.math+temp->s_data.chinese;
	
	}else
	{
		printf("***没有找的匹配的id!***\n");
		return;
	}
	
	head->next->s_data.math=temp->s_data.chinese;
	head->next->s_data.sum=temp->s_data.math+temp->s_data.chinese;

	save_student(l);
	
	free(temp),temp=NULL;
	return;
}


//删除学生信息
void del_student_info()
{
	student_t *head=s_readfile();
	student_t *l;
	student_t *temp=(student_t *)malloc(sizeof(student_t));
	l=head;
	student_t *l2;
	l2=head;

	int s_id=-1,flag=0;
	printf("***请输入您想删除的学生id:");
	scanf("%d",&s_id);
	while(getchar()!='\n');

	if(head->next==NULL)
	{
		printf("******不存在学生信息,按回车键返回******\n");
		while(getchar()!='\n');
		return;
	}

	while(l2->next!=NULL)
	{
		if(l2->next->s_data.id==s_id)
		{
			flag=1;
		}
		l2=l2->next;
	}
	if(flag==0)
	{
		printf("**没有这样的学生,按回车键返回**\n");
		while(getchar()!='\n');
		return;
	}



	while(head->next->s_data.id!=s_id)
	{
		head=head->next;
	}
		temp=head->next;
		head->next=head->next->next;

	save_student(l);

	free(temp),temp=NULL;
	

	return;


	

}




//学生按照学号id排序
void student_id_sort()
{
	student_t *head=s_readfile();
	
	if(head==NULL)
	{
		printf("***没有学生信息");
		return ;
	}
	
	student_t *p1=head->next;
	student_t *low;
	student_t *p2;

	student_t *temp=(student_t *)malloc(sizeof(student_t));
	temp->next=NULL;

	while(p1!=NULL)
	{
		low=p1;
		p2=p1->next;
		while(p2!=NULL)
		{
			if(low->s_data.id > p2->s_data.id)
			{
				low=p2;
				p2=p2->next;
			}
			else
			{
				p2=p2->next;
			}
		}
			if(low!=p1)
			{
				temp->s_data=low->s_data;
				low->s_data=p1->s_data;
				p1->s_data=temp->s_data;
			}
			p1=p1->next;
		}	
	while(head->next!=NULL)
	{
		printf("id:%d\tname:%s\tmath:%.2f\tchinese:%.2f\tsum:%.2f\n",
				head->next->s_data.id,
				head->next->s_data.name,
				head->next->s_data.math,
				head->next->s_data.chinese,
				head->next->s_data.sum);
		head=head->next;
	
	}

}




//学生按照总分排序
void student_score_sort()
{
	student_t *head=s_readfile();
	
	if(head==NULL)
	{
		printf("***没有学生信息");
		return ;
	}
	
	student_t *p1=head->next;
	student_t *low;
	student_t *p2;

	student_t *temp=(student_t *)malloc(sizeof(student_t));
	temp->next=NULL;

	while(p1!=NULL)
	{
		low=p1;
		p2=p1->next;
		while(p2!=NULL)
		{
			if(low->s_data.math+low->s_data.chinese < p2->s_data.math+p2->s_data.chinese)
			{
				low=p2;
				p2=p2->next;
			}
			else
			{
				p2=p2->next;
			}
		}
			if(low!=p1)
			{
				temp->s_data=low->s_data;
				low->s_data=p1->s_data;
				p1->s_data=temp->s_data;
			}
			p1=p1->next;
		
	
	
	}
	while(head->next!=NULL)
	{
		printf("id:%d\tname:%s\tmath:%.2f\tchinese:%.2f\tsum:%.2f\n",
				head->next->s_data.id,
				head->next->s_data.name,
				head->next->s_data.math,
				head->next->s_data.chinese,
				head->next->s_data.sum);
		head=head->next;
	
	}

}


//学生按照数学排序
void student_math_sort()
{
	student_t *head=s_readfile();
	
	if(head==NULL)
	{
		printf("***没有学生信息");
		return ;
	}
	
	student_t *p1=head->next;
	student_t *low;
	student_t *p2;

	student_t *temp=(student_t *)malloc(sizeof(student_t));
	temp->next=NULL;

	while(p1!=NULL)
	{
		low=p1;
		p2=p1->next;
		while(p2!=NULL)
		{
			if(low->s_data.math < p2->s_data.math)
			{
				low=p2;
				p2=p2->next;
			}
			else
			{
				p2=p2->next;
			}
		}
			if(low!=p1)
			{
				temp->s_data=low->s_data;
				low->s_data=p1->s_data;
				p1->s_data=temp->s_data;
			}
			p1=p1->next;
		
	
	
	}
	while(head->next!=NULL)
	{
		printf("id:%d\tname:%s\tmath:%.2f\n",
				head->next->s_data.id,
				head->next->s_data.name,
				head->next->s_data.math);
		head=head->next;
	
	}

}


//学生按照语文排序
void student_chinese_sort()
{
	student_t *head=s_readfile();
	
	if(head==NULL)
	{
		printf("***没有学生信息");
		return ;
	}
	
	student_t *p1=head->next;
	student_t *low;
	student_t *p2;

	student_t *temp=(student_t *)malloc(sizeof(student_t));
	temp->next=NULL;

	while(p1!=NULL)
	{
		low=p1;
		p2=p1->next;
		while(p2!=NULL)
		{
			if(low->s_data.chinese < p2->s_data.chinese)
			{
				low=p2;
				p2=p2->next;
			}
			else
			{
				p2=p2->next;
			}
		}
			if(low!=p1)
			{
				temp->s_data=low->s_data;
				low->s_data=p1->s_data;
				p1->s_data=temp->s_data;
			}
			p1=p1->next;
		
	
	
	}
	while(head->next!=NULL)
	{
		printf("id:%d\tname:%s\tchinese:%.2f\n",
				head->next->s_data.id,
				head->next->s_data.name,
				head->next->s_data.chinese);
		head=head->next;
	
	}

}



//学生的密码修改
void update_student_passwd(int id)
{
	student_t *head=s_readfile();
	student_t *l;
	l=head;

	char newpasswd[20];
	while(head->next->s_data.id!=id)
	{
		head=head->next;
	}

	printf("**请输入您的新密码:\n");
	my_gets(newpasswd);
	strcpy(head->next->s_data.passwd,newpasswd);
	
	printf("**修改完成\n");

	save_student(l);

	return;
}


//学生查看自己信息及其总分排名
void show_my_info(int id)
{
	student_t *head=s_readfile();
	student_t *l;
	l=head;

	while(head->next->s_data.id!=id)
	{
		head=head->next;
	}

	printf("id:%d\tname:%s\tmath score:%.2f\tchinese score:%.2f\tsum:%.2f\n",
			head->next->s_data.id,
			head->next->s_data.name,
			head->next->s_data.math,
			head->next->s_data.chinese,
			head->next->s_data.sum);
	int a=0;
	a=student_score_sort_n(id);
	printf("**恭喜，您的总分排名为%d\n",a);

	return;
}



//计算学生_总分排名
int student_score_sort_n(int id)
{
	int n=1;

	student_t *head=s_readfile();
		
	student_t *p1=head->next;
	student_t *low;
	student_t *p2;

	student_t *temp=(student_t *)malloc(sizeof(student_t));
	temp->next=NULL;

	while(p1!=NULL)
	{
		low=p1;
		p2=p1->next;
		while(p2!=NULL)
		{
			if(low->s_data.math+low->s_data.chinese < p2->s_data.math+p2->s_data.chinese)
			{
				low=p2;
				p2=p2->next;
			}
			else
			{
				p2=p2->next;
			}
		}
			if(low!=p1)
			{
				temp->s_data=low->s_data;
				low->s_data=p1->s_data;
				p1->s_data=temp->s_data;
			}
			p1=p1->next;
		
	}

	while(head->next->s_data.id!=id)
	{
		head=head->next;
		n++;
	}

	return n;
}


//学生留言功能
void leave_word()
{
	int id_2=-1,flag=0;
	printf("输入你想留言的教师id:");
	scanf("%d",&id_2);
	while(getchar()!='\n');
	

	teacher_t *head=t_readfile();
	teacher_t *l;
	l=head;


	while(head->next!=NULL)
	{
		
		if(head->next->t_data.id == id_2)
		{
			flag=1;
			break;
		}
		head=head->next;
	}

	if(flag==0)
	{
		printf("***不存在这样的老师哦***\n");
		return;
	}

	char word_s[100]={"\0"};
	printf("你想说点什么呢?\n");
	scanf("%s",word_s);
	while(getchar()!='\n');

	strcat(head->next->t_data.word,"\n");
	strcat(head->next->t_data.word,word_s);

	save_teacher(l);
	
	return;
}


//教师查看自己留言
void show_leave_word(int id)
{
	teacher_t *head=t_readfile();
	teacher_t *l;
	l=head;

	while(head->next->t_data.id!=id)
	{
		head=head->next;
	}
	
	printf("这是您的留言部分:\n");
	printf("%s\n",head->next->t_data.word);
	
	return;
}


//提出辞职
void resign_work(int id)
{
	printf("您想好了不干了?\n1-->确认\n2-->我点错了\n");
	int cho3=-1;
	scanf("%d",&cho3);
	while(getchar()!='\n');

	teacher_t *head=t_readfile();
	teacher_t *l;
	l=head;

	while(head->next->t_data.id!=id)
	{
		head=head->next;
	}
	
	while(1)
	{
		switch(cho3)
		{
			case 1:
				head->next->t_data.t_flag=1;
				writefile_teacher(l);
				return;
				break;
			case 2:
				printf("***这还差不多***\n");
				return;
				break;
			default:
				printf("***这是开玩笑的事情吗，重新输入***\n");
				break;
		}
	}	
}


//删除辞职的教师信息
void del_teacher_resign(int id)
{
	teacher_t *head=t_readfile();
	teacher_t *l=NULL;
	teacher_t *temp=(teacher_t *)malloc(sizeof(teacher_t));
	l=head;


	while(head->next->t_data.id!=id)
	{
		head=head->next;
	}
		temp=head->next;
		head->next=head->next->next;

	writefile_teacher(l);

	free(temp),temp=NULL;
	
	printf("*****删除成功*****\n");

	return;
}

//是否保存--教师
void save_teacher(teacher_t *head)
{
	int j=0;
	while(1)
	{
		printf("是否保存?\n1-->保存\n2-->不保存\n");
		scanf("%d",&j);
		while(getchar()!='\n');
		switch(j)
		{
			case 1:
				writefile_teacher(head);
				printf("*****保存成功*****\n");
				return;
				break;
			case 2:
				printf("*****您选择不保存******\n**按回车键继续**\n");
				while(getchar()!='\n');
				return;
				break;
			default:
				printf("输入错误,请重新输入\n");
				break;
		}
	}
}


//是否保存--学生
void save_student(student_t *head)
{
	int j=0;
	while(1)
	{
		printf("是否保存?\n1-->保存\n2-->不保存\n");
		scanf("%d",&j);
		while(getchar()!='\n');
		switch(j)
		{
			case 1:
				writefile_student(head);
				printf("*****保存成功*****\n");
				return;
				break;
			case 2:
				printf("*****您选择不保存******\n**按回车键继续**\n");
				while(getchar()!='\n');
				return;
				break;
			default:
				printf("输入错误,请重新输入\n");
				break;
		}
	}
}






