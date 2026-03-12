#ifndef TODO_REPOSITORY_H
#define TODO_REPOSITORY_H

#include "entities/todo.h"

typedef struct TodoRepository {
    Todo *(*get_all)(const struct TodoRepository *, int *count);
    Todo *(*get_by_id)(struct TodoRepository *, int id);
    Todo *(*save)(struct TodoRepository *, const char *title);
    Todo *(*update)(struct TodoRepository *, int,
                    const char *, int);
    int   (*delete)(struct TodoRepository *, int id);
} TodoRepository;

#endif
