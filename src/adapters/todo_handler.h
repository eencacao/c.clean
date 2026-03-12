#ifndef TODO_HANDLER_H
#define TODO_HANDLER_H

#include "http_server.h"
#include "usecases/todo_usecase.h"

void  json_todo(char *buf, int sz, const Todo *t);
char *parse_title(const char *body, char *out, int sz);
void  handle_item(TodoUseCase *uc, HttpRequest *req, int id);
void  handle_request(TodoUseCase *uc, HttpRequest *req);

#endif
