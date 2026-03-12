#include "todo_usecase.h"

void uc_init(TodoUseCase *uc, TodoRepository *repo) {
    uc->repo = repo;
}

Todo *uc_get_all(TodoUseCase *uc, int *count) {
    return uc->repo->get_all(uc->repo, count);
}

Todo *uc_get_by_id(TodoUseCase *uc, int id) {
    return uc->repo->get_by_id(uc->repo, id);
}

Todo *uc_create(TodoUseCase *uc, const char *title) {
    return uc->repo->save(uc->repo, title);
}
