/**
 * @file prompt.h
 * @brief Declaración de la función para mostrar el prompt en la shell.
 *
 * Este archivo define la función `print_prompt`, que muestra el prompt en la
 * shell con información sobre el usuario y el directorio actual.
 */

#ifndef PROMPT_H
#define PROMPT_H

/**
 * @brief Imprime el prompt de la shell con información de usuario y directorio.
 *
 * Muestra el nombre de usuario, el hostname, y el directorio actual. Si el
 * directorio actual está dentro del directorio home del usuario, se representa
 * con `~`.
 */
void print_prompt();

#endif // PROMPT_H
