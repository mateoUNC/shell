/**
 * @file memory.h
 * @brief Memory management library with custom allocation functions.
 *
 * Esta biblioteca define funciones de asignación de memoria dinámica
 * y gestión de bloques para crear un asignador de memoria personalizado.
 */

// memory.h
#pragma once

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Macro para alinear una cantidad de bytes al siguiente múltiplo de 8.
 * 
 * @param x Cantidad de bytes a alinear.
 */
#define align(x) (((((x)-1) >> 3) << 3) + 8)

/** Tamaño mínimo de un bloque de memoria. */
#define BLOCK_SIZE sizeof(struct s_block) // Tamaño del bloque de control
/** Tamaño de página en memoria. */
#define PAGESIZE 4096
/** Política de asignación First Fit. */
#define FIRST_FIT 0
/** Política de asignación Best Fit. */
#define BEST_FIT 1
/** Tamaño del bloque */
#define DATA_START 1

// Definición de métodos de asignación
#define FIRST_FIT 0
#define BEST_FIT 1
#define WORST_FIT 2

/**
 * @struct s_block
 * @brief Estructura para representar un bloque de memoria.
 *
 * Contiene la información necesaria para gestionar la asignación y 
 * liberación de un bloque de memoria.
 */
struct s_block {
    size_t size;          /**< Tamaño del bloque de datos. */
    struct s_block *next; /**< Puntero al siguiente bloque en la lista enlazada. */
    struct s_block *prev; /**< Puntero al bloque anterior en la lista enlazada. */
    int free;             /**< Indicador de si el bloque está libre (1) o ocupado (0). */
    void *ptr;            /**< Puntero a la dirección de los datos almacenados. */
    char data[];          /**< Área donde comienzan los datos del bloque (array flexible). */
};

/** Tipo de puntero para un bloque de memoria. */
typedef struct s_block *t_block;

/**
 * @brief Obtiene el bloque que contiene una dirección de memoria dada.
 *
 * @param p Puntero a la dirección de datos.
 * @return t_block Puntero al bloque de memoria correspondiente.
 */
t_block get_block(void *p);

/**
 * @brief Verifica si una dirección de memoria es válida.
 *
 * @param p Dirección de memoria a verificar.
 * @return int Retorna 1 si la dirección es válida, 0 en caso contrario.
 */
int valid_addr(void *p);

/**
 * @brief Encuentra un bloque libre que tenga al menos el tamaño solicitado.
 *
 * @param last Puntero al último bloque.
 * @param size Tamaño solicitado.
 * @return t_block Puntero al bloque encontrado, o NULL si no se encuentra ninguno.
 */
t_block find_block(t_block *last, size_t size);

/**
 * @brief Expande el heap para crear un nuevo bloque de memoria.
 *
 * @param last Último bloque del heap.
 * @param s Tamaño del nuevo bloque.
 * @return t_block Puntero al nuevo bloque creado.
 */
t_block extend_heap(t_block last, size_t s);

/**
 * @brief Divide un bloque de memoria en dos, si el tamaño solicitado es menor que el bloque disponible.
 *
 * @param b Bloque a dividir.
 * @param s Tamaño del nuevo bloque.
 */
void split_block(t_block b, size_t s);

/**
 * @brief Fusiona un bloque libre con su siguiente bloque si también está libre.
 *
 * @param b Bloque a fusionar.
 * @return t_block Puntero al bloque fusionado.
 */
t_block fusion(t_block b);

/**
 * @brief Copia el contenido de un bloque de origen a un bloque de destino.
 *
 * @param src Bloque de origen.
 * @param dst Bloque de destino.
 */
void copy_block(t_block src, t_block dst);

/**
 * @brief Asigna un bloque de memoria del tamaño solicitado.
 *
 * @param size Tamaño en bytes del bloque a asignar.
 * @return void* Puntero al área de datos asignada.
 */
void *my_malloc(size_t size);

/**
 * @brief Libera un bloque de memoria previamente asignado.
 *
 * @param ptr Puntero al área de datos a liberar.
 */
