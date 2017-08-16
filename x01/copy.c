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
	int srcfd=-1;
	srcfd=open(argv[1],O_RDONLY);
	if (-1==srcfd)
	{
		//strerror:将错误编号代表的错误信息返回
		printf("errno=%d,err:%s\n",errno,strerror(errno));
		return -1;
	}

	int destfd=-1;
	destfd=open(argv[2],O_WRONLY | O_CREAT,0664);
	if (-1==destfd)
	{
		//strerror:将错误编号代表的错误信息返回
		printf("errno=%d,err:%s\n",errno,strerror(errno));
		return -1;
	}

	printf("打开%s成功\n",argv[1]);

	char caBuf[4096]={'\0'};
	int ret=-1;

	while(1)
	{
		memset(caBuf,'\0',4096);
		//fd:要操作的文件
		//caBuf:要存放的地址
		ret=read(srcfd,caBuf,sizeof(caBuf));//strlen(caBuf)计算到'\0'
	
		if(-1==ret)
		{
			perror("read");
			return -1;
		}
		//0==ret:读到文件末尾或者空文件-->无数据可读
		else if(0==ret)
		{
			printf("拷贝完成\n");
			break;
		}
		write(destfd,caBuf,ret);
	}

	printf("写入完成\n");
	close(srcfd);//关闭文件
	close(destfd);
	return 0;
}
