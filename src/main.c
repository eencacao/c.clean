#include <stdio.h>
#include "infrastructure/memory_repo.h"
#include "usecases/todo_usecase.h"
#include "adapters/http_server.h"
#include "adapters/todo_handler.h"

int main(void) {
    MemoryRepo  repo;
    TodoUseCase uc;
    HttpRequest req;
    int         server_fd;
    memory_repo_init(&repo);
    uc_init(&uc, (TodoRepository *)&repo);
    server_fd = server_init(8080);
    printf("Listening on :8080\n");
    while (server_accept(server_fd, &req) == 0)
        handle_request(&uc, &req);
    return 0;
}
