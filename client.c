#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

short socketCreate(void) {
    short hSocket;
    printf("Create the socket\n");
    hSocket = socket(AF_INET, SOCK_STREAM, 0);
    return hSocket;
}

int socketConnect(int hSocket) {
    int iRetval = -1;
    int ServerPort = 12112;

    struct sockaddr_in remote= {0};
    remote.sin_addr.s_addr = inet_addr("127.0.0.1");
    remote.sin_family = AF_INET;
    remote.sin_port = htons(ServerPort);

     iRetval = connect(hSocket, (struct sockaddr *)&remote, sizeof(struct sockaddr_in));
     return iRetval;
}

int socketSend(int hSocket, char* Rqst, short lenRqst) {
    int shortRetval = -1;
    struct timeval tv;
    tv.tv_sec = 20;
    tv.tv_usec = 0;

    if (setsockopt(hSocket, SOL_SOCKET, SO_SNDTIMEO, (char *)&tv,sizeof(tv)) < 0) {
        printf("Time Out\n");
        return -1;
    }

    shortRetval = send(hSocket, Rqst, lenRqst, 0);
    return shortRetval;
}


int socketReceive(int hSocket, char* Rsp,short RvcSize) {
    int shortRetval = -1;
    struct timeval tv;
    tv.tv_sec = 20;
    tv.tv_usec = 0;

    if (setsockopt(hSocket, SOL_SOCKET, SO_RCVTIMEO, (char *) &tv, sizeof(tv)) < 0) {
        printf("Timed Out");
        return -1;
    }

    shortRetval = recv(hSocket, Rsp, RvcSize, 0);
    printf("Reponse %s\n", Rsp);
    return shortRetval;
}

int main(int argc, char *argv[]) {
    int hSocket = 0, read_size = 0;
    char server_reply[200] = {0};

    hSocket = socketCreate();

    if (hSocket == -1) {
        printf("Error Creating Socket");
        return 1;
    }

    printf("Socket Created Successfully");

    if (socketConnect(hSocket) < 0) {
        perror("Connection Failed.\n");
        return 1;
    }

    printf("Connection with server successfully established");

    read_size = socketReceive(hSocket, server_reply, 200);
    printf("Server Response : %s: read_size %d\n\n", server_reply, read_size);
    close(hSocket);
    return 0;
}

