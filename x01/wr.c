#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

int main(int argc,char *argv[])
{
	int fd=-1;
	fd=open(argv[1],O_WRONLY | O_CREAT,0664);
	if(-1==fd)
	{
		printf("errno:%d,err:%s",errno,strerror(errno));
		return -1;
	}

	char *data="我看到你了";
	ssize_t ret=-1;

	ret = write(fd,data,strlen(data));
	if(-1==ret)
	{
		printf("errno:%d,err:%s",errno,strerror(errno));
		return -1;
	}

	printf("差不多吧\n");
	printf("写进去%d个字节\n",ret);
	close(fd);
	return 0;
}
