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
# define PORT1 7212
# define PORT2 7269
int main()
{int t=5;
// I have set the echo server such that it exits after 5 or any number of services to the respective connected client.
int th;dup2(0,th);fflush(stdin);
while(t--)
  {char hh[100];
  read(th,hh,sizeof(hh));
	strcpy(hh,"ewwefwoiejfown");
   send(th,hh,sizeof(hh),0);
//  printf("Hello message sent\n");
}
return 0;
}
