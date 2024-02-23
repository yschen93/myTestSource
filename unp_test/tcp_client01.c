#include "unp.h"

int main(int argc, char* argv[])
{
    if (argc != 3)
        err_quit("usage: ./client <ip> <port>");
    
    // 1. Create socket fd
    int sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    // 2. Connect server
    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(argv[2]));
    sockaddr.sin_addr.s_addr = inet_addr(argv[1]);
    printf("Connect server: %s:%d\n", argv[1], atoi(argv[2]));

    Connect(sockfd, (SA*)(&sockaddr), sizeof(SA));

    // 3. Recv from peer
    char buffer[1024];
    Recv(sockfd, buffer, sizeof(buffer), 0);

    printf("Recv message: %s\n", buffer);
    
    return 0;
}