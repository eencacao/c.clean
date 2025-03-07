#ifndef IN_MEMORY_USER_REPOSITORY_H
#define IN_MEMORY_USER_REPOSITORY_H

#include "../interfaces/user_repository.h"

typedef struct
{
    UserRepository base;
    User users[10];
    int count;
} InMemoryUserRepository;

void in_memory_user_repository_init(InMemoryUserRepository *repository);

#endif