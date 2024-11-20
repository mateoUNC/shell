// Testing/src/test_mocks.c
//
// Este archivo contiene implementaciones de mocks para las funciones de sistema
// que son usadas en las pruebas unitarias de la shell. Estas implementaciones
// permiten verificar llamadas y capturar datos en lugar de ejecutar la lógica
// real.

#include "test_mocks.h"
#include <stdarg.h>
#include <stdio.h> // Solo si necesitas llamar a __real_printf
#include <string.h>

// Variables para controlar los mocks
int kill_called = 0;
pid_t kill_pid = 0;
int kill_sig = 0;

int print_prompt_called = 0;

int printf_called = 0;
char printf_buffer[1024] = {0};

int fflush_called = 0;
FILE *fflush_stream = NULL;

int tcsetpgrp_called = 0;
int tcsetpgrp_fd = 0;
pid_t tcsetpgrp_pgrp = 0;

// Buffer global para almacenar las salidas de printf
#define MAX_PRINTF_BUFFER 1024
char printf_buffer[MAX_PRINTF_BUFFER];
size_t printf_buffer_pos = 0;

/**
 * @brief Mock de la función kill.
 *
 * Simula la función kill, almacenando los parámetros pid y sig para verificar
 * su llamada y configuración en los tests.
 *
 * @param pid El ID del proceso al que enviar la señal.
 * @param sig La señal a enviar al proceso.
 * @return int Retorna 0 simulando éxito.
 */
int kill(pid_t pid, int sig) {
  kill_called = 1;
  kill_pid = pid;
  kill_sig = sig;
  return 0; // Simular éxito
}

/**
 * @brief Implementación de __wrap_printf para capturar llamadas a printf.
 *
 * Intercepta y almacena la salida de printf en un buffer para verificarla en
 * los tests.
 *
 * @param format Cadena de formato de printf.
 * @param ... Lista de argumentos variable para el formato.
 * @return int La cantidad de caracteres escritos.
 */
int __wrap_printf(const char *format, ...) {
  printf_called = 1; // Marcar que se llamó a printf

  va_list args;
  va_start(args, format);

  // Capturar la salida en printf_buffer y verificar el límite del buffer
  int written = vsnprintf(printf_buffer + printf_buffer_pos,
                          MAX_PRINTF_BUFFER - printf_buffer_pos, format, args);
  if (written > 0) {
    printf_buffer_pos += written;
  }
  va_end(args);

  // Forwarding: llamar a la función real printf (usando otra vez va_start)
  va_start(args, format);
  int ret = vprintf(format, args);
  va_end(args);

  return ret;
}

/**
 * @brief Limpia el buffer de printf antes de una nueva prueba.
 *
 * Resetea el contenido del buffer printf_buffer y la posición del mismo.
 *
 * @param void No recibe parámetros.
 */
void clear_printf_buffer() {
  printf_buffer[0] = '\0';
  printf_buffer_pos = 0;
}

/**
 * @brief Devuelve el contenido del buffer de printf para verificación en los
 * tests.
 *
 * @param void No recibe parámetros.
 * @return const char* Apuntador al contenido del buffer printf_buffer.
 */
const char *get_printf_buffer() { return printf_buffer; }

/**
 * @brief Mock de la función print_prompt.
 *
 * Indica que se llamó a print_prompt configurando una variable de control.
 *
 * @param void No recibe parámetros.
 */
void print_prompt(void) { print_prompt_called = 1; }

/**
 * @brief Mock de la función fflush.
 *
 * Simula la llamada a fflush, almacenando el stream en una variable de control.
 *
 * @param stream El flujo a vaciar.
 * @return int Retorna 0 simulando éxito.
 */
int fflush(FILE *stream) {
  fflush_called = 1;
  fflush_stream = stream;
  return 0; // Simular éxito
}

/**
 * @brief Mock de la función tcsetpgrp.
 *
 * Simula la llamada a tcsetpgrp, guardando los parámetros en variables de
 * control.
 *
 * @param fd El descriptor de archivo.
 * @param pgrp El ID del grupo de procesos a establecer.
 * @return int Retorna 0 simulando éxito.
 */
int tcsetpgrp(int fd, pid_t pgrp) {
  tcsetpgrp_called = 1;
  tcsetpgrp_fd = fd;
  tcsetpgrp_pgrp = pgrp;
  return 0; // Simular éxito
}
