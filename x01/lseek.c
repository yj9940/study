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
	fd=open(argv[1],O_RDONLY);
	if (-1==fd)
	{
		printf("errno=%d,err:%s\n",errno,strerror(errno));
		return -1;
	}

	off_t size = lseek(fd,0,SEEK_END);//文件末尾
	if (-1 == size)
	{
		perror("lseek");
		return -1;
	}
	printf("%s size is %d\n",argv[1],size);
	close(fd);//关闭文件
	return 0;
}
