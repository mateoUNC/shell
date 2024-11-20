/**
 * @file parser.h
 * @brief Declaraciones de funciones para el análisis de entrada en la shell.
 *
 * Este archivo define las funciones necesarias para procesar la entrada del
 * usuario en la shell, dividiendo la entrada en argumentos individuales y
 * manejando comandos en pipelines.
 */

#ifndef PARSER_H
#define PARSER_H

#define MAX_ARGS 100    /**< Número máximo de argumentos permitidos. */
#define MAX_PIPELINE 10 /**< Número máximo de comandos en una pipeline. */

/**
 * @brief Divide la entrada del usuario en argumentos individuales.
 *
 * Esta función toma una cadena de entrada y la divide en un array de
 * argumentos, separando por espacios y caracteres de control como tabuladores y
 * saltos de línea.
 *
 * @param input La cadena de entrada a dividir.
 * @param args Array donde se almacenarán los argumentos resultantes.
 */
void divisor_input(char *input, char **args);

/**
 * @brief Divide un comando de entrada en una secuencia de pipelines.
 *
 * Toma una cadena de entrada y la divide en comandos individuales separados por
 * el operador de pipeline "|". Cada comando se recorta para eliminar espacios
 * iniciales y finales antes de almacenarlo.
 *
 * @param input La cadena de entrada a dividir.
 * @param commands Array donde se almacenarán los comandos de la pipeline.
 * @return int Número de comandos en la pipeline.
 */
int parse_pipeline(char *input, char **commands);

#endif // PARSER_H
