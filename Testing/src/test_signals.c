// Testing/src/test_signals.c
//
// Este archivo contiene pruebas unitarias para los manejadores de señales en la
// shell. Las pruebas verifican el comportamiento de shell_signal_handler cuando
// recibe SIGINT o SIGTSTP con y sin un proceso en primer plano.

#include "test_signals.h"
#include "globals.h" // Asegura la inclusión de globals.h
#include "signals.h"
#include "test_mocks.h"
#include "unity.h"
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

extern pid_t foreground_pid;

/**
 * @brief Prueba el manejo de SIGINT cuando hay un proceso en primer plano.
 *
 * Verifica que shell_signal_handler envíe SIGINT al grupo de procesos de
 * foreground_pid. No debe llamar a print_prompt, printf, fflush o tcsetpgrp en
 * este caso.
 *
 * @param void No recibe parámetros.
 */
void test_shell_signal_handler_SIGINT_with_foreground_pid(void) {
  // Inicializar variables antes de cada test
  kill_called = 0;
  kill_pid = 0;
  kill_sig = 0;
  print_prompt_called = 0;
  printf_called = 0;
  memset(printf_buffer, 0, sizeof(printf_buffer));
  fflush_called = 0;
  fflush_stream = NULL;
  tcsetpgrp_called = 0;
  tcsetpgrp_fd = 0;
  tcsetpgrp_pgrp = 0;

  // Configurar condiciones iniciales
  foreground_pid = 1234; // Simular un proceso en primer plano

  // Llamar al manejador con SIGINT
  shell_signal_handler(SIGINT);

  // Verificar que kill fue llamado con los argumentos correctos
  TEST_ASSERT_TRUE(kill_called);
  TEST_ASSERT_EQUAL_INT(-1234,
                        kill_pid); // PID negativo para el grupo de procesos
  TEST_ASSERT_EQUAL_INT(SIGINT, kill_sig);

  // Verificar que foreground_pid no cambió
  TEST_ASSERT_EQUAL_INT(1234, foreground_pid);

  // Verificar que print_prompt, printf, fflush y tcsetpgrp no fueron llamados
  TEST_ASSERT_FALSE(print_prompt_called);
  TEST_ASSERT_FALSE(printf_called);
  TEST_ASSERT_FALSE(fflush_called);
  TEST_ASSERT_FALSE(tcsetpgrp_called);
}

/**
 * @brief Prueba el manejo de SIGTSTP cuando hay un proceso en primer plano.
 *
 * Verifica que shell_signal_handler envíe SIGTSTP al grupo de procesos de
 * foreground_pid, restablezca foreground_pid y llame a print_prompt y
 * fflush(stdout).
 *
 * @param void No recibe parámetros.
 */
void test_shell_signal_handler_SIGTSTP_with_foreground_pid(void) {
  // Inicializar variables antes de cada test
  kill_called = 0;
  kill_pid = 0;
  kill_sig = 0;
  print_prompt_called = 0;
  printf_called = 0;
  memset(printf_buffer, 0, sizeof(printf_buffer));
  fflush_called = 0;
  fflush_stream = NULL;
  tcsetpgrp_called = 0;
  tcsetpgrp_fd = 0;
  tcsetpgrp_pgrp = 0;

  // Configurar condiciones iniciales
  foreground_pid = 1234; // Simular un proceso en primer plano

  // Llamar al manejador con SIGTSTP
  shell_signal_handler(SIGTSTP);

  // Verificar que kill fue llamado con los argumentos correctos
  TEST_ASSERT_TRUE_MESSAGE(kill_called, "kill should have been called");
  TEST_ASSERT_EQUAL_INT_MESSAGE(-1234, kill_pid,
                                "kill was not called with the correct PID");
  TEST_ASSERT_EQUAL_INT_MESSAGE(SIGTSTP, kill_sig,
                                "kill was not called with SIGTSTP");

  // Verificar que foreground_pid se restableció
  TEST_ASSERT_EQUAL_INT_MESSAGE(0, foreground_pid,
                                "foreground_pid was not reset to 0");

  // Verificar que print_prompt fue llamado
  TEST_ASSERT_TRUE_MESSAGE(print_prompt_called,
                           "print_prompt should have been called");

  // Verificar que printf no fue llamado
  TEST_ASSERT_FALSE_MESSAGE(printf_called,
                            "printf should not have been called");

  // Verificar que fflush fue llamado con stdout
  TEST_ASSERT_TRUE_MESSAGE(fflush_called, "fflush should have been called");
  TEST_ASSERT_EQUAL_PTR_MESSAGE(stdout, fflush_stream,
                                "fflush was not called with stdout");

  // Verificar que tcsetpgrp no fue llamado
  TEST_ASSERT_FALSE_MESSAGE(tcsetpgrp_called,
                            "tcsetpgrp should not have been called");
}

/**
 * @brief Prueba el manejo de SIGINT sin un proceso en primer plano.
 *
 * Verifica que shell_signal_handler llame a print_prompt y fflush(stdout)
 * sin intentar enviar señales.
 *
 * @param void No recibe parámetros.
 */
void test_shell_signal_handler_SIGINT_no_foreground_pid(void) {
  // Inicializar variables antes de cada test
  kill_called = 0;
  print_prompt_called = 0;
  fflush_called = 0;
  fflush_stream = NULL;
  foreground_pid = 0;

  // Llamar al manejador con SIGINT
  shell_signal_handler(SIGINT);

  // Verificar que no se llamó a kill
  TEST_ASSERT_FALSE(kill_called);

  // Verificar que print_prompt fue llamado
  TEST_ASSERT_TRUE_MESSAGE(print_prompt_called,
                           "print_prompt debería haber sido llamado");

  // Verificar que fflush fue llamado con stdout
  TEST_ASSERT_TRUE(fflush_called);
  TEST_ASSERT_EQUAL_PTR(stdout, fflush_stream);
}

/**
 * @brief Prueba el manejo de SIGTSTP sin un proceso en primer plano.
 *
 * Verifica que shell_signal_handler llame a print_prompt y fflush(stdout)
 * sin intentar enviar señales.
 *
 * @param void No recibe parámetros.
 */
void test_shell_signal_handler_SIGTSTP_no_foreground_pid(void) {
  // Inicializar variables antes de cada test
  kill_called = 0;
  print_prompt_called = 0;
  fflush_called = 0;
  fflush_stream = NULL;
  foreground_pid = 0;

  // Llamar al manejador con SIGTSTP
  shell_signal_handler(SIGTSTP);

  // Verificar que no se llamó a kill
  TEST_ASSERT_FALSE(kill_called);

  // Verificar que print_prompt fue llamado
  TEST_ASSERT_TRUE_MESSAGE(print_prompt_called,
                           "print_prompt debería haber sido llamado");

  // Verificar que fflush fue llamado con stdout
  TEST_ASSERT_TRUE(fflush_called);
  TEST_ASSERT_EQUAL_PTR(stdout, fflush_stream);
}
