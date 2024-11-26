#include "file_finder.h"
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h> // Para flock

// Función para imprimir el contenido de un archivo
void print_file_content(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("[ERROR] No se pudo abrir el archivo");
        return;
    }

    setvbuf(file, NULL, _IONBF, 0); // Desactiva el buffering

    int fd = fileno(file); // Obtener el descriptor de archivo
    if (flock(fd, LOCK_SH) == -1) { // Adquirir un bloqueo compartido
        perror("[ERROR] No se pudo bloquear el archivo");
        fclose(file);
        return;
    }
    printf("[DEBUG] Archivo bloqueado correctamente: %s\n", file_path);

    char buffer[MAX_BUFFER];
    while (fgets(buffer, sizeof(buffer), file)) {
        printf("%s", buffer);
    }

    if (ferror(file)) {
        perror("[ERROR] Error al leer el archivo");
    }

    flock(fd, LOCK_UN); // Liberar el bloqueo
    fclose(file);
    printf("[DEBUG] Archivo desbloqueado y cerrado: %s\n", file_path);
}


// Función recursiva para buscar archivos .config y .json
void find_config_files(const char *dir_path) {
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("No se pudo abrir el directorio");
        return;
    }

    printf("Explorando el directorio: %s en busca de archivos '.config'\n", dir_path);

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Ignorar los directorios "." y ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char path[MAX_PATH_SIZE];
        snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);

        struct stat statbuf;
        if (stat(path, &statbuf) == -1) {
            perror("Error al obtener información del archivo");
            continue;
        }

        // Si es un archivo regular, verificar la extensión
        if (S_ISREG(statbuf.st_mode)) {
            // Comprobar si la extensión del archivo es .config o .json
            if (strstr(entry->d_name, ".config") != NULL || strstr(entry->d_name, ".json") != NULL) {
                printf("Archivo de configuración encontrado: %s\n", path);
                printf("Contenido de %s:\n", path);
                print_file_content(path); // Imprimir el contenido del archivo
                printf("\n"); // Salto de línea después del contenido
            }
        }
        // Si es un directorio, buscar recursivamente en él
        else if (S_ISDIR(statbuf.st_mode)) {
            find_config_files(path);
        }
    }
    closedir(dir);
}
