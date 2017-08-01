#ifndef _FUNC_C__
#define _FUNC_C__


void add_teacher_info();
void add_student_info();

//建立教师数组
struct t_message
{
	int id;
	char name[20];
	char passwd[20];
	char rank[20];
	char subject[20];
	char word[100];
	int t_flag;
	int last_flag;
};

//建立教师链表
typedef struct teacher
{
	struct t_message t_data;
	struct teacher *next;
}teacher_t;

//建立学生数组
struct s_message
{
	int id;
	char name[20];
	char passwd[20];
	float math;
	float chinese;
	float sum;
};

//建立学生链表
typedef struct student
{
	struct s_message s_data;
	struct student *next;
}student_t;

void writefile_teacher(teacher_t *head);
teacher_t *t_readfile();
void show_teacher();
void update_teacher_info();
void del_teacher_info();
void show_leave_word();
void del_teacher_resign(int id);
void resign_work(int id);

void writefile_student(student_t *head);
student_t *s_readfile();
void add_student_info();
void del_student_info();
void update_student_info();
void update_student_math();
void update_student_chinese();
void show_student();
void student_id_sort();
void student_score_sort();
void student_math_sort();
void student_chinese_sort();
void update_teacher_passwd(int id);
void show_student_math();
void show_student_chinese();
void update_student_passwd(int id);
void show_my_info(int id);
int student_score_sort_n(int id); 
void leave_word();

void save_teacher(teacher_t *head);
void save_student(student_t *head);

#endif
