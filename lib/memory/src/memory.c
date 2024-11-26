// memory.c

#include "memory.h"
#include <memory.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>


// Variables globales
void *base = NULL;
int method = FIRST_FIT; // Cambiado para asignar un valor por defecto

// Variables para el registro
static FILE *log_file = NULL;
static int logging_enabled = 1;
static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;


#define NUM_ITERATIONS 1000
#define MIN_ALLOC_SIZE 16
#define MAX_ALLOC_SIZE 256
#define MAX_BLOCKS 50

void simulate_memory_activity() {
    static void* ptrs[100];
    static int initialized = 0;

    if (!initialized) {
        for (int i = 0; i < 100; i++) {
            ptrs[i] = NULL;
        }
        initialized = 1;
    }

    for (int i = 0; i < 100; i++) {
        if (ptrs[i] == NULL) {
            size_t size = rand() % 1024 + 1; // Tamaños entre 1 y 1024 bytes
            ptrs[i] = my_malloc(size);
        } else if (rand() % 2 == 0) {
            my_free(ptrs[i]);
            ptrs[i] = NULL;
        }
    }
}

int initialize_logger(const char *filename) {
    if (log_file != NULL) {
        return 0;
    }

    log_file = fopen(filename, "a");
    if (!log_file) {
        perror("Failed to open log file");
        return -1;
    }

    fseek(log_file, 0, SEEK_END);
    long file_size = ftell(log_file);
    if (file_size == 0) {
        fprintf(log_file, "=== Memory Allocator Event Log ===\n");
    }

    return 0;
}

void finalize_logger() {
    if (log_file) {
        fclose(log_file);
        log_file = NULL;
    }
}

void set_logging(int enable) {
    logging_enabled = enable;
}

void log_event(const char *operation, size_t size, void *ptr, const char *additional) {
    if (!logging_enabled || !log_file) {
        return;
    }

    pthread_mutex_lock(&log_mutex);

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", t);

    fprintf(log_file, "[%s] Operation: %s, Size: %zu, Ptr: %p", time_str, operation, size, ptr);
    if (additional) {
        fprintf(log_file, ", %s", additional);
    }
    fprintf(log_file, "\n");

    fflush(log_file);

    pthread_mutex_unlock(&log_mutex);
}

bool is_aligned(size_t size) {
    return (size % 8) == 0;
}

t_block get_block(void *p) {
    t_block b = base;
    while (b) {
        if (b->ptr == p) {
            return b;
        }
        b = b->next;
    }
    return NULL;
}

int valid_addr(void *p) {
    if (base) {
        t_block b = get_block(p);
        if (b && b->ptr == p) {
            return 1;
        }
    }
    return 0;
}

t_block find_block(t_block *last, size_t size){
    t_block b = base;

    if (method == FIRST_FIT){
        while (b && !(b->free && b->size >= size)){
            *last = b;
            b = b->next;
        }
        return b;
    } else if (method == BEST_FIT){
        size_t dif = PAGESIZE;
        t_block best = NULL;
        
        while (b){
            if (b->free){
                if (b->size == size){
                    return b;
                }
                if (b->size > size && (b->size - size) < dif){
                    dif = b->size - size;
                    best = b;
                }
            }
            *last = b;
            b = b->next;
        }
        return best;
    } else if (method == WORST_FIT){
        size_t max_size = 0;
        t_block worst = NULL;
        
        while (b){
            if (b->free && b->size >= size){
                if (b->size > max_size){
                    max_size = b->size;
                    worst = b;
                }
            }
            *last = b;
            b = b->next;
        }
        return worst;
    }

    return NULL;
}

void split_block(t_block b, size_t s){
    if (b->size <= s + BLOCK_SIZE){
        return;
    }
    
    t_block new = (t_block)((char *)b + BLOCK_SIZE + s);
    
    new->size = b->size - s - BLOCK_SIZE;
    new->next = b->next;
    new->prev = b;
    new->free = 1;
    new->ptr = new->data;
    
    b->size = s;
    b->next = new;
    
    if (new->next) {
        new->next->prev = new;
    }

    char additional_info[100];
    snprintf(additional_info, sizeof(additional_info), "Splitted block: new free block at %p with size %zu", (void*)new, new->size);
    log_event("split_block", new->size, new->data, additional_info);
}

t_block fusion(t_block b) {
    if (!b) return NULL;

    while (b->next && b->next->free) {
        b->size += BLOCK_SIZE + b->next->size;
        b->next = b->next->next;
        if (b->next) {
            b->next->prev = b;
        }
    }

    if (b->prev && b->prev->free) {
        b = b->prev;
        b->size += BLOCK_SIZE + b->next->size;
        b->next = b->next->next;
        if (b->next) {
            b->next->prev = b;
        }
    }

    log_event("fusion", 0, b->data, "Blocks fused");

    return b;
}

void copy_block(t_block src, t_block dst){
    size_t copy_size = src->size < dst->size ? src->size : dst->size;
    memcpy(dst->ptr, src->ptr, copy_size);
}

