/**
 * @file monitorHandle.c
 * @brief Implementaciones de funciones para controlar el programa de monitoreo.
 */

#include <cjson/cJSON.h>
#include <errno.h>
#include <fcntl.h> // Para open
#include <globals.h>
#include <libgen.h> // Para dirname
#include <limits.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int testing_mode = 0; // Define la variable para las pruebas

// Variable global para almacenar el PID del proceso de monitoreo
pid_t monitor_pid = 0;

/**
 * @brief Ruta al FIFO usado por el monitor.
 */
#define FIFO_PATH "/tmp/metrics_fifo"

/**
 * @brief Variable de control para mantener la ejecución.
 */
volatile bool keep_running = true;

int read_sampling_interval() {
  FILE *file = fopen("/tmp/sampling_interval.txt", "r");
  int interval = 1; // Valor predeterminado

  if (file != NULL) {
    fscanf(file, "%d", &interval);
    fclose(file);
  } else {
    perror("Error al leer el archivo de intervalo de muestreo");
  }
  return interval;
}

int get_executable_dir(char *buffer, size_t size) {
  ssize_t len = readlink("/proc/self/exe", buffer, size - 1);
  if (len == -1) {
    perror("Error al obtener el path del ejecutable");
    return -1;
  }
  buffer[len] = '\0'; // Asegurar que la cadena está terminada

  // Obtener el directorio del ejecutable
  char *dir = dirname(buffer);
  if (dir == NULL) {
    perror("Error al obtener el directorio del ejecutable");
    return -1;
  }

  // Verificar que la longitud del directorio no exceda el tamaño del buffer
  if (strlen(dir) >= size) {
    fprintf(stderr,
            "Buffer demasiado pequeño para el directorio del ejecutable\n");
    return -1;
  }

  // Copiar el directorio al buffer
  strcpy(buffer, dir);
  return 0;
}

void start_monitor() {
  if (testing_mode) {
    // Omite configuraciones que interfieren en los tests
    printf("Monitor iniciado en modo de prueba\n");
    monitor_pid = 1234; // Valor simulado
    return;
  } else {
    if (monitor_pid > 0) {
      printf("El monitor ya está en ejecución con PID %d\n", monitor_pid);
      return;
    }

    // Obtener el directorio del ejecutable de la shell
    char exe_dir[PATH_MAX];
    if (get_executable_dir(exe_dir, sizeof(exe_dir)) != 0) {
      fprintf(stderr, "Error al obtener el directorio del ejecutable\n");
      return;
    }

    // Construir la ruta completa a metricShell
    const char *suffix = "/metricShell";
    char metric_path[PATH_MAX];
    snprintf(metric_path, sizeof(metric_path), "%s%s", exe_dir, suffix);

    // Construir la ruta completa a config.json
    const char *config_suffix = "/config.json";
    char config_path[PATH_MAX];
    snprintf(config_path, sizeof(config_path), "%s%s", exe_dir, config_suffix);

    // Verificar si metricShell existe y es ejecutable
    if (access(metric_path, X_OK) != 0) {
      perror("metricShell no existe o no es ejecutable");
      return;
    }

    // Crear proceso hijo para ejecutar metricShell
    pid_t pid = fork();
    if (pid == 0) {
      // Proceso hijo: ejecuta metricShell con config.json como argumento
      printf("Ejecutando metricShell en el proceso hijo\n");
      execl(metric_path, "metricShell", config_path, NULL);

      // Si execl falla
      perror("Error al ejecutar metricShell");
      exit(EXIT_FAILURE);
    } else if (pid < 0) {
      perror("Error al crear el proceso de monitoreo");
    } else {
      monitor_pid = pid;
      printf("Monitor iniciado con PID %d\n", monitor_pid);
    }
  }
}

