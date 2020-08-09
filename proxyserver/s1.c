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
int main()
{

 int s1fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

///////
s1fd = socket(AF_INET, SOCK_STREAM, 0);
//////
address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(  PORT1 );

bind(s1fd, (struct sockaddr *)&address,
                                 sizeof(address));


  ////////
  listen(s1fd,10);


	int ns1fd=accept(s1fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen);

	while(1)
	{
		char f[100]="\0";
		read(ns1fd,f,sizeof(f));
		strcat(f,"one");

		send(ns1fd,f,sizeof(f),0);
	}


}
