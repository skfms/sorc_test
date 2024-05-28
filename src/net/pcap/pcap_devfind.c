// gcc -o pcap_devfind pcap_devfind.c -lpcap

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pcap.h>

int main(int argc, char *argv[])
{
	char errbuf[PCAP_ERRBUF_SIZE];

	char *dev = (char *)pcap_lookupdev(errbuf);
	if (dev == NULL) {
		fprintf(stderr, "Couldn't find default device: %s\n", errbuf);
		return(2);
	}
	printf("Device: %s\n", dev);
	return(0);
}
