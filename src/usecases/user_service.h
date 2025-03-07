#ifndef USER_SERVICE_H
#define USER_SERVICE_H

#include "../entities/user.h"
#include "../interfaces/user_repository.h"

typedef struct
{
    UserRepository *repository;
} UserService;

void user_service_init(UserService *service, UserRepository *repository);
void user_service_add_user(UserService *service, int id, const char *name);
User *user_service_get_user(UserService *service, int id);
void user_service_list_users(UserService *service);

#endif