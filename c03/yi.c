#include <stdio.h>
int main()
{
  int a;
  printf("请输入成绩:");
  scanf("%d",&a);
  
  if(a>100 || a<0)
    
	  printf("你输入的成绩有误，请重新输入\n");
      
    
	  else if(a<60)
		  

				  printf("不及格！\n");
		  
        else printf("及格！\n");
 return 0;
}
