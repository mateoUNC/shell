// parser.c
//
// Este archivo contiene las implementaciones de funciones para analizar la
// entrada de la shell, dividiendo en argumentos individuales y manejando
// pipelines.

#include "parser.h"
#include "globals.h"
#include <ctype.h>
#include <string.h>

void divisor_input(char *input, char **args) {
  int i = 0;
  char *token = strtok(input, " \t\r\n");

  while (token != NULL && i < MAX_ARGS - 1) {
    args[i++] = token;
    token = strtok(NULL, " \t\r\n");
  }

  args[i] = NULL; // Termina el array de argumentos
}

int parse_pipeline(char *input, char **commands) {
  int i = 0;
  char *token = strtok(input, "|");

  while (token != NULL && i < MAX_PIPELINE - 1) {
    // Eliminar espacios iniciales
    while (isspace(*token))
      token++;

    // Eliminar espacios finales
    char *end = token + strlen(token) - 1;
    while (end > token && isspace(*end)) {
      *end-- = '\0';
    }

    commands[i++] = token;
    token = strtok(NULL, "|");
  }

  commands[i] = NULL; // Termina el array de comandos
  return i;
}
