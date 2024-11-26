# lib/memory/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(memory VERSION 1.0.0 DESCRIPTION "Memory Module" LANGUAGES C)

# Añadir la biblioteca
add_library(memory
    src/memory.c
    # Añade otros archivos fuente si es necesario
)

# Especificar directorios de inclusión para la biblioteca 'memory'
target_include_directories(memory PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
