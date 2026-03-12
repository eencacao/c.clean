#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#define BUF_SIZE  8192
#define RESP_SIZE 8192

typedef struct {
    char method[8];
    char path[256];
    char body[BUF_SIZE];
    int  client_fd;
} HttpRequest;

int  server_init(int port);
int  server_accept(int server_fd, HttpRequest *req);
void server_respond(int fd, int status, const char *body);
void server_respond_empty(int fd, int status);

#endif
