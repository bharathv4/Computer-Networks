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
#include <stdbool.h> 
# define PORT 7266
bool isecho[30];int clsz=0;
int ecmap[10000];
int clientechoindex=1;

struct pollfd clsfd[30];
// I have set the echo server such that it exits after 5 or any number of services to the respective connected client.
static void hdl (int sig, siginfo_t *siginfo, void *context)
{
	//printf ("Sending PID: %ld\n",
			//(long)siginfo->si_pid);fflush(stdout);
			isecho[ecmap[(long)siginfo->si_pid]]=false;
}
void handler()
{	int cc=clientechoindex;
	isecho[clientechoindex]=true;
	clientechoindex++;
	int c=0;c=fork();
	if(c==0)
	{
		 //char m[100]='\0';read(clsfd[clientechoindex-1],m,sizeof(m));
		//m="ypu are served by echo";		
		//send(clsfd[clientechoindex-1],m,sizeof(m));
		dup2(clsfd[cc].fd,0);
		execv("./echo",NULL);
		
		
	}
	else
	{
	
	ecmap[c]=cc;
	//////////////////////
		struct sigaction act,o;
 
	memset (&act, '\0', sizeof(act));
	act.sa_sigaction = &hdl;
	act.sa_flags = SA_SIGINFO;
 
	if (sigaction(SIGCHLD, &act, &o) < 0) {
		perror ("sigaction");
		
	}
	///////////////////
	}
}

 int main() {
/////////
  int sfd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

///////
sfd = socket(AF_INET, SOCK_STREAM, 0);
//////
address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(  PORT );
  ///////////////////////////
bind(sfd, (struct sockaddr *)&address,
                                 sizeof(address));


  ////////
  listen(sfd,10);
  //////////

////////////
int t;t=getpid();


 for(int i=0;i<10000;i++){ecmap[i]=0;}
 //////////
		


	mkfifo("serp1",0666);
	int r1=open("serp1",O_RDONLY);
////////////
printf("pid sent is %d\n",t);
	mkfifo("serp4",0666);
	int w4=open("serp4",O_WRONLY);


	printf("pid sent is %d\n",t);
	write(w4,t,sizeof(t));
printf("pid sent is %d\n",t);
///////
signal(SIGUSR1,handler);

	
for(int i=1;i<30;i++){isecho[i]=false;
      }
clsfd[0].fd=sfd;clsfd[0].events=POLLIN;     

while(1)
{
//////////////////////
   
 
///////////////////

	printf("yes\n");
  poll(clsfd,clsz+1,3000);
  //////
  if(clsfd[0].revents & POLLIN)
  {
    clsz++;
    clsfd[clsz].fd=accept(sfd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen);
clsfd[clsz].events=POLLIN;
                      
 printf("client added,%d\n",clsz);

      

  }

  for(int i=1;i<=clsz;i++)
  {
        if(clsfd[i].revents & POLLIN)
        {
            char m[100]="\0";read(clsfd[i].fd,m,sizeof(m));
		printf("read %s\n",m);

            for(int j=1;j<=clsz;j++)
            {
              if(j!=i&&isecho[i]==false&&isecho[j]==false)
              {
                send(clsfd[j].fd,m,sizeof(m),0);
              }

            }


        }

  }
  


}


  return 0;
}
