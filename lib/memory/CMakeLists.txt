# # lib/memory/CMakeLists.txt
# cmake_minimum_required(VERSION 3.10)
# project(memory VERSION 1.0.0 DESCRIPTION "Memory Module" LANGUAGES C)

# # Añadir la biblioteca
# add_library(memory
#     src/memory.c
#     # Añade otros archivos fuente si es necesario
# )

# # Especificar directorios de inclusión para la biblioteca 'memory'
# target_include_directories(memory PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/include
# )

cmake_minimum_required(VERSION 3.10)
project(memory_test VERSION 1.0 LANGUAGES C)

# Añadir el ejecutable que compilará 'main.c' y 'memory.c'
add_executable(memory_test src/main.c src/memory.c)

# Incluir directorios de encabezados
target_include_directories(memory_test PRIVATE include)

# Añadir la biblioteca pthread para manejar los mutex (necesario en 'memory.c')
find_package(Threads REQUIRED)
target_link_libraries(memory_test PRIVATE Threads::Threads)

# Establecer el estándar C
set_target_properties(memory_test PROPERTIES C_STANDARD 99)
