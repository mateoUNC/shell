#ifndef CONFIG_FILE_FINDER_H
#define CONFIG_FILE_FINDER_H

#define MAX_PATH_SIZE 1024
#define MAX_BUFFER 4096

// Declaración de la función para imprimir el contenido de un archivo
void print_file_content(const char *file_path);

// Declaración de la función recursiva para buscar archivos .config y .json
void find_config_files(const char *dir_path);

#endif // CONFIG_FILE_FINDER_H
