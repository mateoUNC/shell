// main.c

#define _POSIX_C_SOURCE 200809L // Define el estándar POSIX

#include "commands.h"
#include "globals.h"
#include "monitorHandle.h"
#include "parser.h"
#include "pipes.h"
#include "prompt.h"
#include "signals.h" // signals.h ya incluye <signal.h>
#include "utils.h"
#include "file_finder.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>

void slow_print(const char *text) {
  for (const char *c = text; *c != '\0'; c++) {
    putchar(*c);    // Escribe carácter por carácter
    fflush(stdout); // Asegura que se imprime inmediatamente
    usleep(50000);  // 50ms entre caracteres
  }
}

void loading_effect(const char *message) {
  printf("%s", message); // Mensaje inicial
  fflush(stdout);
  for (int i = 0; i < 3; i++) { // Tres puntos
    usleep(500000);             // 500ms entre puntos
    printf(".");                // Agrega un punto
    fflush(stdout);
  }
  printf("\n");
}

void show_banner() {
  printf("\033[1;31m==========================================================="
         "\033[0m\n");
  printf("\033[1;31m                SHELL DE SUPERVIVENCIA\033[0m\n");
  printf("\033[1;31m==========================================================="
         "\033[0m\n");

  // Mensajes temáticos con colores
  printf("\033[1;31m"); // Rojo para dramatismo
  slow_print("Un mundo devastado por la pandemia del Cordyceps...\n\n");
  printf("\033[1;33m"); // Amarillo para descripciones técnicas
  slow_print("Tecnología escasa. Comunidades luchando por sobrevivir.\n");
  slow_print("Con esta herramienta, puedes gestionar recursos y\n");
  printf("\033[1;32m"); // Verde para un mensaje esperanzador
  slow_print("controlar sistemas esenciales. ¡Buena suerte!\n\n");

  // Efectos de carga
  printf("\033[1;34m"); // Azul para los efectos de carga
  loading_effect("Cargando módulos necesarios");
  loading_effect("Inicializando subsistemas");
  loading_effect("Preparando interfaz");
  printf("\033[0m"); // Restablecer color
}

int main(int argc, char *argv[]) {
  //show_banner();

  // Definición de variables globales
  foreground_pid = 0;
  foreground_suspended = 0;

  char input[MY_MAX_INPUT];
  char *args[MAX_ARGS];
  char *commands[MAX_PIPELINE];
  int num_commands;
  int running = 1;
  FILE *input_file = NULL;

  // Configurar el manejador de SIGCHLD
  struct sigaction sa_chld;
  sa_chld.sa_handler = sigchld_handler;
  sigemptyset(&sa_chld.sa_mask);
  sa_chld.sa_flags = SA_RESTART | SA_NOCLDSTOP;
  if (sigaction(SIGCHLD, &sa_chld, NULL) == -1) {
    perror("sigaction SIGCHLD");
    exit(EXIT_FAILURE);
  }

  // Configurar el manejador de señales para SIGINT, SIGTSTP y SIGQUIT
  struct sigaction sa;
  sa.sa_handler = shell_signal_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if (sigaction(SIGINT, &sa, NULL) == -1 ||
      sigaction(SIGTSTP, &sa, NULL) == -1 ||
      sigaction(SIGQUIT, &sa, NULL) == -1) {
    perror("sigaction");
    exit(EXIT_FAILURE);
  }

  // Ignorar señales relacionadas con terminal de la shell
  signal(SIGTTIN, SIG_IGN);
  signal(SIGTTOU, SIG_IGN);

  // Obtener el ID del proceso de la shell y establecer el grupo de procesos
  shell_pgid = getpid();
  if (setpgid(shell_pgid, shell_pgid) < 0) {
    perror("setpgid");
    exit(EXIT_FAILURE);
  }

  // Tomar el control del terminal
  if (tcsetpgrp(STDIN_FILENO, shell_pgid) == -1) {
    perror("tcsetpgrp");
    exit(EXIT_FAILURE);
  }

  // Guardar los modos terminales de la shell
  if (tcgetattr(STDIN_FILENO, &shell_tmodes) == -1) {
    perror("tcgetattr");
    exit(EXIT_FAILURE);
  }

  // Si se proporciona un archivo de comandos como argumento, abrirlo
  if (argc > 1) {
    input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
      perror("Error al abrir el archivo de comandos");
      return EXIT_FAILURE;
    }

    setvbuf(input_file, NULL, _IONBF, 0); // Desactiva el buffering

  }

  // Cambiar al directorio de inicio del usuario
  char *home = getenv("HOME");
  if (home != NULL) {
    if (chdir(home) < 0) {
      perror("chdir");
    }
  } else {
    fprintf(stderr, "No se pudo obtener el directorio HOME\n");
  }

  // Bucle principal de la shell
  while (running) {
    // Mostrar el prompt solo si estamos en modo interactivo
    if (input_file == NULL) {
      print_prompt();
    }

    // Leer el input del usuario o del archivo de comandos
    if (input_file != NULL) {
      // Leer desde el archivo de comandos
      if (fgets(input, sizeof(input), input_file) == NULL) {
        break; // Salir si se alcanza el EOF
      }
      printf("%s", input); // Imprimir el comando en pantalla para referencia
    } else {
      // Leer desde stdin
      if (fgets(input, sizeof(input), stdin) == NULL) {
        if (feof(stdin)) { // Fin de archivo (Ctrl-D)
          printf("\n");
          break;
        } else {
          perror("fgets");
          continue;
        }
      }
    }

    // Eliminar el salto de línea al final
    input[strcspn(input, "\n")] = '\0';

    // Verificar si el input contiene '|'
    if (strchr(input, '|') != NULL) {
      // Parsear la pipeline
      num_commands = parse_pipeline(input, commands);
      if (num_commands > 0) {
        // Ejecutar la pipeline
        execute_pipeline(commands, num_commands);
      }
    } else {
      // Dividir el input en argumentos
      divisor_input(input, args);

      // Si no hay ningún comando, continuar con el siguiente ciclo
      if (args[0] == NULL) {
        continue;
      }

      // Ejecutar el comando
      execute_command(args, &running);
    }
  }

  // Cerrar el archivo de comandos si está abierto
  if (input_file != NULL) {
    fclose(input_file);
  }

  return 0;
}
