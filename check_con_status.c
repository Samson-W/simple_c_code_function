/****************************************************
 * Function of this function: 
 * 		Complete the detection of the port is open.
 * Date:
 *      09/17/2015
 * Author:
 *      Samson-w
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

/********************************************************************
 * Function:
 * 		check_con_status: Check connect cur status(open or close).
 * Param:
 *      addr_str: 
 *         The string contains the IP address and port to be tested.
 *      addr_len:
 *         length of addr_str.
 * Return:
 * 		If open return 0, else return -1.
 *
 *********************************************************************/
int check_con_status(const char *addr_str, int addr_len)
{
	int sockfd, rc, port;
    char *tok, *ipaddr, *portstr, addr[32] = {0};
    struct sockaddr_in servaddr;

	strncpy(addr, addr_str, addr_len);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1 ) { 
        return -1;      
    }
    tok = addr;;
    ipaddr = strtok(tok, ":");
	portstr = addr + strlen(ipaddr) + 1;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    rc = inet_pton(AF_INET, ipaddr, &servaddr.sin_addr);
    if ( rc != 1 ) {
        close(sockfd);
        return -1;  
    }
	port = atoi(portstr);
    servaddr.sin_port = htons(port);
    rc = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    if (rc != 0) {
        close(sockfd);
        return -1;
    }
    close(sockfd);
    return 0;

}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Use useage: check_con_status 111.111.111.111:9999\n");
		return 1;
	}
	char *addr_string = argv[1];
	int rc = check_con_status(addr_string, strlen(addr_string));
	if (rc == 0) {
		printf("%s is Open!\n", argv[1]);
	} else {
		printf("%s is Close!\n", argv[1]);
	}
	return 0;
}
