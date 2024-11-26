// prompt.c
//
// Este archivo contiene la implementación de la función `print_prompt`,
// que muestra el prompt de la shell con el nombre de usuario, hostname,
// y el directorio actual.

#include "prompt.h"
#include "globals.h"
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

void print_prompt() {
    char cwd[PATH_MAX];           // Buffer para almacenar el directorio actual
    char hostname[HOST_NAME_MAX]; // Buffer para almacenar el hostname
    char *user = getenv("USER");  // Obtener el nombre del usuario
    char *home = getenv("HOME");  // Obtener el directorio home del usuario

    char prompt[512]; // Buffer para construir el prompt final
    size_t offset = 0;

    // Obtener el hostname de la máquina
    if (gethostname(hostname, sizeof(hostname)) != 0) {
        strncpy(hostname, "unknown", sizeof(hostname));
    }

    // Obtener el directorio actual de trabajo
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        if (home != NULL && strstr(cwd, home) == cwd) {
            // Si el directorio actual está dentro de HOME, reemplaza esa parte con "~"
            offset = snprintf(prompt, sizeof(prompt), "%s@%s:~%s$ ", user, hostname, cwd + strlen(home));
        } else {
            // Si no está dentro de HOME, muestra la ruta completa
            offset = snprintf(prompt, sizeof(prompt), "%s@%s:%s$ ", user, hostname, cwd);
        }
    } else {
        snprintf(prompt, sizeof(prompt), "%s@%s:unknown$ ", user, hostname);
    }

    // Escribe el prompt directamente en stdout
    write(STDOUT_FILENO, prompt, offset);
}
