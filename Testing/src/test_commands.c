// Testing/src/test_commands.c
//
// Este archivo contiene las pruebas unitarias para los comandos implementados
// en la shell. Utiliza Unity como framework de pruebas y varios mocks
// personalizados para simular comportamientos de sistema en el entorno de
// prueba.

#include "commands.h"
#include "globals.h"
#include "test_mocks.h"
#include "test_utils.h"
#include "unity.h"
#include "file_finder.h"

#include <ctype.h>     // Para isdigit
#include <errno.h>     // Para obtener el código de error en fallos de sistema
#include <fcntl.h>     // Para operaciones de archivo
#include <limits.h>    // Para límites como PATH_MAX
#include <setjmp.h>    // Para manejo de saltos en tests
#include <stdio.h>     // Para entrada/salida estándar
#include <stdlib.h>    // Para manejo de memoria
#include <string.h>    // Para manipulación de cadenas
#include <sys/types.h> // Para tipos de datos del sistema
#include <sys/wait.h>  // Para manipulación de procesos y waitpid
#include <unistd.h>    // Para llamadas al sistema relacionadas con procesos

// Definiciones y variables globales para el control de los mocks
pid_t fork_return_value = 0;    // Valor de retorno simulado de fork
int execvp_return_value = 0;    // Valor de retorno simulado de execvp
pid_t waitpid_return_value = 0; // Valor de retorno simulado de waitpid
int waitpid_status_value = 0;   // Estado simulado de waitpid
static char
    buffer_output[MAX_BUFFER_SIZE]; // Buffer de salida para capturar mensajes

/**
 * @brief Prueba la función change_directory para cambiar al directorio HOME.
 *
 * Verifica que la función change_directory cambie correctamente el directorio
 * actual al directorio HOME cuando se llama con "cd" sin argumentos.
 *
 * @param void No recibe parámetros.
 */
void test_change_directory(void) {
  char *args[] = {"cd", NULL};
  char *home = getenv("HOME");

  // Verifica que la variable HOME esté configurada
  TEST_ASSERT_NOT_NULL(home);

  // Guarda el directorio actual antes de cambiarlo
  char cwd_before[PATH_MAX];
  getcwd(cwd_before, sizeof(cwd_before));

  // Llama a change_directory para cambiar al directorio HOME
  change_directory(args);

  // Verifica que el directorio actual haya cambiado a HOME
  char cwd_after[PATH_MAX];
  getcwd(cwd_after, sizeof(cwd_after));
  TEST_ASSERT_EQUAL_STRING(home, cwd_after);

  // Restaura el directorio original después de la prueba
  chdir(cwd_before);
}

/**
 * @brief Prueba la función execute_command con un comando válido.
 *
 * Verifica que execute_command procese correctamente un comando válido,
 * en este caso "ls -l", y que el estado de ejecución de la shell
 * (representado por la variable `running`) permanezca activo.
 *
 * @param void No recibe parámetros.
 */
void test_execute_command_valid(void) {
  char *args[] = {"ls", "-l", NULL};
  int running = 1;

  // Configura los valores de retorno simulados para los mocks
  fork_return_value = 1234;
  execvp_return_value = 0;
  waitpid_return_value = 1234;
  waitpid_status_value = 0;

  // Ejecuta el comando
  execute_command(args, &running);

  // Verifica que la shell siga en ejecución
  TEST_ASSERT_EQUAL_INT(1, running);
}

/**
 * @brief Prueba la función execute_command con un comando inválido.
 *
 * Verifica que execute_command maneje correctamente un comando inválido,
 * redirigiendo stderr a un pipe para capturar y validar el mensaje de error
 * esperado.
 *
 * @param void No recibe parámetros.
 */
