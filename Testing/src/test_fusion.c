// test/src/test_fusion.c

#include "unity.h"
#include "memory.h"
#include "test_fusion.h"
#include <stdio.h> // Para printf

// Función que se ejecuta antes de cada prueba
static void setUp_fusion(void) {
    if (initialize_logger("memory_log.txt") != 0) {
        printf("Failed to initialize logger in setUp_fusion.\n");
    }
    malloc_control(FIRST_FIT);
}

static void tearDown_fusion(void) {
    finalize_logger();
}

// Prueba que verifica que los bloques se fusionan correctamente al liberar
void test_fusion_of_adjacent_blocks(void) {
    // Paso 1: Asignar múltiples bloques
    void *ptr1 = my_malloc(32);
    TEST_ASSERT_NOT_NULL(ptr1);
    void *ptr2 = my_malloc(64);
    TEST_ASSERT_NOT_NULL(ptr2);
    void *ptr3 = my_malloc(128);
    TEST_ASSERT_NOT_NULL(ptr3);

    // Paso 2: Liberar el segundo bloque y verificar
    printf("Liberando ptr2 (64 bytes)...\n");
    my_free(ptr2);
    t_block block2 = get_block(ptr2);
    TEST_ASSERT_NOT_NULL(block2);
    TEST_ASSERT(block2->free == 1);

    // Paso 3: Liberar el primer bloque y verificar fusión
    printf("Liberando ptr1 (32 bytes)...\n");
    my_free(ptr1);
    t_block block1 = get_block(ptr1);
    TEST_ASSERT_NOT_NULL(block1);
    TEST_ASSERT(block1->free == 1);
    // Verificar que el bloque 1 y 2 se han fusionado
    size_t expected_size1 = 32 + 64 + sizeof(struct s_block);
    TEST_ASSERT(block1->size >= expected_size1);

    // Paso 4: Liberar el tercer bloque y verificar fusión completa
    printf("Liberando ptr3 (128 bytes)...\n");
    my_free(ptr3);
    block1 = get_block(ptr1);

    TEST_ASSERT_NOT_NULL(block1);

    TEST_ASSERT(block1->free == 1);
    // Verificar que todos los bloques se han fusionado
    size_t expected_size2 = 32+64 + 128 + 2*sizeof(struct s_block);
    TEST_ASSERT(block1->size >= expected_size2);
}
