
//Use Poll implement Server

#include "unp.h"

static int MAX_LEN = 1024;
static int OPEN_MAX = 1024;

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

    struct pollfd clients[OPEN_MAX];
    clients[0].fd = listenfd;
    clients[0].events = POLLRDNORM;
    for (int i = 1; i < OPEN_MAX; ++i) {
        clients[i].fd = -1;
    }

    int nready, conn_fd, nbytes;
    int maxi = 0;
    int buffer[MAX_LEN];

    // 4. Accept
    for (; ;) {
        struct sockaddr_in recv_sockaddr;
        bzero(&recv_sockaddr, sizeof(recv_sockaddr));
        socklen_t sock_len = sizeof(SA);


        nready = Poll(clients, maxi + 1, INFTIM);
        printf("nready: %d\n", nready);
        
        if (clients[0].revents & POLLRDNORM) {
            conn_fd = Accept(listenfd, (SA*)&recv_sockaddr, &sock_len);
            int i;
            for (i = 1; i < OPEN_MAX; ++i) {
                if (clients[i].fd == -1) {
                    clients[i].fd = conn_fd;
                    printf("clients[%d].fd = %d\n", i, conn_fd);
                    clients[i].events = POLLRDNORM;
                    if (i > maxi) maxi = i;
                    break;
                }
            }
            if (i == OPEN_MAX)
                err_quit("too many clients");
            if (--nready <= 0)
                continue;
        }

        for (int i = 1; i <= maxi; ++i) {
            if (clients[i].fd == -1)
                continue;
            if (clients[i].revents & (POLLRDNORM | POLLERR)) {
                if ((nbytes = Read(clients[i].fd, buffer, MAX_LEN)) < 0) {
                    if (errno == ECONNRESET) {
                        Close(clients[i].fd);
                        clients[i].fd = -1;
                    } else {
                        err_quit("read error");
                    }
                } else if (nbytes == 0) {
                    Close(clients[i].fd);
                    clients[i].fd = -1;
                } else {
                    Writen(clients[i].fd, buffer, nbytes);
                }

                if (--nready <= 0)
                    break;
            }
        }
    }

    return 0;
}