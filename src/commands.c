// comandos.c
#include "commands.h"
#include "globals.h"
#include "monitorHandle.h" // Para start_monitor(), stop_monitor(), status_monitor()
#include "utils.h"         // Para free_args()
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>

static int job_id = 1; // Inicializamos el ID de trabajo globalmente

int get_current_job_id(void) { return job_id; }

void echo_command(char **args) {
  int i = 1; // Comienza desde args[1] ya que args[0] es "echo"
  char buffer[MAX_BUFFER_SIZE] = ""; // Buffer para el resultado final

  while (args[i] != NULL) {
    char *arg = args[i];
    size_t arg_len = strlen(arg);
    char processed_arg[256]; // Buffer temporal para el argumento procesado
    size_t start = 0;
    size_t end = arg_len;

    // Remueve comillas al inicio
    if (arg[0] == '"' || arg[0] == '\'') {
      start = 1;
    }

    // Remueve comillas al final
    if (arg_len > start &&
        (arg[arg_len - 1] == '"' || arg[arg_len - 1] == '\'')) {
      end = arg_len - 1;
    }

    // Copia el argumento sin comillas al buffer temporal
    strncpy(processed_arg, arg + start, end - start);
    processed_arg[end - start] = '\0'; // Asegura el terminador null

    // Verifica que no exceda el tamaño del buffer principal
    if (strlen(buffer) + strlen(processed_arg) + 2 >
        MAX_BUFFER_SIZE) { // +1 para espacio y +1 para '\0'
      fprintf(stderr, "Error: El buffer es demasiado pequeño para concatenar "
                      "todos los argumentos.\n");
      return;
    }

    // Concatena el argumento procesado al buffer principal
    strcat(buffer, processed_arg);

    // Agrega un espacio si hay más argumentos
    if (args[i + 1] != NULL) {
      strcat(buffer, " ");
    }

    i++;
  }

  // Agrega el salto de línea al final y muestra el resultado
  strcat(buffer, "\n");
  printf("%s", buffer);
}

void execute_command(char **args, int *running) {
  int background = 0;
  int input_redirect = -1;
  int output_redirect = -1;

  // Manejo de redirección y procesos en segundo plano
  for (int i = 0; args[i] != NULL; i++) {
    if (strcmp(args[i], "<") == 0) {
      args[i] = NULL;
      input_redirect = open(args[i + 1], O_RDONLY);
      if (input_redirect < 0) {
        perror("Error al abrir el archivo de entrada");
        return;
      }
      i++;
    } else if (strcmp(args[i], ">") == 0) {
      args[i] = NULL;
      output_redirect = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
      if (output_redirect < 0) {
        perror("Error al abrir el archivo de salida");
        return;
      }
      i++;
    } else if (strcmp(args[i], "&") == 0) {
      background = 1; // Marcar el proceso como en segundo plano
      args[i] = NULL;
    }
  }

  // Manejo del comando "fg" para reanudar procesos suspendidos
  if (strcmp(args[0], "fg") == 0) {
    if (foreground_suspended > 0) {
      foreground_pid = foreground_suspended;
      foreground_suspended = 0;
      printf("Reanudando proceso %d en primer plano\n", foreground_pid);

      if (tcsetpgrp(STDIN_FILENO, foreground_pid) == -1)
        perror("tcsetpgrp");
      if (kill(-foreground_pid, SIGCONT) < 0)
        perror("kill(SIGCONT)");

      int status;
      if (waitpid(foreground_pid, &status, WUNTRACED) == -1)
        perror("waitpid");

      if (WIFSTOPPED(status)) {
        foreground_suspended = foreground_pid;
        printf("\n[1]+  Detenido\t\t%d\n", foreground_pid);
      }

      if (tcsetpgrp(STDIN_FILENO, shell_pgid) == -1)
        perror("tcsetpgrp");
      foreground_pid = 0;
    } else {
      printf("No hay procesos en estado detenido\n");
    }
    return;
  }

  // Manejo de comandos internos específicos
  if (strcmp(args[0], "start_monitor") == 0) {
    start_monitor();
    return;
  }
  if (strcmp(args[0], "stop_monitor") == 0) {
    stop_monitor();
    return;
  }
  if (strcmp(args[0], "status_monitor") == 0) {
    status_monitor();
    return;
  }
  if (strcmp(args[0], "quit") == 0) {
    printf("Cerrando la shell de Mateo...\n");
    *running = 0;
    return;
  }
  if (strcmp(args[0], "cd") == 0) {
    change_directory(args);
    return;
  }

  // Comando "echo" con soporte de redirección
  if (strcmp(args[0], "echo") == 0) {
    pid_t pid = fork();
    if (pid == 0) { // Proceso hijo para manejar "echo"
      if (output_redirect != -1) {
        if (dup2(output_redirect, STDOUT_FILENO) == -1) {
          perror("Error al redirigir la salida");
          exit(EXIT_FAILURE);
        }
        close(output_redirect);
      }
      echo_command(args);
      exit(EXIT_SUCCESS);
    } else if (pid < 0) {
      perror("Error al crear el proceso para echo");
    } else {
      handle_parent_process(pid, background);
    }
    return;
  }

  // Ejecución de comandos externos con redirección y segundo plano
  pid_t pid = fork();
  if (pid == 0) {  // Proceso hijo
    setpgid(0, 0); // Crea un nuevo grupo de procesos

    // Control de terminal solo en primer plano
    if (!background && tcsetpgrp(STDIN_FILENO, getpid()) == -1) {
      perror("tcsetpgrp");
      exit(EXIT_FAILURE);
    }
    // Manejo de redirección de entrada y salida
    handle_redirection(input_redirect, output_redirect);

    // Restaurar manejadores de señales por defecto y ejecutar comando
    reset_signal_handlers();
    if (execvp(args[0], args) == -1) {
      perror("Error en el comando");
      exit(EXIT_FAILURE);
    }
  } else if (pid < 0) {
    perror("Error al crear el proceso");
  } else {
    handle_parent_process(pid, background);
  }
}

