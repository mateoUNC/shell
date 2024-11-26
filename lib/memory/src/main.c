#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_PATH "/tmp/metrics_fifo"

int main() {
    int fifo_fd = open(FIFO_PATH, O_WRONLY | O_CREAT, 0666);
    if (fifo_fd < 0) {
        perror("Error al abrir el FIFO");
        return 1;
    }

    // Inicializar logger
    if (initialize_logger("memory_dynamic_log.txt") != 0) {
        return 1;
    }

    while (1) {
        // Simular actividad de memoria
        simulate_memory_activity();

        // Obtener fragmentación
        double fragmentation = calculate_memory_fragmentation();

        // Preparar los datos en formato JSON para enviar al monitor
        char metrics_json[128];
        snprintf(metrics_json, sizeof(metrics_json),
                 "{\"fragmentation\": %.2f}", fragmentation);

        // Enviar datos al FIFO
        write(fifo_fd, metrics_json, strlen(metrics_json));
        sleep(5); // Esperar antes de la siguiente iteración

    }

    close(fifo_fd);
    finalize_logger();
    return 0;
}
