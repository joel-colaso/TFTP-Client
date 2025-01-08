/*
 * TCB connect important  
 * UDP does not use connect
 *
 */

#include <stdio.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define N_EXPECTED_ARGUMENTS 3
#define HOST_ARGUMENT_INDEX 1
#define FILENAME_ARGUMENT_INDEX 2

#define TFTP_PORT "69"
#define RRQ_PACKET_STRING_LENGTH
#define RRQ_PACKET_STRING_TEMPLATE "1%s\0NETASCII\0" // %s is the filename

int main (int argc, char * argv[]){
	
	if (argc !=  N_EXPECTED_ARGUMENTS) {
		perror("Error: 2 arguments needed");
	}
	   
    char *host = argv[HOST_ARGUMENT_INDEX];
    char *filename = argv[FILENAME_ARGUMENT_INDEX];

    printf("Host: %s\n", host);
    printf("File: %s\n", filename);
    

    struct addrinfo hints = {0};
    hints.ai_family = AF_UNSPEC;     // allow IPv4 or IPv6
    hints.ai_socktype = SOCK_DGRAM;  // datagram socket for UDP
    
    struct addrinfo *server_info;
    
    int status;
    if ((status = getaddrinfo(host, TFTP_PORT, &hints, &server_info)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }
    
    
    
    int socketFileDescriptor;
	if((socketFileDescriptor = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socketerror") ;
		exit(EXIT_FAILURE) ;
	}

	
	
	char* RRQPacketString[RRQ_PACKET_STRING_LENGTH];
	snprintf(RRQPacketString, RRQ_PACKET_STRING_TEMPLATE, filename);
    
    
    
    freeaddrinfo(server_info);


   return 0;
}
