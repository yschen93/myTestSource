//Use select implement Client

#include "unp.h"

static int MAX_LEN = 1024;

void str_cli(FILE* fp, int sockfd)
{
    int maxfd;
    fd_set rset;
    char sendline[MAX_LEN], recvline[MAX_LEN];

    maxfd = max(fileno(fp), sockfd) + 1;

    for (; ;) {
        FD_ZERO(&rset);
        FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);

        Select(maxfd, &rset, NULL, NULL, NULL);

        // Process socket stream
        if (FD_ISSET(sockfd, &rset)) {
            if (Readline(sockfd, recvline, MAX_LEN) == 0)
                err_quit("str_cli: server terminated prematuraly");
            Fputs(recvline, stdout);
        }

        // Process input
        if (FD_ISSET(fileno(fp), &rset)) {
            if (Fgets(sendline, MAX_LEN, fp) == NULL) //fgets will append null byte automatically
                break;
            Writen(sockfd, sendline, strlen(sendline));
        }
    }
}

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

    str_cli(stdin, sockfd);

    Close(sockfd);
    
    return 0;
}