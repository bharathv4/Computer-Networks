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
mkfifo("serp4",0666);
int r=open("serp4",O_RDONLY);
printf("Enter server's pid\n");
int t;scanf("%d",&t);//read(r,t,sizeof(t));
printf("%d\n",t);
while(1)
{
printf("any text to send signals\n");
char f[100];scanf("%s",f);
kill(t,SIGUSR1);
}


}
