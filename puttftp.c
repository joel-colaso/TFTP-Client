#include <stdio.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUF_SIZE 500


int main (int argc, char * argv[]){
	
	if (argc !=  3) {
		perror("Error: 2 arguments needed");
	}
	
   //printf("Hello %s %s %s", argv[0], argv[1], argv[2]);
   
   // This is an example code from the manual
   
   int                      sfd, s;
   //char                     buf[BUF_SIZE];
   //ssize_t                  nread;
   //socklen_t                peer_addrlen;
   struct addrinfo          hints;
   struct addrinfo          *result, *rp;
   //struct sockaddr_storage  peer_addr;

   memset(&hints, 0, sizeof(hints));
   hints.ai_family = AF_UNSPEC;     // Allow IPv4 or IPv6 
   hints.ai_socktype = SOCK_DGRAM;  // Datagram socket 
   hints.ai_flags = AI_PASSIVE;     // For wildcard IP address 
   hints.ai_protocol = 0;           // Any protocol 
   hints.ai_canonname = NULL;
   hints.ai_addr = NULL;
   hints.ai_next = NULL;

   s = getaddrinfo(NULL, argv[1], &hints, &result);
   if (s != 0) {
	   fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
	   exit(EXIT_FAILURE);
   }

   // getaddrinfo() returns a list of address structures.
   // Try each address until we successfully bind(2).
   // If socket(2) (or bind(2)) fails, we (close the socket
   // and) try the next address. 

   for (rp = result; rp != NULL; rp = rp->ai_next) {
	   sfd = socket(rp->ai_family, rp->ai_socktype,
					rp->ai_protocol);
	   if (sfd == -1)
		   continue;

	   if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
		printf("Success\n\r");
		   break;                  // Success 

	   close(sfd);
   }

   freeaddrinfo(result);           // No longer needed 

   if (rp == NULL) {               // No address succeeded 
	   fprintf(stderr, "Could not bind\n");
	   exit(EXIT_FAILURE);
   }

   
   
   return 0;
}
