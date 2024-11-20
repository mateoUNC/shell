// tests/test_parser.c
//
// Este archivo contiene pruebas unitarias para las funciones de análisis de
// comandos en la shell, incluyendo divisor_input y parse_pipeline.

#include "globals.h"
#include "parser.h"
#include "unity.h"
#include <string.h>

/**
 * @brief Prueba la función divisor_input para dividir una cadena de entrada en
 * argumentos.
 *
 * Verifica que divisor_input divida correctamente la cadena de entrada en
 * argumentos individuales y que termine con un valor NULL en el arreglo de
 * argumentos.
 *
 * @param void No recibe parámetros.
 */
void test_divisor_input(void) {
  char input[] = "ls -l /home/user";
  char *args[MAX_ARGS];

  // Llama a divisor_input para dividir la entrada en argumentos
  divisor_input(input, args);

  // Verificaciones de los argumentos
  TEST_ASSERT_NOT_NULL(args[0]);
  TEST_ASSERT_EQUAL_STRING("ls", args[0]);
  TEST_ASSERT_EQUAL_STRING("-l", args[1]);
  TEST_ASSERT_EQUAL_STRING("/home/user", args[2]);
  TEST_ASSERT_NULL(args[3]);
}

/**
 * @brief Prueba la función parse_pipeline para dividir un comando en una
 * secuencia de pipelines.
 *
 * Verifica que parse_pipeline divida correctamente una cadena de entrada en
 * comandos individuales separados por el operador de pipeline '|'.
 *
 * @param void No recibe parámetros.
 */
void test_parse_pipeline(void) {
  char input[] = "ls -l | grep txt | sort";
  char *commands[MAX_PIPELINE];

  // Llama a parse_pipeline para dividir la entrada en una secuencia de
  // pipelines
  int num_commands = parse_pipeline(input, commands);

  // Verificaciones de los comandos y el número total
  TEST_ASSERT_EQUAL_INT(3, num_commands);
  TEST_ASSERT_EQUAL_STRING("ls -l", commands[0]);
  TEST_ASSERT_EQUAL_STRING("grep txt", commands[1]);
  TEST_ASSERT_EQUAL_STRING("sort", commands[2]);
  TEST_ASSERT_NULL(commands[3]);
}