void stop_monitor() {
  if (monitor_pid <= 0) {
    printf("El monitor no está en ejecución.\n");
    return;
  }

  // Enviar la señal SIGTERM al proceso de monitoreo
  if (kill(monitor_pid, SIGTERM) == -1) {
    if (errno == ESRCH) {
      printf("El proceso de monitoreo ya no existe.\n");
    } else {
      perror("Error al detener el monitor");
    }
  } else {
    printf("Monitor detenido con PID %d\n", monitor_pid);
    monitor_pid = 0; // Restablecer PID del monitor
  }
}

void handle_sigint(int sig) {
  (void)sig; // Evita advertencias por no usar el parámetro
  printf("\nTerminando el monitor de estado...\n");
  keep_running = false;
}

void status_monitor() {
  // Registrar el manejador de señal para SIGINT
  signal(SIGINT, handle_sigint);
  printf("\n Control + C para terminar el status.\n");
  while (keep_running) {
    int fifo_fd = open(FIFO_PATH, O_RDONLY | O_NONBLOCK);
    if (fifo_fd < 0) {
      perror("Error al abrir el FIFO para lectura");
      sleep(1);
      continue;
    }

    char buffer[4096];
    ssize_t bytes_read = read(fifo_fd, buffer, sizeof(buffer) - 1);
    if (bytes_read > 0) {
      buffer[bytes_read] = '\0';

      cJSON *json = cJSON_Parse(buffer);
      if (!json) {
        fprintf(stderr, "Error al parsear JSON: %s\n", cJSON_GetErrorPtr());
        close(fifo_fd);
        continue;
      }

      // Mostrar las métricas si existen
      cJSON *cpu_usage = cJSON_GetObjectItem(json, "cpu_usage");
      if (cJSON_IsNumber(cpu_usage)) {
        printf("CPU Usage: %.2f%%\n", cpu_usage->valuedouble);
      }

      cJSON *total_memory = cJSON_GetObjectItem(json, "total_memory");
      cJSON *used_memory = cJSON_GetObjectItem(json, "used_memory");
      cJSON *free_memory = cJSON_GetObjectItem(json, "free_memory");
      if (cJSON_IsNumber(total_memory) && cJSON_IsNumber(used_memory) &&
          cJSON_IsNumber(free_memory)) {
        printf("Memory Usage: Total: %.2f MB, Used: %.2f MB, Free: %.2f MB\n",
               total_memory->valuedouble, used_memory->valuedouble,
               free_memory->valuedouble);
      }

      cJSON *disk_reads = cJSON_GetObjectItem(json, "disk_reads");
      cJSON *disk_writes = cJSON_GetObjectItem(json, "disk_writes");
      if (cJSON_IsNumber(disk_reads) && cJSON_IsNumber(disk_writes)) {
        printf("Disk Usage: Reads: %.0f, Writes: %.0f\n",
               disk_reads->valuedouble, disk_writes->valuedouble);
      }

      cJSON *rx_bytes = cJSON_GetObjectItem(json, "rx_bytes");
      cJSON *tx_bytes = cJSON_GetObjectItem(json, "tx_bytes");
      if (cJSON_IsNumber(rx_bytes) && cJSON_IsNumber(tx_bytes)) {
        printf("Network Usage: RX: %.0f bytes, TX: %.0f bytes\n",
               rx_bytes->valuedouble, tx_bytes->valuedouble);
      }

      cJSON *context_switches = cJSON_GetObjectItem(json, "context_switches");
      if (cJSON_IsNumber(context_switches)) {
        printf("Context Switches: %.0f\n", context_switches->valuedouble);
      }

      cJSON *running_processes = cJSON_GetObjectItem(json, "running_processes");
      if (cJSON_IsNumber(running_processes)) {
        printf("Running Processes: %.0f\n", running_processes->valuedouble);
      }

      cJSON_Delete(json);
    }

    close(fifo_fd);
    sleep(read_sampling_interval()); // Pausa antes de la siguiente lectura
  }
  printf("Status monitor detenido.\n");
}