t_block extend_heap(t_block last, size_t s) {
    t_block b;

    b = sbrk(BLOCK_SIZE + s);
    if (b == (void*) -1) {
        perror("sbrk failed");
        log_event("extend_heap", s, NULL, "Failed to extend heap using sbrk");
        return NULL;
    }

    b->size = s;
    b->next = NULL;
    b->prev = last;
    b->free = 0;
    b->ptr = b->data;

    if (last) {
        last->next = b;
    }

    log_event("extend_heap", s, b->data, "Block extended using sbrk");

    return b;
}
void set_method(int m){
    method = m;
}

void malloc_control(int m){
    if (m == FIRST_FIT) {
        set_method(FIRST_FIT);
        log_event("malloc_control", 0, NULL, "Set allocation method to FIRST_FIT");
    } else if (m == BEST_FIT) {
        set_method(BEST_FIT);
        log_event("malloc_control", 0, NULL, "Set allocation method to BEST_FIT");
    } else if (m == WORST_FIT) {
        set_method(WORST_FIT);
        log_event("malloc_control", 0, NULL, "Set allocation method to WORST_FIT");
    } else {
        printf("Error: invalid method\n");
        log_event("malloc_control", m, NULL, "Invalid allocation method");
    }
}

void debug_heap() {
    t_block b = base;
    printf("\n\033[1;36mHeap Debug:\033[0m\n");
    while (b) {
        printf("Block at %p - Size: %zu, Free: %d, Next: %p, Prev: %p\n",
               b, b->size, b->free, (void*)b->next, (void*)b->prev);
        b = b->next;
    }
}

void check_heap(void *data) {
    if (!valid_addr(data)) {
        printf("Invalid pointer: %p\n", data);
        return;
    }

    t_block block = get_block(data);
    if (block == NULL) {
        printf("Block is NULL for pointer: %p\n", data);
        return;
    }

    printf("\033[1;33mHeap check\033[0m\n");
    printf("Size: %zu\n", block->size);

    if (block->next != NULL) {
        printf("Next block: %p\n", (void *)(block->next));
    } else {
        printf("Next block: NULL\n");
    }

    if (block->prev != NULL) {
        printf("Prev block: %p\n", (void *)(block->prev));
    } else {
        printf("Prev block: NULL\n");
    }

    printf("Free: %d\n", block->free);

    if (block->ptr != NULL) {
        printf("Beginning data address: %p\n", block->ptr);
        printf("Last data address: %p\n", (void *)((char *)(block->ptr) + block->size));
    } else {
        printf("Data address: NULL\n");
    }

    printf("Heap address: %p\n", sbrk(0));
}

void extended() {
    if (!base) {
        printf("Heap is empty.\n");
        return;
    }

    printf("\n\033[1;33mExtended Heap Consistency Check\033[0m\n");

    t_block current = base;
    size_t total_size = 0;
    int block_count = 0;
    bool consistent = true;

    t_block slow = base;
    t_block fast = base;

    while (current) {
        block_count++;
        total_size += current->size + BLOCK_SIZE;

        if (current->size < 1) {
            printf("Error: Block %d at %p has invalid size: %zu (minimum allowed: 1)\n",
                   block_count, (void*)current, current->size);
            consistent = false;
        }

        if (!is_aligned(current->size)) {
            printf("Warning: Block %d at %p has unaligned size: %zu bytes\n",
                   block_count, (void*)current, current->size);
        }

        if (current->next) {
            if (current->next->prev != current) {
                printf("Error: Inconsistent pointers between blocks %d (%p) and %d (%p)\n",
                       block_count, (void*)current, block_count + 1, (void*)current->next);
                consistent = false;
            }
        }

        if (current->free && current->next && current->next->free) {
            printf("Error: Adjacent free blocks detected at %p and %p (should be fused)\n",
                   (void*)current, (void*)current->next);
            consistent = false;
        }

        if (current->next) {
            char *current_end = (char*)current + BLOCK_SIZE + current->size;
            char *next_start = (char*)current->next;
            if (current_end > next_start) {
                printf("Error: Blocks %d (%p) and %d (%p) are overlapping.\n",
                       block_count, (void*)current, block_count + 1, (void*)current->next);
                consistent = false;
            }
        }

        current = current->next;

        if (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow) {
                printf("Error: Cycle detected in the heap list.\n");
                consistent = false;
                break;
            }
        }
    }

    size_t heap_size = (char*)sbrk(0) - (char*)base;
    if (total_size > heap_size) {
        printf("Error: Total size of blocks (%zu bytes) exceeds heap size (%zu bytes).\n",
               total_size, heap_size);
        consistent = false;
    }

    current = base;
    block_count = 0;
    while (current) {
        block_count++;
        if (current->ptr != (void*)current->data) {
            printf("Error: Block %d (%p) has ptr (%p) not pointing to data (%p)\n",
                   block_count, (void*)current, current->ptr, (void*)current->data);
            consistent = false;
        }
        current = current->next;
    }

    if (consistent) {
        printf("Heap consistency check PASSED. Total blocks: %d, Total heap size: %zu bytes.\n",
               block_count, heap_size);
    } else {
        printf("Heap consistency check FAILED. Please review the errors above.\n");
    }
}

