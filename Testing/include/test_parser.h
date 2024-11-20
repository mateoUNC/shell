// tests/test_parser.h
//
// Este archivo contiene las definiciones de funciones de prueba para las
// funciones de análisis de comandos en la shell, como divisor_input y
// parse_pipeline.

#ifndef TEST_PARSER_H
#define TEST_PARSER_H

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
void test_divisor_input(void);

/**
 * @brief Prueba la función parse_pipeline para dividir un comando en una
 * secuencia de pipelines.
 *
 * Verifica que parse_pipeline divida correctamente una cadena de entrada en
 * comandos individuales separados por el operador de pipeline '|'.
 *
 * @param void No recibe parámetros.
 */
void test_parse_pipeline(void);

#endif // TEST_PARSER_H
