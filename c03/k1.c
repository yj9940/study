#include <stdio.h>
int main()
{   int n;
	float a[100],rs;
	char ch;
	scanf("%f%c%f",&a[0],&ch,&a[1]);
	switch(ch){
	case('+'):
    {	printf("结果%.2f",a[0]+a[1]);
		rs=a[0]+a[1]; 
	break;}
	case('-'):
	{   printf("结果%.2f",a[0]-a[1]);
		rs=a[0]-a[1];
	break;}
	case('*'):
	{   printf("结果%.2f",a[0]*a[1]);
		rs=a[0]*a[1];
	break;	}
	case('/'):
	{   printf("结果%.2f",a[0]/a[1]);
		rs=a[0]/a[1];
	break;	}
	default:
	{	printf("无结果\n");
			return 0;}
	}
    for(n=1;n<100;n++){
	getchar();
	printf("\n");
	scanf("%c%f",&ch,&a[n]);
	if('+' == ch){
		rs=rs+a[n];}
	else if('-' == ch){
		rs=rs-a[n];}
	else if('*' == ch){
		rs=rs*a[n];}
	else if('/' == ch && a[n] != 0){
		rs=rs/a[n];}
    else{ printf("无结果\n");
	return 0;}
	printf("结果%.2f",rs);}
		return 0;
}
