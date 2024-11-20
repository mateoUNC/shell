// prompt.c
//
// Este archivo contiene la implementación de la función `print_prompt`,
// que muestra el prompt de la shell con el nombre de usuario, hostname,
// y el directorio actual.

#include "prompt.h"
#include "globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_prompt() {
  char cwd[PATH_MAX];           // Buffer para almacenar el directorio actual
  char hostname[HOST_NAME_MAX]; // Buffer para almacenar el hostname
  char *user = getenv("USER");  // Obtener el nombre del usuario
  char *home = getenv("HOME");  // Obtener el directorio home del usuario

  // Obtener el hostname de la máquina
  if (gethostname(hostname, sizeof(hostname)) != 0) {
    perror("Error al obtener el nombre del host");
    strcpy(hostname, "unknown");
  }

  // Obtener el directorio actual de trabajo
  if (getcwd(cwd, sizeof(cwd)) != NULL) {
    // Si el directorio actual está dentro de HOME, reemplaza esa parte con "~"
    if (home != NULL && strstr(cwd, home) == cwd) {
      printf("%s@%s:~%s$ ", user, hostname, cwd + strlen(home));
    } else {
      // Si no está dentro de HOME, muestra la ruta completa
      printf("%s@%s:%s$ ", user, hostname, cwd);
    }
  } else {
    perror("Error al obtener el directorio actual");
  }

  // Vaciar el buffer de salida para mostrar el prompt inmediatamente
  fflush(stdout);
}
