#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

#include<sys/type.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

int main(int argc,char *argv[])
{
	int fd=-1;
	fd=open(argv[1],O_RDONLY);
	if(-1 == fd)
	{
		printf("error=%d,err:%s",errno,strerror(errno));
		return -1;
	}
	
	printf("打开文件%s成功\n",argv[1]);
	close(fd);
	return 0;
}