void test_execute_command_invalid(void) {
  int running = 1;
  char *args[] = {"comando_invalido", NULL}; // Comando que no existe

  // Redirigir stderr a un pipe
  int pipe_fds[2];
  pipe(pipe_fds);
  int stderr_copy = dup(STDERR_FILENO);
  dup2(pipe_fds[1], STDERR_FILENO);
  close(pipe_fds[1]);

  // Ejecuta el comando inválido
  execute_command(args, &running);

  // Restaurar stderr
  dup2(stderr_copy, STDERR_FILENO);
  close(stderr_copy);

  // Leer el contenido del pipe
  char buffer[256];
  read(pipe_fds[0], buffer, sizeof(buffer));
  close(pipe_fds[0]);

  // Verificar el mensaje de error
  TEST_ASSERT_NOT_EQUAL(NULL, strstr(buffer, "No such file or directory"));
}

/**
 * @brief Prueba la función echo_command con un solo argumento.
 *
 * Verifica que echo_command concatene y muestre correctamente los argumentos
 * dados, en este caso "Hello, world!", con un salto de línea al final.
 *
 * @param void No recibe parámetros.
 */
void test_echo_command_single_arg(void) {
  // Limpiar el buffer antes de la prueba
  clear_printf_buffer();

  // Ejemplo de entrada
  char *args[] = {"echo", "Hello,", "world!", NULL};
  echo_command(args);

  // Verificar el contenido del buffer
  TEST_ASSERT_EQUAL_STRING("Hello, world!\n", get_printf_buffer());
}

/**
 * @brief Prueba la función echo_command cuando el argumento excede el tamaño
 * del buffer.
 *
 * Verifica que echo_command detecte y maneje correctamente un caso en el que la
 * longitud de los argumentos excede el tamaño máximo del buffer, imprimiendo un
 * mensaje de error en stderr.
 *
 * @param void No recibe parámetros.
 */
void test_echo_command_exceed_buffer(void) {
  char long_arg[MAX_BUFFER_SIZE] = {0};
  memset(long_arg, 'A',
         MAX_BUFFER_SIZE - 10); // Crea un argumento largo que excede el buffer

  char *args[] = {"echo", long_arg, "extra", NULL};

  // Redirigir stderr a un archivo temporal para capturar el mensaje de error
  freopen("temp_output_error.txt", "w+", stderr);
  echo_command(args);

  // Asegurar que el mensaje se haya escrito en el archivo y restaurar stderr
  fflush(stderr);
  freopen("/dev/tty", "a", stderr);

  // Leer el contenido del archivo para verificar el mensaje de error
  FILE *fp = fopen("temp_output_error.txt", "r");
  TEST_ASSERT_NOT_NULL_MESSAGE(fp, "No se pudo abrir temp_output_error.txt");

  char error_buffer[256];
  fgets(error_buffer, sizeof(error_buffer), fp);
  fclose(fp);
  remove("temp_output_error.txt");

  TEST_ASSERT_EQUAL_STRING("Error: El buffer es demasiado pequeño para "
                           "concatenar todos los argumentos.\n",
                           error_buffer);
}

/**
 * @brief Prueba la función execute_command con un proceso en segundo plano.
 *
 * Verifica que execute_command maneje correctamente un comando con el operador
 * "&" para ejecutar el proceso en segundo plano y que la shell continúe en
 * ejecución. Además, comprueba que se imprima el ID de trabajo en el buffer de
 * salida.
 *
 * @param void No recibe parámetros.
 */
void test_execute_command_background(void) {
  int running = 1;
  printf_called = 0;     // Reinicia la bandera de printf_called
  clear_printf_buffer(); // Limpia el buffer antes de la prueba
  char *args[] = {"echo", "Hola", "&", NULL};

  // Ejecuta el comando en segundo plano
  execute_command(args, &running);

  // Verificar que el proceso se ejecutó en segundo plano
  TEST_ASSERT_TRUE_MESSAGE(printf_called,
                           "Se esperaba que printf fuera llamado.");
  TEST_ASSERT_NOT_EQUAL(
      NULL, strstr(get_printf_buffer(),
                   "[1]")); // Confirma que se imprimió el ID de trabajo

  // Asegurarse de que la shell sigue en ejecución
  TEST_ASSERT_TRUE(running);
}
