#include "unity.h"
#include "memory.h"
#include "test_worst_fit.h"
#include <stdio.h>

static void setUp_worst_fit(void) {
    initialize_logger("memory_log.txt");
    malloc_control(WORST_FIT); // Configuramos la política WORST_FIT
}

static void tearDown_worst_fit(void) {
    finalize_logger();
}

void test_worst_fit_allocation(void) {
    setUp_worst_fit();

    // Paso 1: Asignar bloques de diferentes tamaños
    void *ptr1 = my_malloc(100); // Bloque de 100 bytes
    TEST_ASSERT_NOT_NULL(ptr1);
    printf("ptr1 asignado en: %p\n", ptr1);

    void *ptr2 = my_malloc(300); // Bloque de 300 bytes
    TEST_ASSERT_NOT_NULL(ptr2);
    printf("ptr2 asignado en: %p\n", ptr2);

    void *ptr3 = my_malloc(200); // Bloque de 200 bytes
    TEST_ASSERT_NOT_NULL(ptr3);
    printf("ptr3 asignado en: %p\n", ptr3);

    void *ptr4 = my_malloc(150); // Bloque de 150 bytes
    TEST_ASSERT_NOT_NULL(ptr4);
    printf("ptr4 asignado en: %p\n", ptr4);

    // Paso 2: Liberar bloques intermedios
    my_free(ptr2); // Liberamos el bloque de 300 bytes
    printf("ptr2 (300 bytes) liberado.\n");

    my_free(ptr4); // Liberamos el bloque de 150 bytes
    printf("ptr4 (150 bytes) liberado.\n");

    // Mostrar el estado del heap antes de la asignación
    debug_heap();

    // Paso 3: Asignar un bloque que debería utilizar el más grande disponible
    void *ptr5 = my_malloc(250); // Bloque de 250 bytes
    TEST_ASSERT_NOT_NULL(ptr5);
    printf("ptr5 asignado en: %p\n", ptr5);

    // Paso 4: Validar que WORST_FIT seleccionó el bloque más grande
    t_block selected_block = get_block(ptr5);
    TEST_ASSERT_NOT_NULL(selected_block);

    // Validar que el bloque asignado tiene el tamaño adecuado
    TEST_ASSERT(selected_block->size >= 250); // Debe tener al menos el tamaño solicitado
    printf("El bloque asignado por WORST_FIT tiene un tamaño de: %zu bytes\n", selected_block->size);

    // Validar que el tamaño asignado es consistente con la lógica de división
    TEST_ASSERT(selected_block->size == 256); // Ajustado por BLOCK_SIZE o alineación
    printf("El bloque fue asignado y ajustado correctamente: tamaño = %zu\n", selected_block->size);

    // Paso 5: Liberar todos los bloques
    my_free(ptr1);
    my_free(ptr3);
    my_free(ptr5);
    printf("Todos los bloques liberados correctamente.\n");

    // Mostrar el estado final del heap
    debug_heap();

    tearDown_worst_fit();
}