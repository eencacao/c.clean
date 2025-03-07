#include "in_memory_user_repository.h"
#include <stdio.h>
#include <string.h>

void add_user_impl(UserRepository *repo, User *user)
{
    InMemoryUserRepository *self = (InMemoryUserRepository *)repo;
    if (self->count < 10)
    {
        self->users[self->count++] = *user;
    }
}

User *get_user_impl(UserRepository *repo, int id)
{
    InMemoryUserRepository *self = (InMemoryUserRepository *)repo;
    for (int i = 0; i < self->count; i++)
    {
        if (self->users[i].id == id)
        {
            return &self->users[i];
        }
    }
    return NULL;
}

void list_users_impl(UserRepository *repo)
{
    InMemoryUserRepository *self = (InMemoryUserRepository *)repo;
    for (int i = 0; i < self->count; i++)
    {
        printf("ID: %d, Name: %s\n", self->users[i].id, self->users[i].name);
    }
}

void in_memory_user_repository_init(InMemoryUserRepository *repository)
{
    repository->count = 0;
    repository->base.add_user = add_user_impl;
    repository->base.get_user = get_user_impl;
    repository->base.list_users = list_users_impl;
}