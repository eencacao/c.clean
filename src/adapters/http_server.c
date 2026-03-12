#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "http_server.h"

int server_init(int port) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port   = htons(port),
        .sin_addr   = {.s_addr = INADDR_ANY}
    };
    bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(fd, 16);
    return fd;
}

static int parse_request(int fd, HttpRequest *req) {
    char buf[BUF_SIZE] = {0};
    int  n = recv(fd, buf, BUF_SIZE - 1, 0);
    if (n <= 0) return -1;
    sscanf(buf, "%7s %255s", req->method, req->path);
    char *body_start = strstr(buf, "\r\n\r\n");
    if (body_start) {
        body_start += 4;
        strncpy(req->body, body_start, BUF_SIZE - 1);
    }
    return 0;
}

int server_accept(int server_fd, HttpRequest *req) {
    int fd = accept(server_fd, NULL, NULL);
    if (fd < 0) return -1;
    req->client_fd = fd;
    return parse_request(fd, req);
}
