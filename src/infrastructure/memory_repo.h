#ifndef MEMORY_REPO_H
#define MEMORY_REPO_H

#include "interfaces/todo_repository.h"

typedef struct {
    TodoRepository base;
    Todo  items[MAX_TODOS];
    int   count;
    int   next_id;
} MemoryRepo;

Todo *repo_get_all(TodoRepository *r, int *count);
Todo *repo_get_by_id(TodoRepository *r, int id);
Todo *repo_save(TodoRepository *r, const char *title);
Todo *repo_update(TodoRepository *r, int id,
                  const char *title, int done);
int   repo_delete(TodoRepository *r, int id);
void  memory_repo_init(MemoryRepo *repo);

#endif
