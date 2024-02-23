#include "unp.h"

static int MAX_LEN = 1024;

void* HandleAccept(void* arg)
{
    int conn_fd = *(int*)arg;
    char buffer[MAX_LEN];
    strncpy(buffer, "Connection success!\n", sizeof(buffer));
    Send(conn_fd, buffer, strlen(buffer)+1, 0);
    close(conn_fd);
}

int main(int argc, char* argv[])
{
    if (argc != 2)
        err_quit("Usage: ./server <port>");
    
    // 1. Create socket fd
    int sockfd = Socket(AF_INET, SOCK_STREAM, 0);

    // 2. Bind address
    struct sockaddr_in sockaddr;
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(atoi(argv[1]));
    sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    Bind(sockfd, (SA*)(&sockaddr), sizeof(SA));

    // 3. Listen
    Listen(sockfd, 5);

    // 4. Accept
    for (; ;) {
        struct sockaddr_in recv_sockaddr;
        socklen_t sock_len = sizeof(SA);
        int conn_fd = Accept(sockfd, (SA*)(&recv_sockaddr), &sock_len);

        char recv_buf[MAX_LEN];
        inet_ntop(AF_INET, &(recv_sockaddr.sin_addr.s_addr), recv_buf, MAX_LEN);
        printf("Recv connection from %s:%d\n", recv_buf, recv_sockaddr.sin_port);

        pthread_t tid;
        if (0 != pthread_create(&tid, NULL, HandleAccept, &conn_fd))
            err_quit("Create new thread failed. ");
        
        pthread_join(tid, NULL);
    }

    // 5. Close sockfd
    close(sockfd);
    return 0;
}