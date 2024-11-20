// Testing/include/test_mocks.h
//
// Este archivo contiene las declaraciones de variables y funciones mock para
// controlar el comportamiento de las funciones de sistema en las pruebas de la
// shell.

#ifndef TEST_MOCKS_H
#define TEST_MOCKS_H

#include <limits.h>
#include <setjmp.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

// Declaraciones de variables para controlar los mocks
/**
 * @brief Indica si la función kill fue llamada.
 */
extern int kill_called;

/**
 * @brief Almacena el pid utilizado en la llamada a kill.
 */
extern pid_t kill_pid;

/**
 * @brief Almacena la señal utilizada en la llamada a kill.
 */
extern int kill_sig;

/**
 * @brief Indica si la función print_prompt fue llamada.
 */
extern int print_prompt_called;

/**
 * @brief Indica si la función printf fue llamada.
 */
extern int printf_called;

/**
 * @brief Buffer para capturar la salida de printf.
 */
extern char printf_buffer[1024];

/**
 * @brief Indica si la función fflush fue llamada.
 */
extern int fflush_called;

/**
 * @brief Almacena el flujo utilizado en la llamada a fflush.
 */
extern FILE *fflush_stream;

/**
 * @brief Indica si la función tcsetpgrp fue llamada.
 */
extern int tcsetpgrp_called;

/**
 * @brief Almacena el descriptor de archivo utilizado en tcsetpgrp.
 */
extern int tcsetpgrp_fd;

/**
 * @brief Almacena el ID del grupo de procesos utilizado en tcsetpgrp.
 */
extern pid_t tcsetpgrp_pgrp;

// Declaraciones de funciones mockeadas

/**
 * @brief Mock de la función kill.
 *
 * @param pid El ID del proceso al que enviar la señal.
 * @param sig La señal a enviar al proceso.
 * @return int Retorna 0 simulando éxito.
 */
int kill(pid_t pid, int sig);

/**
 * @brief Mock de la función printf que captura la salida en un buffer.
 *
 * @param format Cadena de formato de printf.
 * @param ... Lista de argumentos variable para el formato.
 * @return int La cantidad de caracteres escritos.
 */
int printf(const char *format, ...);

/**
 * @brief Mock de la función print_prompt.
 *
 * Indica que se llamó a print_prompt configurando una variable de control.
 */
void print_prompt(void);

/**
 * @brief Mock de la función fflush.
 *
 * Simula la llamada a fflush, almacenando el stream en una variable de control.
 *
 * @param stream El flujo a vaciar.
 * @return int Retorna 0 simulando éxito.
 */
int fflush(FILE *stream);

/**
 * @brief Mock de la función tcsetpgrp.
 *
 * Simula la llamada a tcsetpgrp, guardando los parámetros en variables de
 * control.
 *
 * @param fd Descriptor de archivo.
 * @param pgrp ID del grupo de procesos a establecer.
 * @return int Retorna 0 simulando éxito.
 */
int tcsetpgrp(int fd, pid_t pgrp);

/**
 * @brief Limpia el buffer de printf antes de una nueva prueba.
 *
 * Resetea el contenido del buffer printf_buffer y la posición del mismo.
 *
 * @param void No recibe parámetros.
 */
void clear_printf_buffer(void);

/**
 * @brief Devuelve el contenido del buffer de printf para verificación en los
 * tests.
 *
 * @param void No recibe parámetros.
 * @return const char* Apuntador al contenido del buffer printf_buffer.
 */
const char *get_printf_buffer(void);

#endif // TEST_MOCKS_H
