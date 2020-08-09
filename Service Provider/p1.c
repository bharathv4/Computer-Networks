#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include<errno.h>
#include <sys/types.h>
#include <unistd.h>
#include<pthread.h>
#include<poll.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include<signal.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main()
{
mkfifo("serp1",0666);
int w=open("serp1",O_WRONLY);
	while(1)
	{char f[100]="\0";
	gets(f);
	write(w,f,sizeof(f));	
	}

}
