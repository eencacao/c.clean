#ifndef TODO_USECASE_H
#define TODO_USECASE_H

#include "interfaces/todo_repository.h"

typedef struct {
    TodoRepository *repo;
} TodoUseCase;

void  uc_init(TodoUseCase *uc, TodoRepository *repo);
Todo *uc_get_all(TodoUseCase *uc, int *count);
Todo *uc_get_by_id(TodoUseCase *uc, int id);
Todo *uc_create(TodoUseCase *uc, const char *title);
Todo *uc_update(TodoUseCase *uc, int id,
                const char *title, int done);
int   uc_delete(TodoUseCase *uc, int id);

#endif
