/**
 * @file globals.h
 * @brief Declaraciones de variables globales y definiciones de constantes
 *
 * Este archivo contiene las declaraciones de variables globales y definiciones
 * de constantes utilizadas en la shell, como IDs de procesos y configuraciones
 * de terminal.
 */

#ifndef GLOBALS_H
#define GLOBALS_H

#include <sys/types.h>
#include <termios.h>

// Variables globales relacionadas con los procesos y el estado de la shell
/**
 * @brief PID del proceso que se ejecuta en primer plano.
 */
extern pid_t foreground_pid;

/**
 * @brief PID del proceso suspendido en primer plano.
 */
extern pid_t foreground_suspended;

/**
 * @brief Grupo de procesos de la shell.
 */
extern pid_t shell_pgid;

/**
 * @brief Configuración de modo de terminal de la shell.
 */
extern struct termios shell_tmodes;

/**
 * @brief Indica si el modo de prueba está activado.
 */
extern int testing_mode;

// Definiciones de constantes
/**
 * @brief Número máximo de argumentos permitidos.
 */
#define MAX_ARGS 100

/**
 * @brief Número máximo de comandos en una pipeline.
 */
#define MAX_PIPELINE 10

/**
 * @brief Tamaño máximo para el buffer de salida.
 */
#define MAX_BUFFER_SIZE 1024

/**
 * @brief Tamaño máximo para el nombre de host.
 */
#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

/**
 * @brief Tamaño máximo para la ruta de directorio.
 */
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

/**
 * @brief Tamaño máximo de la entrada del usuario.
 */
#define MY_MAX_INPUT 1024

#endif // GLOBALS_H
