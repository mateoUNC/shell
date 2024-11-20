/**
 * @file utils.h
 * @brief Declaraciones de funciones auxiliares para la shell.
 *
 * Este archivo contiene las declaraciones de funciones auxiliares que asisten
 * en el manejo de recursos y la gestión de la interfaz de usuario en la shell,
 * incluyendo funciones para liberar argumentos y limpiar la pantalla.
 */

#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

/**
 * @brief Libera la memoria asignada para un array de argumentos.
 *
 * Esta función recorre un array de punteros a cadenas y libera la memoria
 * asignada para cada argumento. El array debe terminar con un valor NULL.
 *
 * @param args Array de cadenas (char*) a liberar.
 */
void free_args(char **args);

/**
 * @brief Limpia la pantalla y coloca el cursor en la esquina superior
 * izquierda.
 *
 * Utiliza secuencias de escape ANSI para borrar el contenido de la pantalla y
 * mover el cursor al inicio, proporcionando una interfaz de shell limpia.
 */
void clear_screen();

#endif // UTILS_H
