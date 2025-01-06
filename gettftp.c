#include <stdio.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


#define TFTP_PORT "69"


/*

void print_address_info(struct addrinfo *addr_list) {
    char ipstr[INET6_ADDRLEN];
    struct addrinfo *addr;
    
    for (addr = addr_list; addr != NULL; addr = addr->ai_next) {
        void *addr_ptr;
        
        // Get the pointer to the address itself
        if (addr->ai_family == AF_INET) {  // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)addr->ai_addr;
            addr_ptr = &(ipv4->sin_addr);
        } else {  // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)addr->ai_addr;
            addr_ptr = &(ipv6->sin6_addr);
        }
        
        // Convert IP to string
        inet_ntop(addr->ai_family, addr_ptr, ipstr, sizeof ipstr);
        printf("IP address: %s\n", ipstr);
    }
}

*/





int main (int argc, char * argv[]){
	
	if (argc !=  3) {
		perror("Error: 2 arguments needed");
	}
	
	
    printf("Hello %s %s %s\n\r", argv[0], argv[1], argv[2]);
   
   
    char *host = argv[1];
    char *filename = argv[2];

    printf("Host: %s\n", host);
    printf("File: %s\n", filename);
    
    
    // Prepare hints for getaddrinfo
    struct addrinfo hints, *server_info;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;     // Allow IPv4 or IPv6
    hints.ai_socktype = SOCK_DGRAM;  // Datagram socket for UDP
    
    
    // Get address information
    int status;
    if ((status = getaddrinfo(host, TFTP_PORT, &hints, &server_info)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }
    
    
    int sock;
	if((sock = socket (AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socketerror") ;
		exit(EXIT_FAILURE) ;
	}

		
    
    
    
    // Free the linked list
    freeaddrinfo(server_info);


   return 0;
}
