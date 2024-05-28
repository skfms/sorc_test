
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>
#include <errno.h>
#include <sys/time.h>

#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

#include <pcap.h>

#define PROMISCUOUS 1
#define NONPROMISCUOUS 0

// IP 헤더 구조체
struct ip *iph;

// TCP 헤더 구조체
struct tcphdr *tcph;

#define ETHERNET_HEADER_LEN 16
#define IP_HEADER_LEN 20

void PrintData (const u_char* data , int Size)
{
	int i , j;
	for(i=0 ; i < Size ; i++)
	{
		if( i!=0 && i%16==0)   //if one line of hex printing is complete...
		{
			fprintf(stdout , "         ");
			for(j=i-16 ; j<i ; j++)
			{
				if(data[j]>=32 && data[j]<=128)
					fprintf(stdout , "%c",(unsigned char)data[j]); //if its a number or alphabet
				
				else fprintf(stdout , "."); //otherwise print a dot
			}
			fprintf(stdout , "\n");
		} 
		
		if(i%16==0) fprintf(stdout , "   ");
			fprintf(stdout , " %02X",(unsigned int)data[i]);
				
		if( i==Size-1)  //print the last spaces
		{
			for(j=0;j<15-i%16;j++) 
			{
			  fprintf(stdout , "   "); //extra spaces
			}
			
			fprintf(stdout , "         ");
			
			for(j=i-i%16 ; j<=i ; j++)
			{
				if(data[j]>=32 && data[j]<=128) 
				{
				  fprintf(stdout , "%c",(unsigned char)data[j]);
				}
				else 
				{
				  fprintf(stdout , ".");
				}
			}
			
			fprintf(stdout ,  "\n" );
		}
	}
}

// 패킷을 받아들일경우 이 함수를 호출한다.  
// packet 가 받아들인 패킷이다.
void callback
(
	u_char *useless, 
	const struct pcap_pkthdr *pkthdr, 
	const u_char *packet
)
{
	int size = pkthdr->len;

	struct iphdr *iph = (struct iphdr*)(packet + sizeof(struct ethhdr));
	switch (iph->protocol)
	{
		case  1: printf("ICMP Packet\n"); break;
		case  2: printf("IGMP Packet\n"); break;
		case 17: printf("UDP Packet\n"); break;
		case  6:
			{
				printf("TCP Packaet\n");

				int size = pkthdr->len;

				struct iphdr *iph = (struct iphdr *)(packet  + sizeof(struct ethhdr));
				unsigned short iphdrlen = iph->ihl*4;
	
				struct tcphdr *tcph=(struct tcphdr*)(packet + iphdrlen + sizeof(struct ethhdr));
				int header_size =  sizeof(struct ethhdr) + iphdrlen + tcph->doff*4;				

				{
					struct sockaddr_in sorc, dest;

					memset(&sorc, 0x00, sizeof(sorc));
					sorc.sin_addr.s_addr = iph->saddr;

					memset(&dest, 0x00, sizeof(dest));
					dest.sin_addr.s_addr = iph->daddr;

					printf("sorc_ip=%s(%u) / dest_ip=%s(%u) pktsz=%u\n", 
						inet_ntoa(sorc.sin_addr), ntohs(tcph->source), 
						inet_ntoa(dest.sin_addr), ntohs(tcph->dest),
						size - header_size
						);

				};

				PrintData(packet+header_size, size - header_size);
			};
			break;
		default: printf("Other Protocol\n"); break;
	};
}    


int main(int argc, char **argv)
{
    char *dev;
    char *net;
    char *mask;

    bpf_u_int32 netp;
    bpf_u_int32 maskp;
    char errbuf[PCAP_ERRBUF_SIZE];
    int ret;
    struct pcap_pkthdr hdr;
    struct in_addr net_addr, mask_addr;
    struct ether_header *eptr;
    const u_char *packet;

    struct bpf_program fp;     

    pcap_t *pcd;  // packet capture descriptor

    // 사용중인 디바이스 이름을 얻어온다. 
    dev = pcap_lookupdev(errbuf);
    if (dev == NULL)
    {
        printf("%s\n", errbuf);
        exit(1);
    }
    printf("DEV : %s\n", dev);

    // 디바이스 이름에 대한 네트웍/마스크 정보를 얻어온다. 
    ret = pcap_lookupnet(dev, &netp, &maskp, errbuf);
    if (ret == -1)
    {
        printf("%s\n", errbuf);
        exit(1);
    }

    // 네트웍/마스트 정보를 점박이 3형제 스타일로 변경한다. 
    net_addr.s_addr = netp;
    net = inet_ntoa(net_addr);
    printf("NET : %s\n", net);

    mask_addr.s_addr = maskp;
    mask = inet_ntoa(mask_addr);
    printf("MSK : %s\n", mask);
    printf("=======================\n");

    // 디바이스 dev 에 대한 packet capture 
    // descriptor 를얻어온다.   
    pcd = pcap_open_live(dev, BUFSIZ,  NONPROMISCUOUS, -1, errbuf);
    if (pcd == NULL)
    {
        printf("%s\n", errbuf);
        exit(1);
    }    

    // 컴파일 옵션을 준다.
    if (pcap_compile(pcd, &fp, argv[2], 0, netp) == -1)
    {
        printf("compile error\n");    
        exit(1);
    }
    // 컴파일 옵션대로 패킷필터 룰을 세팅한다. 
    if (pcap_setfilter(pcd, &fp) == -1)
    {
        printf("setfilter error\n");
        exit(0);    
    }

    // 지정된 횟수만큼 패킷캡쳐를 한다. 
    // pcap_setfilter 을 통과한 패킷이 들어올경우 
    // callback 함수를 호출하도록 한다. 
    pcap_loop(pcd, atoi(argv[1]), callback, NULL);
}
