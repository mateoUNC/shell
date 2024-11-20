/**
 * @file pipes.h
 * @brief Declaración de la función para manejar la ejecución de pipelines en la
 * shell.
 *
 * Este archivo define la función `execute_pipeline`, que permite la ejecución
 * de comandos en pipeline, redirigiendo la salida de cada comando a la entrada
 * del siguiente.
 */

#ifndef PIPES_H
#define PIPES_H

/**
 * @brief Ejecuta una secuencia de comandos en pipeline.
 *
 * Esta función toma un array de comandos y ejecuta cada uno en una secuencia
 * de pipes, permitiendo que la salida de cada comando sea la entrada del
 * siguiente.
 *
 * @param commands Array de cadenas que contiene los comandos a ejecutar en
 * pipeline.
 * @param num_commands Número de comandos en el pipeline.
 */
void execute_pipeline(char **commands, int num_commands);

#endif // PIPES_H
