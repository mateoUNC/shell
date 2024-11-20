// Testing/include/test_utils.h
//
// Este archivo contiene las definiciones de variables y funciones de utilidad
// para las pruebas, incluyendo el manejo simulado de exit().

#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <setjmp.h>

/**
 * @brief Indica si la función exit fue llamada en una prueba.
 */
extern int exit_called;

/**
 * @brief Almacena el estado de salida proporcionado a la función exit.
 */
extern int exit_status;

/**
 * @brief Entorno de salto para simular el comportamiento de exit en las
 * pruebas.
 */
extern jmp_buf exit_env;

/**
 * @brief Simula el comportamiento de la función exit en las pruebas.
 *
 * Utiliza setjmp y longjmp para permitir que las pruebas continúen
 * después de una llamada a exit en el código bajo prueba.
 *
 * @param status El código de salida proporcionado a exit.
 */
void test_exit(int status);

#endif // TEST_UTILS_H
