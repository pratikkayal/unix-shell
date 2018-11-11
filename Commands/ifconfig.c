#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <ifaddrs.h>
// #include <arpa/inet.h>
// #include <sys/socket.h>
// #include <linux/if_link.h>

int ifconfig_command()
{
	struct ifaddrs *ifaddr, *ifa;
	int family, s, m, n;
	char host[NI_MAXHOST];
	char netmask[NI_MAXHOST];

	// The  getifaddrs() function creates a linked list of structures describ‐
	// ing the network interfaces of the local system, and stores the  address
	// of  the  first item of the list in *ifaddr 
	if (getifaddrs(&ifaddr) == -1) {
		perror("Failed to getifaddrs");
	}

	// Walk through linked list, maintaining head pointer ifaddr so we can free list later
	for (ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++) {
			if (ifa->ifa_addr == NULL)
					continue;

			family = ifa->ifa_addr->sa_family;

			//For an AF_INET* interface address, display the address

			if (family == AF_INET || family == AF_INET6)
			{
				// Display interface name and family (including symbolic form of the latter for the common families)
				printf("%-10s %s \n", ifa->ifa_name,
						(family == AF_PACKET) ? "AF_PACKET" :
						(family == AF_INET) ? "AF_INET" :
						(family == AF_INET6) ? "AF_INET6" : "???");

				s = getnameinfo(ifa->ifa_addr,(family == AF_INET) ? sizeof(struct sockaddr_in):sizeof(struct sockaddr_in6),
								host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
				m = getnameinfo(ifa->ifa_netmask,(family == AF_INET) ? sizeof(struct sockaddr_in):sizeof(struct sockaddr_in6),
								netmask, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
				if (s != 0) 
				{
						perror("getnameinfo() failed");
						// printf("getnameinfo() failed: %s\n", gai_strerror(s));
				}
				printf("\taddress: %s\n", host);
				printf("\tnet mask: %s\n", netmask);
			}
	}
	freeifaddrs(ifaddr);


	// // Now get packet transmission/receive failures
	printf("\n\nNow get packet transmission/receive Statistics\n\n");
	FILE *file;
	file = fopen("/proc/net/dev", "r");
	//read line by line
	const size_t line_size = 300;
	char* line = malloc(line_size);
	while (fgets(line, line_size, file) != NULL)
	{
		printf("%s\n",line);
	}
	free(line); 
	fclose(file);
}