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
# define PORT 7266
 int main() {


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

int clsfd[30],clsz=0;
struct pollfd fds[100];fds[0].events=POLLIN;fds[0].fd=sfd;
while(1)
{


  poll(fds,clsz+1,3000);
  //////
  if(fds[0].revents & POLLIN)
  {
    clsz++;
    clsfd[clsz]=accept(sfd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen);
                       printf("client added,%d\n",clsz);

         fds[clsz].events=POLLIN;fds[clsz].fd=clsfd[clsz];

  }

  for(int i=1;i<=clsz;i++)
  {
        if(fds[i].revents & POLLIN)
        {
            char m[100]=NULL;read(clsfd[i],m,sizeof(m));
printf("read %s\n",m);

            for(int j=1;j<=clsz;j++)
            {
              if(j!=i)
              {
                send(clsfd[j],m,sizeof(m),0);
              }

            }


        }

  }


}


  return 0;
}
