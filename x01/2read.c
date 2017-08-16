#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#include<errno.h>    //errno

ssize_t readDataFromFile()






int main(int argc,char *argv[])
{
	int fd=-1;
	fd=open(argv[1],O_RDONLY | O_CREAT,0664);
	if (-1==fd)
	{
		//strerror:将错误编号代表的错误信息返回
		printf("errno=%d,err:%s\n",errno,strerror(errno));
		return -1;
	}

	printf("打开%s成功\n",argv[1]);

	char caBuf[4096]={'\0'};
	int ret=-1;

	ret=read(fd,caBuf,sizeof(caBuf));//strlen(caBuf)计算到'\0'

	if(-1==ret)
	{
		perror("read");
		return -1;
	}

	//0==ret:读到文件末尾或者空文件-->无数据可读
	else if(0==ret)
	{
		return 0;
	}
	printf("读到%d字节的数据:%s\n",ret,caBuf);
	
	close(fd);//关闭文件
	return 0;
}
