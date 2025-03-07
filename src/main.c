#include <stdio.h>
#include "infrastructure/in_memory_user_repository.h"
#include "usecases/user_service.h"

int main()
{
    InMemoryUserRepository repository;
    in_memory_user_repository_init(&repository);

    UserService service;
    user_service_init(&service, (UserRepository *)&repository);

    user_service_add_user(&service, 1, "Alice");
    user_service_add_user(&service, 2, "Bob");

    printf("User List:\n");
    user_service_list_users(&service);

    User *user = user_service_get_user(&service, 1);
    if (user)
    {
        printf("\nFetched User: ID=%d, Name=%s\n", user->id, user->name);
    }
    else
    {
        printf("\nUser not found!\n");
    }

    return 0;
}