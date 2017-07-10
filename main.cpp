#include <iostream>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <strings.h>

const int EPOLL_SIZE = 1 << 20;
static sockaddr_in server;
static sockaddr_in client;
static socklen_t len;
static int sock_fd;
static int epoll_fd;
//static int listen_fd;
static int nfds;

const char IP_ADDRESS[] = "127.0.0.1";

typedef void (*ctl_ev)(int epoll_fd, int fd, int state);

void set_non_blocking(int sock) {
    int opts;
    opts = fcntl(sock, F_GETFL);

    if (opts < 0) {
        perror("fcntl(sock, GETFL)");
        exit(1);
    }

    opts = opts | O_NONBLOCK;

    if (fcntl(sock, F_SETFL, opts) < 0) {
        perror("fcntl(sock, SETFL, opts)");
        exit(1);
    }
}

int main() {
    epoll_event ev, events[20];
    epoll_fd = epoll_create(EPOLL_SIZE);

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    set_non_blocking(sock_fd);


    ev.data.fd = sock_fd;
    ev.events = EPOLLIN | EPOLLET;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sock_fd, &ev);

    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    inet_aton(IP_ADDRESS, &(server.sin_addr));
    server.sin_port = htons(12345);
//    server.sin_addr.s_addr = INADDR_ANY;
    bind(sock_fd, (sockaddr *) &server, sizeof(server));


    /**
     *
     */


    printf("epoll_fd %d\n", epoll_fd);

    listen(sock_fd, 5);
    for (;;) {
        nfds = epoll_wait(epoll_fd, events, 20, 500);
        if (nfds) {
            printf("nfds %d", nfds);
        }
        for (int i = 0; i < nfds; ++i) {
            epoll_event *event = &events[i];
            if (event->data.fd == sock_fd) {

            } else if (event->events & EPOLLIN) {

            } else if (event->events & EPOLLOUT) {

            }
        }
    }

    close(sock_fd);
    return 0;
}