#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "todo_handler.h"

void json_todo(char *buf, int sz, const Todo *t) {
    snprintf(buf, sz,
        "{\"id\":%d,\"title\":\"%s\","
        "\"completed\":%s,\"created_at\":\"%s\"}",
        t->id, t->title,
        t->completed ? "true" : "false",
        t->created_at);
}

char *parse_title(const char *body, char *out, int sz) {
    const char *p = strstr(body, "\"title\"");
    if (!p) { out[0] = '\0'; return out; }
    p = strchr(p + 7, '"');
    if (!p) { out[0] = '\0'; return out; }
    p++;
    const char *end = strchr(p, '"');
    if (!end) { out[0] = '\0'; return out; }
    int len = (int)(end - p);
    if (len >= sz) len = sz - 1;
    strncpy(out, p, len);
    out[len] = '\0';
    return out;
}

static void handle_get_all(TodoUseCase *uc, int fd) {
    char buf[RESP_SIZE];
    int pos = 0, count = 0;
    Todo *todos = uc_get_all(uc, &count);
    pos += snprintf(buf + pos, RESP_SIZE - pos, "[");
    for (int i = 0; i < count; i++) {
        char item[512];
        json_todo(item, sizeof(item), &todos[i]);
        if (i > 0)
            pos += snprintf(buf+pos, RESP_SIZE-pos, ",");
        pos += snprintf(buf + pos, RESP_SIZE-pos, "%s", item);
    }
    snprintf(buf + pos, RESP_SIZE - pos, "]");
    server_respond(fd, 200, buf);
}

static void handle_post(TodoUseCase *uc, HttpRequest *req) {
    char title[TITLE_LEN];
    parse_title(req->body, title, TITLE_LEN);
    if (title[0] == '\0') {
        server_respond(req->client_fd, 400,
                       "{\"error\":\"title required\"}");
        return;
    }
    char buf[RESP_SIZE];
    Todo *t = uc_create(uc, title);
    json_todo(buf, RESP_SIZE, t);
    server_respond(req->client_fd, 201, buf);
}

void handle_request(TodoUseCase *uc, HttpRequest *req) {
    int is_item = (int)strlen(req->path) > 7 &&
                  strncmp(req->path, "/todos/", 7) == 0;
    if (!is_item) {
        if (strcmp(req->method, "GET") == 0)
            handle_get_all(uc, req->client_fd);
        else if (strcmp(req->method, "POST") == 0)
            handle_post(uc, req);
        else
            server_respond(req->client_fd, 405,
                           "{\"error\":\"not allowed\"}");
    } else {
        int id = atoi(req->path + 7);
        handle_item(uc, req, id);
    }
}
