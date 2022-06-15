// g++ -g -o get_macaddr get_macaddr.c

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/ether.h>


//+++++++++++++++++++++++++++++++++++++++++++++++++
int get_macaddr
(
	char *t_macaaadr
)
{
	int ifs = 0;
	
	//int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	int sockfd = socket(PF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0) return -1;

	struct ifconf ifc;
	memset(&ifc, 0x00, sizeof(struct ifconf));

	if(ioctl(sockfd, SIOCGIFCONF, &ifc) < 0) return -2;

	// 메모리 확보
	struct ifreq  * pifreq = (ifreq *)malloc(ifc.ifc_len);
	ifc.ifc_ifcu.ifcu_req = pifreq;

	if(ioctl(sockfd, SIOCGIFCONF, &ifc) < 0) return -2;

	ifs = ifc.ifc_len / sizeof(struct ifreq);
	printf("if count = %d\n", ifs);
	
	for(int n=0; n<ifs; n++)
	{
		struct ifreq *req = &pifreq[n];

		if(!strcmp(req->ifr_name, "lo")) continue;

		if(ioctl(sockfd, SIOCGIFHWADDR, req) < 0) break;

		sprintf(t_macaaadr, 
				"%s : %02x:%02x:%02x:%02x:%02x:%02x",
				req->ifr_name,
				(unsigned char)req->ifr_hwaddr.sa_data[0],
				(unsigned char)req->ifr_hwaddr.sa_data[1],
				(unsigned char)req->ifr_hwaddr.sa_data[2],
				(unsigned char)req->ifr_hwaddr.sa_data[3],
				(unsigned char)req->ifr_hwaddr.sa_data[4],
				(unsigned char)req->ifr_hwaddr.sa_data[5]);
	};

	free(pifreq);
	close(sockfd);
    return 0;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++
int main()
{
	char t_macaadr[50];
	memset(t_macaadr, 0x00, 50);
	
	int r= get_macaddr(t_macaadr);
	if(r) exit(1);
	
	printf("MAC address :\n%s\n", t_macaadr);
};