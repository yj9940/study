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
	//参数三:O_WRONLY-->      只写
	//      :O_RDWR

	//O_CREAT:若文件不存在，则以指定的权限创建文件
	fd=open(argv[1],O_WRONLY | O_CREAT,0664);
	if (-1==fd)
	{
		//strerror:将错误编号代表的错误信息返回
		printf("errno=%d,err:%s\n",errno,strerror(errno));
		return -1;
	}

	char *pData = "Hello 1711";
	ssize_t ret = -1;
	//fd:要错做的文件的文件描述符
	//pData:要写入的数据的地址
	//参数三:要写入的数据的大小
	ret = write(fd,pData,strlen(pData));
	if(-1==ret)
	{
		printf("errno=%d,err:%s\n",errno,strerror(errno));
		return -1;
	}
	

	printf("打开%s成功\n",argv[1]);
	printf("成功写入文件%d字节的数据\n",ret);
	close(fd);//关闭文件
	return 0;
}
