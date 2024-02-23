
//Use epoll implement Server

#include "unp.h"
#include <sys/epoll.h>

static int MAX_LEN = 1024;
static int OPEN_MAX = 1024;

int main(int argc, char* argv[])
{
    if (argc != 2)
        err_quit("Usage: ./server <port>");
    
    // 1. Create socket fd
    int listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    // 1.1 Set nonblocking
    int flags = fcntl(listenfd, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(listenfd, F_SETFL, flags);

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

    int nready, conn_fd, nbytes;
    int maxi = 0;
    int buffer[MAX_LEN];

    int epollfd = epoll_create(1);
    if (-1 == epollfd) {
        err_quit("epoll_create failed.");
    }

    struct epoll_event event;
    event.events = EPOLLET | EPOLLIN;
    event.data.fd = listenfd;

    if (-1 == epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &event)) {
        Close(epollfd); //must do!
        err_quit("epoll_ctl failed.");
    }

    // 4. Accept
    for (; ;) {
        struct sockaddr_in recv_sockaddr;
        bzero(&recv_sockaddr, sizeof(recv_sockaddr));
        socklen_t sock_len = sizeof(SA);

        struct epoll_event revents[MAX_LEN];
        if ((nready = epoll_wait(epollfd, revents, MAX_LEN, -1)) == -1) {
            Close(epollfd); //must do!
            err_quit("epoll_wait failed.");
        }
        printf("nready: %d\n", nready);
        
        for (int i = 0; i < nready; ++i) {
            if (revents[i].data.fd == listenfd && revents[i].events == EPOLLIN) {
                conn_fd = Accept(listenfd, (SA*)&recv_sockaddr, &sock_len);

                // set nonblocking
                int flags = fcntl(listenfd, F_GETFL);
                flags |= O_NONBLOCK;
                fcntl(listenfd, F_SETFL, flags);

                struct epoll_event event;
                event.events = EPOLLET | EPOLLIN;
                event.data.fd = conn_fd;

                if (-1 == epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_fd, &event)) {
                    err_quit("epoll_ctl failed.");
                }
                if (--nready <= 0)
                    break;
            }

            if (revents[i].events == EPOLLIN) {
                conn_fd = revents[i].data.fd;
                if ((nbytes = Read(conn_fd, buffer, MAX_LEN)) < 0) {
                    if (errno == ECONNRESET) {
                        Close(conn_fd);
                    } else {
                        err_quit("read error");
                    }
                } else if (nbytes == 0) {
                    Close(conn_fd);
                } else {
                    Writen(conn_fd, buffer, nbytes);
                }
                if (--nready <= 0)
                    break;
            }
        }
    }
        //Close(epollfd);

    return 0;
}