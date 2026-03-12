#include "todo_usecase.h"

Todo *uc_update(TodoUseCase *uc, int id,
                const char *title, int done) {
    return uc->repo->update(uc->repo, id, title, done);
}

int uc_delete(TodoUseCase *uc, int id) {
    return uc->repo->delete(uc->repo, id);
}
