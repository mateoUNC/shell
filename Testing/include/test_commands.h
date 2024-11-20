// Testing/include/test_commands.h
//
// Este archivo contiene las definiciones de funciones de prueba para los
// comandos de la shell, incluyendo pruebas para cambiar directorios, ejecución
// de comandos y manejo de salidas de echo.

#ifndef TEST_COMMANDS_H
#define TEST_COMMANDS_H

#include <setjmp.h>
#include <sys/types.h> // Para pid_t

/**
 * @brief Redirige stdout a un buffer temporal para capturar la salida en las
 * pruebas.
 *
 * @param void No recibe parámetros.
 */
void redirect_stdout(void);

/**
 * @brief Restaura stdout y lee el contenido redirigido en el buffer
 * proporcionado.
 *
 * @param buffer El buffer donde se almacenará la salida capturada.
 * @param size Tamaño máximo del buffer.
 */
void restore_stdout_and_read(char *buffer, size_t size);

/**
 * @brief Prueba la función change_directory.
 *
 * Verifica el cambio de directorio al directorio HOME.
 */
void test_change_directory(void);

/**
 * @brief Prueba la ejecución de un comando válido en execute_command.
 *
 * Verifica la correcta ejecución de un comando como "ls -l".
 */
void test_execute_command_valid(void);

/**
 * @brief Prueba la ejecución de un comando inválido en execute_command.
 *
 * Verifica el manejo de errores para un comando inexistente.
 */
void test_execute_command_invalid(void);

/**
 * @brief Prueba la función echo_command sin argumentos.
 *
 * Verifica que echo_command maneje correctamente la falta de argumentos.
 */
void test_echo_command_no_args(void);

/**
 * @brief Prueba la función echo_command con un solo argumento.
 *
 * Verifica que un solo argumento se imprima correctamente.
 */
void test_echo_command_single_arg(void);

/**
 * @brief Prueba la función echo_command con argumentos entre comillas.
 *
 * Verifica que los argumentos en comillas se impriman sin ellas.
 */
void test_echo_command_args_with_quotes(void);

/**
 * @brief Prueba la función echo_command con una mezcla de argumentos con y sin
 * comillas.
 *
 * Verifica el manejo de diferentes tipos de argumentos en una misma llamada.
 */
void test_echo_command_mixed_args(void);

/**
 * @brief Prueba el manejo de un buffer excedido en echo_command.
 *
 * Verifica que se muestre un mensaje de error cuando los argumentos superan
 * el tamaño máximo del buffer.
 */
void test_echo_command_exceed_buffer(void);

/**
 * @brief Prueba la ejecución de un comando en segundo plano en execute_command.
 *
 * Verifica que el comando se ejecute en segundo plano cuando se usa "&".
 */
void test_execute_command_background(void);

/**
 * @brief Prueba el mock de printf para capturar y verificar la salida.
 */
void test_printf_mock(void);

// Declaración de variables globales para los stubs
extern pid_t fork_return_value;
extern int execvp_return_value;
extern pid_t waitpid_return_value;
extern int waitpid_status_value;

// Declaración de variables para exit()
extern int exit_called;
extern int exit_status;
extern jmp_buf exit_env;

#endif // TEST_COMMANDS_H