void handle_redirection(int input_redirect, int output_redirect) {
  if (input_redirect != -1) {
    if (dup2(input_redirect, STDIN_FILENO) == -1) {
      perror("Error al redirigir la entrada");
      exit(EXIT_FAILURE);
    }
    close(input_redirect);
  }
  if (output_redirect != -1) {
    if (dup2(output_redirect, STDOUT_FILENO) == -1) {
      perror("Error al redirigir la salida");
      exit(EXIT_FAILURE);
    }
    close(output_redirect);
  }
}

void handle_parent_process(pid_t pid, int background) {
  if (background) {
    printf("[%d] %d\n", job_id++, pid);
  } else {
    int status;
    foreground_pid = pid;

    if (waitpid(foreground_pid, &status, WUNTRACED) == -1)
      perror("waitpid");

    if (WIFSTOPPED(status)) {
      foreground_suspended = foreground_pid;
      printf("\n[1]+  Detenido\t\t%d\n", foreground_pid);
    }

    if (tcsetpgrp(STDIN_FILENO, shell_pgid) == -1)
      perror("tcsetpgrp");
    foreground_pid = 0;
  }
}

/**
 * @brief Restaura los manejadores de señales por defecto en el proceso hijo.
 */
void reset_signal_handlers() {
  signal(SIGINT, SIG_DFL);
  signal(SIGTSTP, SIG_DFL);
  signal(SIGQUIT, SIG_DFL);
}

void change_directory(char **args) {
  char cwd[PATH_MAX];
  char *home = getenv("HOME"); // Obtener el directorio HOME del usuario
  char *oldpwd =
      getenv("OLDPWD"); // Obtener el último directorio visitado (OLDPWD)

  // Guardar el directorio actual en `cwd`
  if (getcwd(cwd, sizeof(cwd)) == NULL) {
    perror("Error al obtener el directorio actual");
    return;
  }

  // Manejar "cd -" para cambiar al último directorio (OLDPWD)
  if (args[1] != NULL && strcmp(args[1], "-") == 0) {
    if (oldpwd != NULL) {
      // Si OLDPWD está definido, cambiar a él
      if (chdir(oldpwd) == 0) {
        printf("%s\n", oldpwd); // Imprimir OLDPWD después de cambiar
        setenv("OLDPWD", cwd,
               1); // Actualizar OLDPWD al directorio actual anterior
        setenv("PWD", oldpwd, 1); // Actualizar PWD al nuevo directorio
      } else {
        perror("Error en el comando"); // Error al intentar cambiar a OLDPWD
      }
    } else {
      fprintf(
          stderr,
          "OLDPWD no está definido\n"); // Mensaje si OLDPWD no está definido
    }
    return;
  }

  // Si no hay argumento, cambiar al directorio HOME
  if (args[1] == NULL) {
    args[1] = home;
  }

  // Cambiar al directorio especificado en args[1]
  if (chdir(args[1]) == 0) {
    setenv("OLDPWD", cwd,
           1); // Guardar el directorio actual en OLDPWD antes del cambio
    setenv("PWD", args[1], 1); // Actualizar PWD al nuevo directorio
  } else {
    perror("Error en el comando"); // Mensaje de error si chdir falla
  }
}
