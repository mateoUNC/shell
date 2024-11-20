/**
 * @file commands.h
 * @brief Declaraciones de funciones relacionadas con la ejecución de comandos
 * en la shell
 *
 * Este archivo contiene las declaraciones de funciones relacionadas con la
 * ejecución de comandos en la shell, incluyendo redirección, ejecución en
 * segundo plano, y manejo de comandos internos.
 */

#ifndef COMMANDS_H
#define COMMANDS_H

#include "globals.h"
#include <stdbool.h>

/**
 * @brief Ejecuta un comando en la shell, manejando redirección, segundo plano,
 *        y comandos internos específicos.
 *
 * Permite redirigir entrada y salida, ejecutar comandos en segundo plano,
 * reanudar procesos suspendidos, y manejar comandos internos como `fg`, `cd`, y
 * `echo`.
 *
 * @param args Array de cadenas con los argumentos del comando.
 * @param running Puntero al estado de ejecución de la shell.
 */
void execute_command(char **args, int *running);

/**
 * @brief Cambia el directorio actual de trabajo al especificado en los
 * argumentos.
 *
 * Cambia el directorio de trabajo al directorio proporcionado en los argumentos
 * de la función.
 *
 * @param args Array de cadenas que contiene "cd" seguido del directorio de
 * destino.
 */
void change_directory(char **args);

/**
 * @brief Imprime los argumentos proporcionados al comando "echo", eliminando
 * comillas.
 *
 * Concatena y muestra los argumentos de "echo", eliminando comillas alrededor
 * de cada uno.
 *
 * @param args Array de cadenas que contiene "echo" seguido de los argumentos a
 * imprimir.
 */
void echo_command(char **args);

/**
 * @brief Obtiene el ID actual del trabajo para procesos en segundo plano.
 *
 * Retorna un identificador único de trabajo para los procesos en segundo plano.
 *
 * @return int El ID actual del trabajo.
 */
int get_current_job_id(void);

/**
 * @brief Redirige la entrada y salida estándar según los descriptores.
 *
 * Configura la redirección de entrada y salida estándar utilizando los
 * descriptores proporcionados para la ejecución de un comando.
 *
 * @param input_redirect Descriptor de archivo para redirección de entrada.
 * @param output_redirect Descriptor de archivo para redirección de salida.
 */
void handle_redirection(int input_redirect, int output_redirect);

/**
 * @brief Configura el proceso padre para manejar la ejecución en primer o
 * segundo plano.
 *
 * Configura el proceso padre para esperar o supervisar un proceso hijo
 * en función de si se está ejecutando en primer o segundo plano.
 *
 * @param pid El ID del proceso hijo.
 * @param background Indica si el proceso está en segundo plano (1 para segundo
 * plano).
 */
void handle_parent_process(pid_t pid, int background);

/**
 * @brief Restaura los manejadores de señales por defecto en el proceso hijo.
 *
 * Restablece los manejadores de señales SIGINT, SIGTSTP y SIGQUIT
 * a sus valores predeterminados en el proceso hijo.
 */
void reset_signal_handlers();

#endif // COMMANDS_H
