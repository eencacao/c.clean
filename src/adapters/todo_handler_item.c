#include <string.h>
#include "todo_handler.h"

static void handle_get_one(TodoUseCase *uc,
                           const HttpRequest *req, int id) {
    const Todo *t = uc_get_by_id(uc, id);
    if (!t) {
        server_respond(req->client_fd, 404,
                       "{\"error\":\"not found\"}");
        return;
    }
    char buf[RESP_SIZE];
    json_todo(buf, RESP_SIZE, t);
    server_respond(req->client_fd, 200, buf);
}

static void handle_put(TodoUseCase *uc,
                       const HttpRequest *req, int id) {
    char title[TITLE_LEN];
    parse_title(req->body, title, TITLE_LEN);
    int done = strstr(req->body, "\"completed\":true") != NULL;
    const Todo *t = uc_update(uc, id, title, done);
    if (!t) {
        server_respond(req->client_fd, 404,
                       "{\"error\":\"not found\"}");
        return;
    }
    char buf[RESP_SIZE];
    json_todo(buf, RESP_SIZE, t);
    server_respond(req->client_fd, 200, buf);
}

static void handle_delete(TodoUseCase *uc,
                          const HttpRequest *req, int id) {
    if (!uc_delete(uc, id)) {
        server_respond(req->client_fd, 404,
                       "{\"error\":\"not found\"}");
        return;
    }
    server_respond_empty(req->client_fd, 204);
}

void handle_item(TodoUseCase *uc, const HttpRequest *req, int id) {
    if (strcmp(req->method, "GET") == 0)
        handle_get_one(uc, req, id);
    else if (strcmp(req->method, "PUT") == 0)
        handle_put(uc, req, id);
    else if (strcmp(req->method, "DELETE") == 0)
        handle_delete(uc, req, id);
    else
        server_respond(req->client_fd, 405,
                       "{\"error\":\"not allowed\"}");
}
