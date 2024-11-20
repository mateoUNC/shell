// Testing/include/test_signals.h
//
// Este archivo contiene las definiciones de funciones de prueba para verificar
// el manejo de señales en la shell, como SIGINT y SIGTSTP, con y sin procesos
// en primer plano.

#ifndef TEST_SIGNALS_H
#define TEST_SIGNALS_H

/**
 * @brief Prueba el manejo de SIGINT cuando hay un proceso en primer plano.
 *
 * Verifica que shell_signal_handler envíe SIGINT al grupo de procesos
 * correspondiente sin afectar otras configuraciones.
 *
 * @param void No recibe parámetros.
 */
void test_shell_signal_handler_SIGINT_with_foreground_pid(void);

/**
 * @brief Prueba el manejo de SIGTSTP cuando hay un proceso en primer plano.
 *
 * Verifica que shell_signal_handler envíe SIGTSTP al grupo de procesos
 * correspondiente, restablezca foreground_pid, y llame a print_prompt.
 *
 * @param void No recibe parámetros.
 */
void test_shell_signal_handler_SIGTSTP_with_foreground_pid(void);

/**
 * @brief Prueba el manejo de SIGINT sin un proceso en primer plano.
 *
 * Verifica que shell_signal_handler llame a print_prompt y fflush(stdout)
 * sin intentar enviar señales.
 *
 * @param void No recibe parámetros.
 */
void test_shell_signal_handler_SIGINT_no_foreground_pid(void);

/**
 * @brief Prueba el manejo de SIGTSTP sin un proceso en primer plano.
 *
 * Verifica que shell_signal_handler llame a print_prompt y fflush(stdout)
 * sin intentar enviar señales.
 *
 * @param void No recibe parámetros.
 */
void test_shell_signal_handler_SIGTSTP_no_foreground_pid(void);

#endif // TEST_SIGNALS_H
