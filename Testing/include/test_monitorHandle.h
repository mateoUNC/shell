// Testing/include/test_monitorHandle.h
//
// Este archivo contiene las definiciones de funciones y variables globales para
// las pruebas relacionadas con el manejo del proceso de monitoreo en la shell.

#ifndef TEST_MONITORHANDLE_H
#define TEST_MONITORHANDLE_H

#include "globals.h"
#include <limits.h>
#include <setjmp.h>
#include <sys/types.h>

/**
 * @brief Prueba la función start_monitor para iniciar el proceso de monitoreo.
 *
 * Verifica que start_monitor cree correctamente el proceso de monitoreo, evite
 * la creación de procesos duplicados y maneje el PID del monitor de forma
 * adecuada.
 *
 * @param void No recibe parámetros.
 */
void test_start_monitor(void);

// Variables de control para los stubs
/**
 * @brief Valor de retorno simulado para fork en las pruebas de monitoreo.
 */
extern pid_t monitor_fork_return_value;

/**
 * @brief Valor de retorno simulado para execl en las pruebas de monitoreo.
 */
extern int monitor_execl_return_value;

/**
 * @brief Valor de retorno simulado para access en las pruebas de monitoreo.
 */
extern int monitor_access_return_value;

/**
 * @brief Valor de retorno simulado para get_executable_dir en las pruebas.
 */
extern int monitor_get_executable_dir_return_value;

/**
 * @brief Buffer simulado que almacena el directorio ejecutable en las pruebas.
 */
extern char monitor_get_executable_dir_buffer[PATH_MAX];

/**
 * @brief Almacena el path utilizado en la llamada a execl en las pruebas.
 */
extern char monitor_execl_called_with_path[PATH_MAX];

/**
 * @brief Almacena el primer argumento utilizado en la llamada a execl.
 */
extern char monitor_execl_called_with_arg[PATH_MAX];

// Variables para exit()
/**
 * @brief Indica si la función exit fue llamada en las pruebas.
 */
extern int exit_called;

/**
 * @brief Almacena el estado de salida utilizado en la llamada a exit.
 */
extern int exit_status;

/**
 * @brief Entorno de salto para simular el comportamiento de exit en las
 * pruebas.
 */
extern jmp_buf exit_env;

#endif // TEST_MONITORHANDLE_H
