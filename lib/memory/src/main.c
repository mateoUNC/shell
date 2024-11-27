#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Inicializar el logger para registrar eventos
    if (initialize_logger("memory_log.txt") == -1) {
        return EXIT_FAILURE;
    }

    // Cambiar el método de asignación a Best Fit
    malloc_control(BEST_FIT);
    printf("Método de asignación cambiado a Best Fit\n");

    // Asignar y liberar bloques de memoria
    void *ptr1 = my_malloc(64);
    if (ptr1) {
        printf("Asignado bloque de 64 bytes en %p\n", ptr1);
        check_heap_extended();
    }

    void *ptr2 = my_malloc(128);
    if (ptr2) {
        printf("Asignado bloque de 128 bytes en %p\n", ptr2);
        check_heap_extended();
    }

    // Liberar un bloque para probar Best Fit
    if (ptr1) {
        my_free(ptr1);
        printf("Liberado bloque de 64 bytes en %p\n", ptr1);
        check_heap_extended();
        ptr1 = NULL; // Asegurarse de no usar ptr1 nuevamente
    }

    // Asignar un bloque más pequeño para ver si se reutiliza el espacio de 64 bytes
    void *ptr3 = my_malloc(32);
    if (ptr3) {
        printf("Asignado bloque de 32 bytes en %p (debería ocupar el bloque de 64 bytes liberado)\n", ptr3);
        check_heap_extended();
    }

    // Asignar otro bloque más grande
    void *ptr4 = my_malloc(48);
    if (ptr4) {
        printf("Asignado bloque de 48 bytes en %p\n", ptr4);
        check_heap_extended();
    }

    // Liberar todos los bloques restantes
    if (ptr2) {
        my_free(ptr2);
        printf("Liberado bloque de 128 bytes en %p\n", ptr2);
        ptr2 = NULL;
    }

    if (ptr3) {
        my_free(ptr3);
        printf("Liberado bloque de 32 bytes en %p\n", ptr3);
        ptr3 = NULL;
    }

    if (ptr4) {
        my_free(ptr4);
        printf("Liberado bloque de 48 bytes en %p\n", ptr4);
        ptr4 = NULL;
    }

    // Mostrar el estado del heap después de todas las operaciones
    check_heap_extended();

    // Finalizar el logger
    finalize_logger();

    return 0;
}
