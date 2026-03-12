#include <assert.h>
#include <stdio.h>
#include "../src/infrastructure/memory_repo.h"
#include "../src/usecases/todo_usecase.h"

extern MemoryRepo  g_repo;
extern TodoUseCase g_uc;
extern void setup(void);
extern void test_create(void);
extern void test_get_all(void);
extern void test_get_by_id(void);
extern void test_update(void);

static void test_delete(void)
{
    setup();
    uc_create(&g_uc, "bye");
    assert(uc_delete(&g_uc, 1) == 1);
    assert(uc_delete(&g_uc, 1) == 0);
    printf("PASS test_delete\n");
}

int main(void)
{
    printf("=== Unit Tests ===\n");
    test_create();
    test_get_all();
    test_get_by_id();
    test_update();
    test_delete();
    printf("All unit tests passed.\n");
    return 0;
}
