#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include "../entities/user.h"

typedef struct UserRepository
{
    void (*add_user)(struct UserRepository *, User *);
    User *(*get_user)(struct UserRepository *, int);
    void (*list_users)(struct UserRepository *);
} UserRepository;

#endif