#include <string.h>
#include <time.h>
#include "memory_repo.h"

static void set_time(char *buf) {
    time_t t = time(NULL);
    struct tm *tm = gmtime(&t);
    strftime(buf, DATE_LEN, "%Y-%m-%dT%H:%M:%SZ", tm);
}

Todo *repo_get_all(TodoRepository *r, int *count) {
    MemoryRepo *mr = (MemoryRepo *)r;
    *count = mr->count;
    return mr->items;
}

Todo *repo_get_by_id(TodoRepository *r, int id) {
    MemoryRepo *mr = (MemoryRepo *)r;
    for (int i = 0; i < mr->count; i++)
        if (mr->items[i].id == id)
            return &mr->items[i];
    return NULL;
}

Todo *repo_save(TodoRepository *r, const char *title) {
    MemoryRepo *mr = (MemoryRepo *)r;
    if (mr->count >= MAX_TODOS) return NULL;
    Todo *t = &mr->items[mr->count++];
    t->id = mr->next_id++;
    t->completed = 0;
    strncpy(t->title, title, TITLE_LEN - 1);
    t->title[TITLE_LEN - 1] = '\0';
    set_time(t->created_at);
    return t;
}