void my_free(void *ptr);

/**
 * @brief Asigna un bloque de memoria para un número de elementos, inicializándolo a cero.
 *
 * @param number Número de elementos.
 * @param size Tamaño de cada elemento.
 * @return void* Puntero al área de datos asignada e inicializada.
 */
void *my_calloc(size_t number, size_t size);

/**
 * @brief Cambia el tamaño de un bloque de memoria previamente asignado.
 *
 * @param ptr Puntero al área de datos a redimensionar.
 * @param size Nuevo tamaño en bytes.
 * @return void* Puntero al área de datos redimensionada.
 */
void *my_realloc(void *ptr, size_t size);

/**
 * @brief Realiza una verificación extendida de la consistencia del heap.
 *
 * Detecta inconsistencias como bloques libres adyacentes no fusionados,
 * bloques con tamaños inválidos, superposición de bloques y ciclos en la lista.
 */
void check_heap_extended();

/**
 * @brief Realiza una verificación básica de la consistencia del heap.
 *
 * Detecta problemas simples en la estructura de la memoria, como bloques mal enlazados
 * o inconsistencias básicas en los tamaños de los bloques.
 */
void check_heap();

/**
 * @brief Verifica si un tamaño dado está alineado a los límites requeridos por el sistema.
 *
 * @param size Tamaño en bytes a verificar.
 * @return bool `true` si el tamaño está alineado, `false` en caso contrario.
 */
bool is_aligned(size_t size);
/**
 * @brief Configura el modo de asignación de memoria (First Fit o Best Fit).
 *
 * @param mode Modo de asignación (0 para First Fit, 1 para Best Fit).
 */
void malloc_control(int mode);

/**
 * @brief Reporta el tamaño total de bloques asignados y la cantidad de memoria libre.
 *
 * Esta función recorre todos los bloques de memoria gestionados por el asignador
 * y calcula el tamaño total de memoria asignada (ocupada) y libre.
 *
 * @param allocated_size Puntero a una variable donde se almacenará el tamaño total asignado.
 * @param free_size Puntero a una variable donde se almacenará la cantidad de memoria libre.
 */
void memory_usage(size_t *allocated_size, size_t *free_size);

/**
 * @brief Imprime el estado actual del heap para depuración.
 */
void debug_heap();

/**
 * @brief Inicializa el sistema de registro de eventos.
 *
 * Abre el archivo de log en modo append. Debe llamarse al inicio del programa.
 *
 * @param filename Nombre del archivo de log.
 * @return int Retorna 0 si se inicializó correctamente, -1 en caso de error.
 */
int initialize_logger(const char *filename);

/**
 * @brief Cierra el sistema de registro de eventos.
 *
 * Cierra el archivo de log. Debe llamarse al final del programa.
 */
void finalize_logger();

/**
 * @brief Habilita o deshabilita el registro de eventos.
 *
 * @param enable 1 para habilitar, 0 para deshabilitar.
 */
void set_logging(int enable);

/**
 * @brief Registra un evento en el archivo de log.
 *
 * @param operation Tipo de operación ("malloc", "calloc", "free", "realloc").
 * @param size Tamaño solicitado (0 si no aplica).
 * @param ptr Puntero asignado o liberado.
 * @param additional Información adicional (puede ser NULL).
 */
void log_event(const char *operation, size_t size, void *ptr, const char *additional);

/**
 * @brief Calcula la fragmentación de memoria en el heap.
 *
 * Determina el nivel de fragmentación dividiendo el tamaño total de bloques libres
 * entre el tamaño del bloque libre más grande.
 *
 * @return double Fragmentación de memoria como un porcentaje.
 */
double calculate_memory_fragmentation();

/**
 * @brief Simula actividad de memoria para pruebas y monitoreo.
 *
 * Esta función asigna y libera bloques de memoria dinámicamente
 * y registra las estadísticas para ser usadas en monitoreo.
 */
void simulate_memory_activity();
