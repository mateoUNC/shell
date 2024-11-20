// signals.c
//
// Este archivo contiene las implementaciones de los manejadores de señales para
// la shell, incluyendo el control de interrupciones y la gestión de procesos
// hijos que terminan o son suspendidos.

#include "signals.h"
#include "globals.h"
#include "prompt.h"

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>

// Variables globales para almacenar el PID del proceso en primer plano y el
// grupo de procesos de la shell
pid_t foreground_pid = 0;       // PID del proceso en primer plano
pid_t foreground_suspended = 0; // PID del proceso suspendido en primer plano
pid_t shell_pgid;               // ID del grupo de procesos de la shell
struct termios shell_tmodes;    // Modo terminal de la shell

void shell_signal_handler(int sig) {
  if (foreground_pid > 0) {
    // Enviar la señal al grupo de procesos del proceso en primer plano
    if (kill(-foreground_pid, sig) < 0) {
      perror("Error al enviar señal al grupo de procesos");
    }

    // Si la señal es SIGTSTP, se suspende el proceso en primer plano
    if (sig == SIGTSTP) {
      foreground_pid = 0; // Restablecer foreground_pid
      print_prompt();
      fflush(stdout);
    }
  } else {
    // Si no hay proceso en primer plano, ignora la señal y muestra el prompt
    printf("\n");
    print_prompt();
    fflush(stdout);
  }
}

void sigchld_handler(int sig) {
  (void)sig; // Indica que 'sig' no se usa en el cuerpo de la función

  int saved_errno = errno; // Guardar errno para restaurarlo después
  int status;
  pid_t pid;

  // Recolectar todos los procesos hijos que hayan terminado o suspendido
  while ((pid = waitpid(-1, &status, WUNTRACED | WNOHANG)) > 0) {
    if (pid == foreground_pid) {
      // El proceso en primer plano es manejado directamente en execute_command
      continue;
    }

    if (WIFSTOPPED(status)) {
      // Proceso en segundo plano suspendido
      printf("\n[Proceso en segundo plano %d] Detenido\n", pid);
    } else {
      // Proceso en segundo plano terminado
      printf("\n[Proceso en segundo plano %d] Hecho\n", pid);
    }

    // Mostrar el prompt de nuevo después de notificar sobre el proceso
    print_prompt();
    fflush(stdout);
  }

  // Restaurar errno para no afectar otras operaciones
  errno = saved_errno;
}
