#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "../src/infrastructure/memory_repo.h"
#include "../src/usecases/todo_usecase.h"

MemoryRepo  g_repo;
TodoUseCase g_uc;

void setup(void)
{
    memory_repo_init(&g_repo);
    uc_init(&g_uc, (TodoRepository *)&g_repo);
}

void test_create(void)
{
    setup();
    Todo *t = uc_create(&g_uc, "buy milk");
    assert(t != NULL);
    assert(t->id == 1);
    assert(strcmp(t->title, "buy milk") == 0);
    assert(t->completed == 0);
    printf("PASS test_create\n");
}

void test_get_all(void)
{
    setup();
    int count = 0;
    uc_get_all(&g_uc, &count);
    assert(count == 0);
    uc_create(&g_uc, "a");
    uc_create(&g_uc, "b");
    uc_get_all(&g_uc, &count);
    assert(count == 2);
    printf("PASS test_get_all\n");
}

void test_get_by_id(void)
{
    setup();
    uc_create(&g_uc, "find me");
    Todo *t = uc_get_by_id(&g_uc, 1);
    assert(t != NULL);
    assert(strcmp(t->title, "find me") == 0);
    assert(uc_get_by_id(&g_uc, 99) == NULL);
    printf("PASS test_get_by_id\n");
}

void test_update(void)
{
    setup();
    uc_create(&g_uc, "old");
    Todo *t = uc_update(&g_uc, 1, "new", 1);
    assert(t != NULL);
    assert(strcmp(t->title, "new") == 0);
    assert(t->completed == 1);
    assert(uc_update(&g_uc, 99, "x", 0) == NULL);
    printf("PASS test_update\n");
}
