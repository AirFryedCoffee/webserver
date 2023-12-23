#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> 
#include <arpa/inet.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netdb.h>


/*
Create a function that creates a socket. The socket() command takes in AF_INET, SOCK_STREAM,
& 0, which are parameters that represent IPv4, a 2 way stream, and TCP Port 0
*/

short socketCreate(void) {
    short hSocket = 0;
    printf("Create the socket\n");
    hSocket = socket(AF_INET, SOCK_STREAM, 0);
    return hSocket;
}


int bindCreatedSocket(int hSocket) {
    int iRetval = -1;
    int clientPort = 12345;

    struct sockaddr_in remote = {0};

    remote.sin_family = AF_INET;

    remote.sin_addr.s_addr = htonl(INADDR_ANY);
    remote.sin_port = htons(clientPort);

    iRetval = bind(hSocket, (struct sockaddr *) & remote, sizeof(remote));
    return iRetval;
}

int main(int argc, char *argv[]) {
        int socket_desc = 0, sock = 0, clinetLen = 0;
        struct sockaddr_in client;
        char client_message[200] = {0};
        char message[100] = 0;
        const char *pMessage = "Hello from the server";


        socket_desc = socketCreate();
        if (socket_desc == -1) {
            printf("Could not accept the socket");
            return 1;
        }

        printf("Socket Created");

        if (bindCreatedSocket(socket_desc) < 0) {
            perror("bind failed");
            return 1;
        }

        printf("bind done\n");

        listen(socket_desc, 3);

        while(1) {
            printf("Waiting for incoming connections...\n");
            clinetLen = sizeof(struct sockaddr_in);
        }
}




