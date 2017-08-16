#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#include<sys/type.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

int main(int argc,char *argv[])
{
	int fd=-1;
	fd=open(argv[1],O_RDONLY | O_CREAT,0664);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}

	printf("打开文件%s成功\n",argv[1]);

	char buf[4096]={'\n'};
	int ret=-1;

	ret=read(fd,buf,sizeof(buf));
	if(-1==ret)
	{
		perror("read");
		return -1;
	}
	else if(0==ret)
	{
		break;
	}

	printf("读到%d字节的数据:%s\n",ret,buf);
	close(fd);
}
