#include <string.h>
#include "memory_repo.h"

static Todo *repo_update(TodoRepository *r, int id,
                         const char *title, int done) {
    MemoryRepo *mr = (MemoryRepo *)r;
    for (int i = 0; i < mr->count; i++) {
        if (mr->items[i].id == id) {
            strncpy(mr->items[i].title, title, TITLE_LEN - 1);
            mr->items[i].title[TITLE_LEN - 1] = '\0';
            mr->items[i].completed = done;
            return &mr->items[i];
        }
    }
    return NULL;
}

static int repo_delete(TodoRepository *r, int id) {
    MemoryRepo *mr = (MemoryRepo *)r;
    for (int i = 0; i < mr->count; i++) {
        if (mr->items[i].id == id) {
            mr->items[i] = mr->items[--mr->count];
            return 1;
        }
    }
    return 0;
}

void memory_repo_init(MemoryRepo *repo) {
    memset(repo, 0, sizeof(*repo));
    repo->next_id        = 1;
    repo->base.get_all   = repo_get_all;
    repo->base.get_by_id = repo_get_by_id;
    repo->base.save      = repo_save;
    repo->base.update    = repo_update;
    repo->base.delete    = repo_delete;
}
