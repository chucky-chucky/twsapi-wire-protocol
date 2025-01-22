/*
 * TWS Wire Protocol Connection Test
 * 
 * This program is simply used to test your connection.
 * press the green DATA button on you TWS workstation to
 * observe a successful connection. 
 * 
*/
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
 
using namespace std;

/*
 * 	Default usage connects to localhost 127.0.0.1 and port 7496
 * 	If your connecting from another computer you can either enter
 * 	the ipaddress and port on the command line or change them here.
 * 
 */
  
string ipAddress = "127.0.0.1";
int ipPort = 7496;

int StartTWS()
{
    int status, client_fd;
    struct sockaddr_in serv_addr;
    unsigned char login[100] = { 'A','P','I','\0','\0','\0','\0','\x9','v','1','0','0','.','.','1','7','6'};
    unsigned char startAPI[100] = { '\0','\0','\0','\x8','7','1','\0','2','\0','0','\0','\0'};
//    char buffer[1024] = { 0 };
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(ipPort);

    // Convert IPv4 and IPv6 addresses from text to binary form

    if (inet_pton(AF_INET, ipAddress.c_str(), &serv_addr.sin_addr) <= 0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if ((status = connect(client_fd, (struct sockaddr*)&serv_addr,sizeof(serv_addr))) < 0) {
        printf("\nConnection Failed \n\n");
        printf("Check your TWS Workstaion API settings. Insure that your API\n");
        printf("is checked: 'Enable ActiveX and Socket Clients'\n");
        printf("The Socket Port matches the Port this test app is using\n");
        printf("Scroll to the bottom and if you are connecting from another computer\n");
        printf("uncheck the box 'Allow connections from localhost only' and\n");
		printf("enter your ip address in the Trusted IPs window and\n");
		printf("make sure your calling the TWS Workstation ip address.\n\n");
        
        return -1;
    }
    
    printf("Sending API Negotiation\n");   
    send(client_fd, login, 17, 0);
    send(client_fd, startAPI, 12, 0);
    
	printf("\nPress Enter to close the connection\n");
	getchar();

    // closing the connected socket
    close(client_fd);
    return 0;
}
   
int main(int argc, char const* argv[])
{
	printf("argc= %d\n",argc);
	if (argc >= 2) ipAddress = argv[1];
	if (argc >= 3) ipPort = atoi(argv[2]);
	
	printf("Trying ip: %s port: %d\n", ipAddress.c_str(), ipPort);
	
	StartTWS();
    return 0;
}

