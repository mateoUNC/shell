// pipes.c
//
// Este archivo contiene la implementación de la función `execute_pipeline`
// que permite la ejecución de múltiples comandos en pipeline dentro de la
// shell.

#include "pipes.h"
#include "commands.h"
#include "parser.h"
#include "utils.h"

#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>

void execute_pipeline(char **commands, int num_commands) {
  int in_fd = STDIN_FILENO; // Descriptor de entrada inicial (estándar)
  pid_t last_pid = 0;       // PID del último proceso en la pipeline
  int fd[2]; // Descriptores de pipe para comunicación entre procesos

  for (int i = 0; i < num_commands; i++) {
    char *args[MAX_ARGS];
    divisor_input(commands[i], args);

    // Manejo de comandos vacíos en la pipeline
    if (args[0] == NULL) {
      continue;
    }

    // Verificar si el comando es interno y no puede ejecutarse en pipeline
    if (strcmp(args[0], "cd") == 0 || strcmp(args[0], "echo") == 0 ||
        strcmp(args[0], "quit") == 0) {
      fprintf(stderr,
              "Error: El comando interno '%s' no puede ser parte de una "
              "pipeline.\n",
              args[0]);
      return;
    }

    // Crear un pipe para la comunicación, excepto para el último comando
    if (i < num_commands - 1) {
      if (pipe(fd) == -1) {
        perror("pipe");
        return;
      }
    }

    // Crear un nuevo proceso para ejecutar el comando actual
    pid_t pid = fork();
    if (pid == 0) { // Proceso hijo
      // Establecer un nuevo grupo de procesos para el hijo
      setpgid(0, 0);

      // Redirigir la entrada si no es el primer comando
      if (in_fd != STDIN_FILENO) {
        dup2(in_fd, STDIN_FILENO);
        close(in_fd);
      }

      // Redirigir la salida si no es el último comando
      if (i < num_commands - 1) {
        close(fd[0]);               // Cerrar el extremo de lectura del pipe
        dup2(fd[1], STDOUT_FILENO); // Redirigir la salida al pipe
        close(fd[1]);
      }

      // Restaurar los manejadores de señales por defecto
      signal(SIGINT, SIG_DFL);
      signal(SIGTSTP, SIG_DFL);
      signal(SIGQUIT, SIG_DFL);

      // Ejecutar el comando actual
      if (execvp(args[0], args) == -1) {
        perror("Error en el comando");
        exit(EXIT_FAILURE);
      }
    } else if (pid < 0) { // Error al crear el proceso
      perror("fork");
      return;
    } else { // Proceso padre
      // Establecer el grupo de procesos del hijo en el proceso padre
      setpgid(pid, pid);

      // Cerrar el extremo de escritura del pipe en el proceso padre
      if (i < num_commands - 1) {
        close(fd[1]);
      }

      // Actualizar in_fd para el siguiente comando
      if (in_fd != STDIN_FILENO) {
        close(in_fd);
      }
      if (i < num_commands - 1) {
        in_fd = fd[0];
      }

      // Guardar el PID del último proceso para controlar el terminal
      last_pid = pid;
    }
  }

  // Control del terminal para el último proceso de la pipeline
  if (last_pid > 0) {
    foreground_pid = last_pid;
    if (tcsetpgrp(STDIN_FILENO, foreground_pid) == -1) {
      perror("tcsetpgrp");
    }

    // Esperar al último proceso de la pipeline
    int status;
    if (waitpid(foreground_pid, &status, WUNTRACED) == -1) {
      perror("waitpid");
    }

    // Verificar si el proceso fue suspendido
    if (WIFSTOPPED(status)) {
      foreground_suspended = foreground_pid;
      printf("\n[1]+  Detenido\t\t%d\n", foreground_pid);
    }

    // Restaurar el control del terminal a la shell
    if (tcsetpgrp(STDIN_FILENO, shell_pgid) == -1) {
      perror("tcsetpgrp");
    }

    // Restaurar los modos de terminal de la shell
    if (tcgetattr(STDIN_FILENO, &shell_tmodes) == -1) {
      perror("tcgetattr");
    }
    if (tcsetattr(STDIN_FILENO, TCSADRAIN, &shell_tmodes) == -1) {
      perror("tcsetattr");
    }

    // Resetear foreground_pid si el proceso no fue suspendido
    if (foreground_suspended == 0) {
      foreground_pid = 0;
    }
  }
}
