// utils.c
//
// Este archivo contiene la implementación de funciones auxiliares para la
// shell, incluyendo la liberación de memoria para argumentos y la limpieza de
// pantalla.

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void free_args(char **args) {
  for (int i = 0; args[i] != NULL; i++) {
    free(args[i]);
  }
}

void clear_screen() {
  printf("\033[H\033[J"); // Secuencias ANSI: \033[H mueve el cursor; \033[J
                          // borra la pantalla.
  fflush(stdout);         // Asegura que los cambios se reflejen inmediatamente.
}
