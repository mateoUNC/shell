/**
 * @file monitorHandle.h
 * @brief Declaraciones de funciones para controlar el programa de monitoreo del
 * sistema.
 *
 * Este archivo contiene las funciones `start_monitor`, `stop_monitor` y
 * `status_monitor`, que permiten controlar el programa de monitoreo de métricas
 * en un proceso separado.
 */

#ifndef MONITOR_H
#define MONITOR_H

#include <sys/types.h>

/**
 * @brief Variable global para almacenar el PID del proceso de monitoreo.
 *
 * Esta variable se utiliza para rastrear el proceso de monitoreo del sistema.
 * Si el proceso está activo, `monitor_pid` almacena su PID; en caso contrario,
 * tiene el valor 0.
 */
extern pid_t monitor_pid;

/**
 * @brief Inicia el programa de monitoreo del sistema.
 *
 * La función crea un proceso hijo para ejecutar el programa `metrics` en
 * segundo plano. Si el proceso de monitoreo ya está en ejecución, la función
 * muestra un mensaje indicando el PID.
 */
void start_monitor(void);

/**
 * @brief Detiene el programa de monitoreo del sistema.
 *
 * Envía una señal `SIGTERM` al proceso de monitoreo para detenerlo.
 * Si el proceso no está en ejecución, la función muestra un mensaje indicando
 * que no está activo.
 */
void stop_monitor(void);

/**
 * @brief Muestra el estado actual del programa de monitoreo.
 *
 * Verifica si el proceso de monitoreo sigue activo o si no está en ejecución.
 * Muestra un mensaje indicando el PID del proceso si está en ejecución o un
 * mensaje de estado inactivo.
 */
void status_monitor();

/**
 * @brief Lee el intervalo de muestreo desde un archivo de configuración.
 *
 * Intenta abrir y leer el archivo de configuración en la ruta
 * "/tmp/sampling_interval.txt" para obtener el intervalo de muestreo
 * especificado. Si el archivo no existe o no se puede leer, se usa un valor
 * predeterminado de 1 segundo.
 *
 * @return El intervalo de muestreo en segundos leído del archivo, o 1 si ocurre
 * un error.
 */
int read_sampling_interval();

/**
 * @brief Obtiene el directorio donde se encuentra el ejecutable de la shell.
 *
 * Esta función utiliza `/proc/self/exe` para obtener el path del ejecutable
 * actual y extrae el directorio en el que se encuentra. Copia el resultado en
 * el buffer proporcionado.
 *
 * @param buffer Puntero a un buffer donde se almacenará el directorio del
 * ejecutable.
 * @param size Tamaño del buffer.
 * @return 0 si tiene éxito, -1 en caso de error.
 */
int get_executable_dir(char *buffer, size_t size);

/**
 * @brief Manejador de señal SIGINT.
 *
 * Esta función se utiliza como manejador de la señal SIGINT (Ctrl+C) para
 * interrumpir el estado del monitor de manera segura, terminando su ejecución.
 *
 * @param sig La señal recibida (normalmente SIGINT).
 */
void handle_sigint(int sig);

#endif // MONITOR_H
