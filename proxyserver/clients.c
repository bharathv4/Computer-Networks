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
#define PORT 7788
#define PORT1 7789
#define PORT2 7790
#define PORT3 7791
#define PORT4 7792
#define PORT5 7793
int sock = 0;
void* readt()
{ while(1)
  {int v;char bu[1024];
  v = read( sock , bu, sizeof(bu));
  printf("%s\n",bu );
  }
}
void* writet()
{
  while(1)
  {char hh[100];
  scanf("%s",hh);
    send(sock , hh , strlen(hh) , 0 );
//  printf("Hello message sent\n");
}
}
 int main() {
   int valread;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    pthread_t tid;pthread_create(&tid,NULL,readt,NULL);
  pthread_t wtid;pthread_create(&wtid,NULL,writet,NULL);
pthread_join(tid, NULL); pthread_join(wtid, NULL);
    

  return 0;
}
