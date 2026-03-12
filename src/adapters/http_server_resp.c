#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include "http_server.h"

static const char *status_text(int code) {
    if (code == 200) return "OK";
    if (code == 201) return "Created";
    if (code == 204) return "No Content";
    if (code == 400) return "Bad Request";
    if (code == 404) return "Not Found";
    return "Internal Server Error";
}

void server_respond(int fd, int status, const char *body) {
    char resp[RESP_SIZE];
    int  blen = (int)strlen(body);
    int  n = snprintf(resp, RESP_SIZE,
        "HTTP/1.0 %d %s\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %d\r\n\r\n%s",
        status, status_text(status), blen, body);
    send(fd, resp, n, 0);
    close(fd);
}

void server_respond_empty(int fd, int status) {
    char resp[128];
    int n = snprintf(resp, sizeof(resp),
        "HTTP/1.0 %d %s\r\n"
        "Content-Length: 0\r\n\r\n",
        status, status_text(status));
    send(fd, resp, n, 0);
    close(fd);
}
