// Testing/src/test_main.c
//
// Archivo principal para ejecutar las pruebas unitarias de la shell.
// Utiliza Unity como framework de pruebas y agrupa las pruebas de diferentes
// módulos, incluyendo el parser, comandos, manejo de monitor y señales.

#include "test_commands.h"
#include "test_mocks.h"
#include "test_monitorHandle.h"
#include "test_parser.h"
#include "test_redireccion.h"
#include "test_signals.h"
#include "test_utils.h"
#include "test_malloc.h"
#include "test_fusion.h"
#include "test_worst_fit.h"
#include "unity.h"

//#include "test_printf.h"

// Declarar las variables de control para los mocks (si es necesario)
extern pid_t fork_return_value;
extern int execvp_return_value;
extern pid_t waitpid_return_value;
extern int waitpid_status_value;

// Variables para exit()
extern int exit_called;
extern int exit_status;
extern jmp_buf exit_env;

/**
 * @brief Configuración inicial que se ejecuta antes de cada prueba.
 *
 * Reinicia los valores de las variables de los stubs y las variables de control
 * de exit(), asegurando que cada prueba comienza con un estado limpio.
 *
 * @param void No recibe parámetros.
 */
void setUp(void) {
  // Reiniciar valores de los stubs antes de cada test
  fork_return_value = 0;
  execvp_return_value = 0;
  waitpid_return_value = 0;
  waitpid_status_value = 0;

  // Reiniciar variables de exit()
  exit_called = 0;
  exit_status = 0;
}

/**
 * @brief Limpieza que se ejecuta después de cada prueba.
 *
 * Esta función es opcional y actualmente no realiza ninguna limpieza,
 * pero puede ser utilizada para liberar recursos si es necesario en el futuro.
 *
 * @param void No recibe parámetros.
 */
void tearDown(void) {
  // Opcional: limpiar recursos después de cada test
}

/**
 * @brief Función principal que ejecuta todas las pruebas unitarias.
 *
 * Inicializa Unity, ejecuta las pruebas para cada módulo y retorna el estado
 * final de la ejecución de pruebas. Incluye pruebas para el parser, comandos,
 * procesos en segundo plano, manejo de señales, y monitoreo.
 *
 * @param void No recibe parámetros.
 * @return int Retorna el resultado de UNITY_END().
 */
int main(void) {
  UNITY_BEGIN();

  // Pruebas del parser
  RUN_TEST(test_divisor_input);
  RUN_TEST(test_parse_pipeline);

  // Pruebas de commands
  RUN_TEST(test_change_directory);
  RUN_TEST(test_execute_command_valid);
  RUN_TEST(test_execute_command_invalid);

  // Test de Monitor.
  RUN_TEST(test_start_monitor);

  // Pruebas de señales
  RUN_TEST(test_shell_signal_handler_SIGINT_with_foreground_pid);
  RUN_TEST(test_shell_signal_handler_SIGTSTP_with_foreground_pid);
  RUN_TEST(test_shell_signal_handler_SIGINT_no_foreground_pid);
  RUN_TEST(test_shell_signal_handler_SIGTSTP_no_foreground_pid);

  // Pruebas Redireccion.
  RUN_TEST(test_cat_redireccion_entrada);
  RUN_TEST(test_cat_redireccion_entrada_multilinea);
  RUN_TEST(test_cat_redireccion_entrada_vacia);

  // Pruebas de memory
  RUN_TEST(test_fusion_of_adjacent_blocks);
  RUN_TEST(test_worst_fit_allocation);
  RUN_TEST(test_malloc_simple);

  return UNITY_END();
}