void *my_malloc(size_t size) {
    t_block b, last = NULL;
    size_t s = align(size);
    void *result = NULL;
    const char *operation = "malloc";

    if (base) {
        b = find_block(&last, s);
        if (b) {
            if ((b->size - s) >= (BLOCK_SIZE + 8)) {
                split_block(b, s);
            }
            b->free = 0;
            result = b->data;

            log_event(operation, size, result, "Block reused from free list");
        } else {
            b = extend_heap(last, s);
            if (!b) {
                log_event(operation, size, NULL, "Failed to extend heap using sbrk");
                return NULL;
            }
            base = base ? base : b;
            result = b->data;

            log_event(operation, size, result, "Block extended using sbrk");
        }
    } else {
        b = extend_heap(NULL, s);
        if (!b) {
            log_event(operation, size, NULL, "Failed to extend heap using sbrk");
            return NULL;
        }
        base = b;
        result = b->data;

        log_event(operation, size, result, "Initial block created");
    }

    return result;
}

void my_free(void *ptr) { 
    if (!ptr) {
        log_event("free", 0, NULL, "Attempted to free NULL pointer");
        return;
    }

    if (valid_addr(ptr)) {
        t_block b = get_block(ptr);
        if (!b) {
            log_event("free", 0, ptr, "get_block returned NULL");
            return;
        }
        
        b->free = 1;
        
        log_event("free", b->size, ptr, "Block marked as free");
        
        fusion(b);
    } else {
        log_event("free", 0, ptr, "Attempted to free invalid pointer");
    }
}
void *my_calloc(size_t number, size_t size){
    void *new_block;
    size_t total_size;

    if (!number || !size){
        log_event("calloc", number * size, NULL, "Attempted to calloc with zero elements or size");
        return NULL;
    }

    total_size = number * size;
    new_block = my_malloc(total_size);
    if (new_block){
        memset(new_block, 0, total_size);
        log_event("calloc", total_size, new_block, "Block allocated and zero-initialized");
    } else {
        log_event("calloc", total_size, NULL, "Failed to allocate block");
    }
    return new_block;
}

void *my_realloc(void *ptr, size_t size) { 
    size_t s;
    t_block b;
    void *newp;
    const char *operation = "realloc";

    if (!ptr)
        return my_malloc(size);

    if (valid_addr(ptr)){
        b = get_block(ptr);
        s = align(size);

        if (b->size >= s){
            if (b->size - s >= (BLOCK_SIZE + 8))
                split_block(b, s);
            log_event(operation, size, ptr, "Block resized without expanding");
            return ptr;
        } else {
            if (b->next && b->next->free && (b->size + BLOCK_SIZE + b->next->size) >= s){
                fusion(b);
                if (b->size - s >= (BLOCK_SIZE + 8))
                    split_block(b, s);
                log_event(operation, size, ptr, "Block resized by merging with next free block");
                return ptr;
            } else {
                newp = my_malloc(s);
                if (!newp){
                    log_event(operation, size, NULL, "Failed to allocate new block during realloc");
                    return NULL;
                }
                copy_block(b, get_block(newp));
                my_free(ptr);
                log_event(operation, size, newp, "Block resized by allocating new block and freeing old block");
                return newp;
            }
        }
    }
    log_event(operation, size, ptr, "Attempted to realloc invalid pointer");
    return NULL;
}

void memory_usage(size_t *allocated_size, size_t *free_size) {
    if (!allocated_size || !free_size) {
        printf("Error: Punteros NULL pasados a memory_usage.\n");
        return;
    }

    *allocated_size = 0;
    *free_size = 0;

    t_block current = base;
    int block_number = 0;

    while (current) {
        block_number++;
        if (current->free) {
            *free_size += current->size;
        } else {
            *allocated_size += current->size;
        }
        current = current->next;
    }

    printf("\n\033[1;34mMemory Usage Report\033[0m\n");
    printf("Total Allocated Memory: %zu bytes\n", *allocated_size);
    printf("Total Free Memory: %zu bytes\n\n", *free_size);

    char additional_info[100];
    snprintf(additional_info, sizeof(additional_info), "Allocated: %zu bytes, Free: %zu bytes", *allocated_size, *free_size);
    log_event("memory_usage", *allocated_size + *free_size, NULL, additional_info);
}

double calculate_memory_fragmentation() {
    size_t total_free = 0;
    size_t largest_free_block = 0;

    t_block current = base;
    while (current) {
        if (current->free) {
            total_free += current->size;
            if (current->size > largest_free_block) {
                largest_free_block = current->size;
            }
        }
        current = current->next;
    }

    if (total_free == 0) {
        return 0.0;
    }

    double fragmentation = (1.0 - ((double)largest_free_block / total_free));
    return fragmentation;
}
