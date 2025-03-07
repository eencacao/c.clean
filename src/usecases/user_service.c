#include "user_service.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void user_service_init(UserService *service, UserRepository *repository)
{
    service->repository = repository;
}

void user_service_add_user(UserService *service, int id, const char *name)
{
    User user;
    user.id = id;
    strncpy(user.name, name, sizeof(user.name));
    service->repository->add_user(service->repository, &user);
}

User *user_service_get_user(UserService *service, int id)
{
    return service->repository->get_user(service->repository, id);
}

void user_service_list_users(UserService *service)
{
    service->repository->list_users(service->repository);
}