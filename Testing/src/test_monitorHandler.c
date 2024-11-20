// Testing/src/test_monitorHandle.c
//
// Este archivo contiene las pruebas unitarias para el manejo de procesos de
// monitoreo en la shell. Incluye mocks específicos para las funciones que
// interactúan con procesos del sistema y directorios ejecutables.

#include "commands.h"
#include "monitorHandle.h"
#include "test_monitorHandle.h"
#include "test_utils.h"
#include "unity.h"

#include <errno.h>
#include <setjmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// Definición de variables globales para los stubs
pid_t monitor_fork_return_value = 1234;
int monitor_execl_return_value = 0;
int monitor_access_return_value = 0;
int monitor_get_executable_dir_return_value = 0;
char monitor_get_executable_dir_buffer[PATH_MAX];
char monitor_execl_called_with_path[PATH_MAX];
char monitor_execl_called_with_arg[PATH_MAX];

/**
 * @brief Mock de la función fork para pruebas de monitoreo.
 *
 * Simula llamadas a fork en start_monitor para alternar entre el proceso hijo
 * y un proceso de monitoreo simulado con un PID específico.
 *
 * @return pid_t Retorna 0 en la primera llamada (hijo), luego
 * monitor_fork_return_value.
 */
static pid_t monitor_mocked_fork(void) {
  static int fork_call_count = 0;
  fork_call_count++;
  return (fork_call_count == 1) ? 0 : monitor_fork_return_value;
}

/**
 * @brief Mock de la función execl para pruebas de monitoreo.
 *
 * Simula una llamada a execl, almacenando el path y el primer argumento,
 * luego termina el proceso con _exit(0) simulando éxito.
 *
 * @param path La ruta del ejecutable.
 * @param arg0 El primer argumento.
 * @param arg1 El segundo argumento.
 * @return int Retorna -1 en caso de fallo (simulado aquí).
 */
static int monitor_mocked_execl(const char *path, const char *arg0,
                                const char *arg1, ...) {
  strncpy(monitor_execl_called_with_path, path, PATH_MAX);
  strncpy(monitor_execl_called_with_arg, arg1, PATH_MAX);
  _exit(0); // Simular éxito de execl reemplazando la imagen del proceso
  return -1;
}

/**
 * @brief Mock de la función access para pruebas de monitoreo.
 *
 * Simula access, retornando el valor de monitor_access_return_value para
 * simular disponibilidad del archivo ejecutable.
 *
 * @param pathname Ruta del archivo.
 * @param mode Modo de acceso solicitado.
 * @return int Valor de retorno simulado.
 */
static int monitor_mocked_access(const char *pathname, int mode) {
  return monitor_access_return_value;
}

/**
 * @brief Mock de la función get_executable_dir para pruebas.
 *
 * Rellena el buffer proporcionado con el directorio del ejecutable, según
 * el valor en monitor_get_executable_dir_return_value.
 *
 * @param buffer Buffer donde almacenar la ruta.
 * @param size Tamaño máximo del buffer.
 * @return int Valor de retorno simulado.
 */
static int monitor_mocked_get_executable_dir(char *buffer, size_t size) {
  if (monitor_get_executable_dir_return_value == 0) {
    strncpy(buffer, monitor_get_executable_dir_buffer, size);
  }
  return monitor_get_executable_dir_return_value;
}

/**
 * @brief Mock de la función tcsetpgrp para pruebas.
 *
 * Simula tcsetpgrp retornando siempre 0 para indicar éxito.
 *
 * @param fd Descriptor de archivo.
 * @param pgrp ID del grupo de procesos.
 * @return int Retorna 0 simulando éxito.
 */
static int my_mocked_tcsetpgrp(int fd, pid_t pgrp) {
  return 0; // Simular éxito de tcsetpgrp
}

/**
 * @brief Prueba la función start_monitor para iniciar el proceso de monitoreo.
 *
 * Verifica que start_monitor lance correctamente el proceso de monitoreo si no
 * existe, evitando iniciar procesos duplicados. También comprueba que el PID
 * del monitor sea válido y que el proceso se esté ejecutando correctamente.
 *
 * @param void No recibe parámetros.
 */
void test_start_monitor(void) {
  // Activar modo de prueba si es necesario
  testing_mode = 1;

  // Primer llamado a `start_monitor()`: debería iniciar el proceso de monitoreo
  start_monitor();

  // Verificar que `monitor_pid` se estableció y que es válido
  TEST_ASSERT_TRUE_MESSAGE(
      monitor_pid > 0, "El PID del monitor no fue establecido correctamente");

  // Verificar que el proceso con `monitor_pid` realmente existe
  TEST_ASSERT_EQUAL_INT_MESSAGE(0, kill(monitor_pid, 0),
                                "El proceso de monitoreo no está en ejecución");

  // Capturar `monitor_pid` actual para comparar después
  pid_t initial_pid = monitor_pid;

  // Segundo llamado a `start_monitor()`: no debería iniciar un nuevo proceso
  start_monitor();

  // Verificar que `monitor_pid` no cambió
  TEST_ASSERT_EQUAL_INT_MESSAGE(
      initial_pid, monitor_pid,
      "Se inició un nuevo proceso de monitoreo innecesariamente");

  // Desactivar el modo de prueba si fue activado
  testing_mode = 0;

  // Limpiar: Terminar el proceso de monitoreo al final del test
  if (monitor_pid > 0) {
    kill(monitor_pid, SIGKILL);
    monitor_pid = 0; // Restablecer el PID después de terminar el proceso
  }

  printf("test_start_monitor passed successfully!\n");
}
