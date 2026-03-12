#ifndef MEMORY_REPO_H
#define MEMORY_REPO_H

#include "interfaces/todo_repository.h"

typedef struct {
    TodoRepository base;
    Todo  items[MAX_TODOS];
    int   count;
    int   next_id;
} MemoryRepo;

Todo *repo_get_all(const TodoRepository *r, int *count);
Todo *repo_get_by_id(TodoRepository *r, int id);
Todo *repo_save(TodoRepository *r, const char *title);
void  memory_repo_init(MemoryRepo *repo);

#endif
