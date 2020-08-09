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
int cltos[100];
int clfd[100];int clsz=0;
void server1()
{
/////////////////
 int s1fd;
 struct sockaddr_in serv_addr;

    if ((s1fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT1);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(s1fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
  ///////////////////////
	
	struct pollfd pfd[100];
	while(1)
	{
		for(int i=0;i<clsz;i++)
		{
		pfd[i].fd=clfd[i];pfd[i].events=POLLIN;
		
		}
		
		poll(pfd,clsz,3000);
		
		for(int i=0;i<=clsz;i++)
		{
		
			if(pfd[i].revents & POLLIN)
			{
				if(cltos[i]==1)
				{
				
					char h[100]="\0";
					read(clfd[i],h,sizeof(h));
					send(s1fd,h,sizeof(h),0);
					read(s1fd,h,sizeof(h));
					send(clfd[i],h,sizeof(h),0);
					
				}
			}
		
		}
		
	
	
	
	
	
	
	}
	
	

}
//////////////////////////////////////////////////
//////////////////////////////////////////////////
void server2()
{
/////////////////
 int s2fd;
 struct sockaddr_in serv_addr;

    if ((s2fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT2);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(s2fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
  ///////////////////////
	
	struct pollfd pfd[100];
	while(1)
	{
		for(int i=0;i<clsz;i++)
		{
		pfd[i].fd=clfd[i];pfd[i].events=POLLIN;
		
		}
		
		poll(pfd,clsz,3000);
		
		for(int i=0;i<=clsz;i++)
		{
		
			if(pfd[i].revents & POLLIN)
			{
				if(cltos[i]==2)
				{
				
					char h[100]="\0";
					read(clfd[i],h,sizeof(h));
					send(s2fd,h,sizeof(h),0);
					read(s2fd,h,sizeof(h));
					send(clfd[i],h,sizeof(h),0);
					
				}
			}
		
		}
		
	
	
	
	
	
	
	}
	
	

}
///////////////////////
/////////////////////
void server3()
{
/////////////////
 int s3fd;
 struct sockaddr_in serv_addr;

    if ((s3fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT3);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(s3fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
  ///////////////////////
	
	struct pollfd pfd[100];
	while(1)
	{
		for(int i=0;i<clsz;i++)
		{
		pfd[i].fd=clfd[i];pfd[i].events=POLLIN;
		
		}
		
		poll(pfd,clsz,3000);
		
		for(int i=0;i<=clsz;i++)
		{
		
			if(pfd[i].revents & POLLIN)
			{
                                        char h[100]="\0";
					read(clfd[i],h,sizeof(h));
			for(int i=0;i<=clsz;i++)
			{
				if(cltos[i]==3)
				{
				
					
					send(s3fd,h,sizeof(h),0);
					read(s3fd,h,sizeof(h));
					send(clfd[i],h,sizeof(h),0);
					
				}
			}
			
					}
		
		}
		
	
	
	
	
	
	
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
/////////////////////////////////

pthread_t tid1;pthread_create(&tid1,NULL,server1,NULL);
pthread_t tid2;pthread_create(&tid2,NULL,server2,NULL);
pthread_t tid3;pthread_create(&tid3,NULL,server3,NULL);

printf("haa tho\n");
while(1)
{
	clfd[clsz]=accept(sfd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen);
	
	
 	printf("client added,%d\n",clsz);
	char m[20];
	recv(clfd[clsz],m,sizeof(m),0);
	//int in;
	fflush(stdout);
int val=atoi(&m);
	//printf("what server to be connected\n");fflush(stdout);
	//scanf("%d\n",&in);
	printf("%d is connected",val);fflush(stdout);
	cltos[clsz]=val;
	clsz++;

}


}
