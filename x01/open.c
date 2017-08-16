#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#include<errno.h>    //errno

int main(int argc,char *argv[])
{
	int fd=-1;
	//若以一下方式打开文件，若文件不存在不会自动创建文件
	//参数一:argv[1]:要打开的文件
	//参数二:O_RDONLY-->表示以只读的方式打开
	//参数三:O_WRONLY
	//       O_RDWR
	fd=open(argv[1],O_RDONLY);
	if (-1==fd)
	{
		//strerror:将错误编号代表的错误信息返回
		printf("errno=%d,err:%s\n",errno,strerror(errno));
		return -1;
	}
	printf("打开%s成功\n",argv[1]);
	close(fd);//关闭文件
	return 0;
}
