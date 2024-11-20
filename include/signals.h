/**
 * @file signals.h
 * @brief Declaración de funciones para el manejo de señales en la shell.
 *
 * Este archivo contiene las declaraciones de las funciones de manejo de
 * señales, permitiendo que la shell responda adecuadamente a interrupciones
 * (SIGINT) y señales de suspensión (SIGTSTP), así como a eventos de
 * finalización de procesos hijos (SIGCHLD).
 */

#ifndef SIGNALS_H
#define SIGNALS_H

#include <signal.h> // Necesario para struct sigaction

/**
 * @brief Manejador de señales para la shell.
 *
 * Controla las señales recibidas por la shell, como SIGINT y SIGTSTP, y
 * las envía al proceso en primer plano, si lo hay.
 *
 * @param sig La señal recibida (por ejemplo, SIGINT o SIGTSTP).
 */
void shell_signal_handler(int sig);

/**
 * @brief Manejador de la señal SIGCHLD para procesos hijos.
 *
 * Maneja la terminación o suspensión de procesos hijos, y muestra el estado
 * del proceso en segundo plano al usuario.
 *
 * @param sig La señal recibida (usualmente SIGCHLD).
 */
void sigchld_handler(int sig);

#endif // SIGNALS_H
