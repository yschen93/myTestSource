
//Use Slect implement Server

#include "unp.h"

static int MAX_LEN = 1024;

int main(int argc, char* argv[])
{
    if (argc != 2)
        err_quit("Usage: ./server <port>");
    
    // 1. Create socket fd
    int listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    // 2. Bind address
    struct sockaddr_in sockaddr;
    bzero(&sockaddr, sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(argv[1]));
    sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    Bind(listenfd, (SA*)(&sockaddr), sizeof(SA));

    // 3. Listen
    Listen(listenfd, LISTENQ);
    printf("listenfd: %d\n",listenfd);

    int nready, clients[FD_SETSIZE];

    int maxfd, maxi, conn_fd;

    maxfd = listenfd;
    maxi = -1;

    for (int i = 0; i < FD_SETSIZE; ++i) {
        clients[i] = -1;
    }

    fd_set allset, rset;
    FD_ZERO(&allset);
    FD_ZERO(&rset);

    FD_SET(listenfd, &allset);

    // 4. Accept
    for (; ;) {
        rset = allset;
        struct sockaddr_in recv_sockaddr;
        bzero(&recv_sockaddr, sizeof(recv_sockaddr));
        socklen_t sock_len = sizeof(SA);

        nready = Select(maxfd+1, &rset, NULL, NULL, NULL);
        printf("nready: %d\n", nready);
        if (FD_ISSET(listenfd, &rset)) {
            conn_fd = Accept(listenfd, (SA*)(&recv_sockaddr), &sock_len);

            if (conn_fd > maxfd) maxfd = conn_fd;

            for (int i = 0; i < FD_SETSIZE; ++i) {
                if (clients[i] == -1) {
                    clients[i] = conn_fd;
                    FD_SET(clients[i], &allset);
                    if (i > maxi) maxi = i;
                    break;
                }
            }
            if (--nready <= 0)
                continue;
        }

        char buffer[MAX_LEN];
        int nbytes;
        for (int i = 0; i <= maxi; ++i) {
            if (clients[i] != -1 && FD_ISSET(clients[i], &rset)) {
                if ((nbytes = Read(clients[i], buffer, MAX_LEN)) <= 0) {
                    Close(clients[i]);
                    FD_CLR(clients[i], &allset);
                    clients[i] = -1;
                } else {
                    Writen(clients[i], buffer, nbytes);
                }
            }
            if (--nready <= 0)
                break;
        }

        for (int i = 0; i <= maxi; ++i) {
            if (clients[i] != -1) {
                printf("index: [%d], fd: [%d]\n", i, clients[i]);
            }
        }
    }

    return 0;
}