# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/include        # Headers del proyecto principal
    ${CMAKE_CURRENT_SOURCE_DIR}/include # Headers de los tests
    ${PROJECT_SOURCE_DIR}/lib/memory/include # Headers de la biblioteca memory
)

# Coleccionar archivos fuente de los tests de la shell
file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
list(REMOVE_ITEM TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/test_mocks.c") # Excluir test_mocks.c

# Definir test_mocks.c por separado
set(TEST_MOCKS ${CMAKE_CURRENT_SOURCE_DIR}/src/test_mocks.c)

# Añadir los archivos de pruebas de memory
file(GLOB MEMORY_TEST_SOURCES
    "${PROJECT_SOURCE_DIR}/lib/memory/test/src/*.c"
)

# Crear el ejecutable de test unificado
add_executable(test_runner ${TEST_MOCKS} ${TEST_SOURCES} ${MEMORY_TEST_SOURCES})

# Añadir los archivos fuente del proyecto principal, excluyendo prompt.c si es necesario
target_sources(test_runner PRIVATE
    ${PROJECT_SOURCE_DIR}/src/commands.c
    ${PROJECT_SOURCE_DIR}/src/parser.c
    ${PROJECT_SOURCE_DIR}/src/utils.c
    ${PROJECT_SOURCE_DIR}/src/monitorHandle.c
    ${PROJECT_SOURCE_DIR}/src/signals.c
    ${PROJECT_SOURCE_DIR}/src/file_finder.c # <-- Incluido aquí

)

# Incluir Unity (framework de tests) y enlazar librerías
find_package(Unity REQUIRED) # Si Unity está configurado como un paquete de CMake
target_link_libraries(test_runner PRIVATE memory unity::unity)


target_link_libraries(test_runner PRIVATE cjson::cjson memory unity::unity)

# Añadir la definición de compilación para redefinir exit en tests
target_compile_definitions(test_runner PRIVATE exit=test_exit)

# Opciones de cobertura si se usa GCC o G++
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    target_compile_options(test_runner PRIVATE --coverage)
    target_link_options(test_runner PRIVATE --coverage)
endif()

# Añadir el test a CTest
enable_testing()
add_test(NAME test_runner COMMAND test_runner)
