// test/src/test_malloc.c

#include "unity.h"
#include "memory.h"
#include "test_malloc.h"
#include <stdio.h> // Para printf

void test_malloc_simple(void) {
    printf("test_malloc_simple: Iniciando prueba\n");
    void *ptr1 = my_malloc(50);
    TEST_ASSERT_NOT_NULL(ptr1);
    printf("test_malloc_simple: Asignado ptr1 en %p\n", ptr1);

    void *ptr2 = my_malloc(100);
    TEST_ASSERT_NOT_NULL(ptr2);
    printf("test_malloc_simple: Asignado ptr2 en %p\n", ptr2);

    // Liberar los punteros para limpiar
    my_free(ptr1);
    my_free(ptr2);
    printf("test_malloc_simple: Liberados ptr1 y ptr2\n");
}
