#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

int main(int argc,char *argv[])
{
	int srcfd=-1;
	srcfd=open(argv[1],O_RDONLY);
	if(-1==srcfd)
	{
		printf("errno:%d,err:%s",errno,strerror(errno));
		return -1;
	}

	int destfd=-1;
	destfd=open(argv[2],O_WRONLY | O_CREAT,0664);
	if(-1==destfd)
	{
		printf("errno:%d,err:%s",errno,strerror(errno));
		return -1;
	}
	printf("打开文件成功\n");
	
	int ret = -1;
	char buf[4096]={'\0'};
	while(1)
	{
		memset(buf,'\0',4096);
		ret = read(srcfd,buf,4096);
		if(-1==ret)
		{
			perror("read");
			return -1;
		}
		else if(0==ret)
		{
			printf("拷贝\n");
			break;
		}
		write(destfd,buf,4096);
	}
	close(srcfd);
	close(destfd);

	return 0;
}
